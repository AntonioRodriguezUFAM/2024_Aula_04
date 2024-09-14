// PPM Image processing - MultiThreads - Impact Lab 2024

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono> // Timer
#include <cmath> // ceil

using namespace std;
using namespace std::chrono; // Timer

// Pixel structure to hold RGB values
struct Pixel {
    int r, g, b;
};

// Class Image handles PPM image loading, saving, and processing
class Image {
public:
    int width = 0, height = 0, max_color = 0;
    vector<Pixel> pixels;

    Image() = default;

    Image(int w, int h, int m) {
        width = w;
        height = h;
        max_color = m;
        pixels.resize(width * height);
    }

    // Load PPM Images
    void loadPPM(const string& filename) {
        ifstream infile(filename, ios::binary);
        if (!infile.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }
        string magic_number;
        infile >> magic_number >> width >> height >> max_color;
        pixels.resize(width * height);

        for (int i = 0; i < width * height; ++i) {
            Pixel pixel;
            infile >> pixel.r >> pixel.g >> pixel.b;
            pixels[i] = pixel;
        }

        infile.close();
    }

    // Save PPM Image
    void savePPM(const string& filename) const {
        ofstream outfile(filename, ios::binary);
        if (!outfile.is_open()) {
            cerr << "Error: Could not save file " << filename << endl;
            return;
        }
        outfile << "P3" << endl << width << " " << height << endl << max_color << endl;

        for (const auto& pixel : pixels) {
            outfile << static_cast<unsigned char>(pixel.r)
                << static_cast<unsigned char>(pixel.g)
                << static_cast<unsigned char>(pixel.b);
        }

        outfile.close();
    }

    // Invert colors (sequential processing)
    void invertColors() {
        auto start = high_resolution_clock::now(); // Start Timer
        for (auto& pixel : pixels) {
            pixel.r = max_color - pixel.r;
            pixel.g = max_color - pixel.g;
            pixel.b = max_color - pixel.b;
        }
        auto end = high_resolution_clock::now(); // End Timer
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Sequential Invert Color Time: " << duration.count() << " ms" << std::endl;
    }

    // Invert colors (multithreaded processing)
    void threadsInvertColors() {
        const int num_threads = thread::hardware_concurrency();
        if (num_threads == 0) {
            cerr << "Error: Could not determine number of threads." << endl;
            return;
        }

        vector<thread> threads(num_threads);
        int chunk_size = (width * height + num_threads - 1) / num_threads; // Calculate chunk size

        auto start = high_resolution_clock::now(); // Start Timer

        // Process each chunk in a separate thread
        for (int i = 0; i < num_threads; ++i) {
            threads[i] = thread([this, i, chunk_size]() {
                int start_idx = i * chunk_size;
                int end_idx = min(start_idx + chunk_size, static_cast<int>(pixels.size()));
                for (int j = start_idx; j < end_idx; ++j) {
                    pixels[j].r = max_color - pixels[j].r;
                    pixels[j].g = max_color - pixels[j].g;
                    pixels[j].b = max_color - pixels[j].b;
                }
                });
        }

        // Wait for all threads to complete
        for (auto& t : threads) {
            if (t.joinable()) t.join();
        }

        auto end = high_resolution_clock::now(); // End Timer
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Parallel Invert Color Time: " << duration.count() << " ms" << std::endl;
    }
};

int main() {

    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "-------------------------- IMPACT LAB 2024: ICOMP - UFAM   -----------" << std::endl;
    std::cout << "--------------------------        TURMA 2024    ----------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------   Parallel Programming --------------------" << std::endl;
    std::cout << "                       CODE: PPM Image Processing in C++              " << std::endl;
    std::cout << "                         - Sequential VS Parallel -                   " << std::endl;
    std::cout << "                         Prof. Antonio Souto Rodriguez                " << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    Image image;
    image.loadPPM("images/Image01.ppm");
    std::cout << "--------------------------   Load Image PPM     ---------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "----------------------  Run Sequential: Invert Color   ----------------" << std::endl;
    std::cout << std::endl;
    image.invertColors();       // Sequential Code
    std::cout << std::endl;

    std::cout << "----------------------  Run Parallel: Invert Color   ------------------" << std::endl;
    std::cout << std::endl;
    image.threadsInvertColors(); // Parallel Code
    std::cout << std::endl;

    image.savePPM("images/output/Parallel_output01.ppm");
    std::cout << "--------------------------   Save Image PPM     ----------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                               Code: END                  " << std::endl;

    return 0;
}
