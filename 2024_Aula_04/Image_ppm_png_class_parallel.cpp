
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono> // Timer

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include <cmath>  // For ceil

using namespace std;
using namespace std::chrono; // Timer

// Pixel structure to hold RGB values
struct Pixel {
    int r, g, b;
};

// Class Image handles PPM image loading, saving, and processing
class Image {
public:
    int width = 0, height = 0, max_color = 255;
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
        outfile << "P6" << endl << width << " " << height << endl << max_color << endl;

        for (const auto& pixel : pixels) {
            outfile << static_cast<unsigned char>(pixel.r)
                << static_cast<unsigned char>(pixel.g)
                << static_cast<unsigned char>(pixel.b);
        }

        outfile.close();
    }

    // Load images with STB (JPG, PNG, etc.)
    bool loadSTBImage(const string& filename) {
        int channels;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3); // Force loading 3 channels (RGB)
        if (!data) {
            cerr << "Error: Could not load image using STB: " << filename << endl;
            return false;
        }

        pixels.resize(width * height);
        for (int i = 0; i < width * height; ++i) {
            pixels[i].r = data[i * 3 + 0]; // Red
            pixels[i].g = data[i * 3 + 1]; // Green
            pixels[i].b = data[i * 3 + 2]; // Blue
        }

        stbi_image_free(data); // Free the image memory after loading
        return true;
    }

    // Save images with STB (JPG, PNG, etc.)
    bool saveSTBImage(const string& filename, const string& format) const {
        vector<unsigned char> raw_data;
        raw_data.reserve(width * height * 3);

        for (const auto& pixel : pixels) {
            raw_data.push_back(static_cast<unsigned char>(pixel.r));
            raw_data.push_back(static_cast<unsigned char>(pixel.g));
            raw_data.push_back(static_cast<unsigned char>(pixel.b));
        }

        if (format == "png") {
            if (stbi_write_png(filename.c_str(), width, height, 3, raw_data.data(), width * 3) == 0) {
                cerr << "Error: Could not save PNG file: " << filename << endl;
                return false;
            }
        }
        else if (format == "jpg") {
            if (stbi_write_jpg(filename.c_str(), width, height, 3, raw_data.data(), 100) == 0) { // 100 = maximum quality
                cerr << "Error: Could not save JPG file: " << filename << endl;
                return false;
            }
        }
        else {
            cerr << "Error: Unsupported format " << format << endl;
            return false;
        }

        return true;
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

        //int num_threads = 4; // Limit threads to 4 by default
       cout << "Number of Threads: " << num_threads << endl;
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

    // Load PNG or JPG using STB
    if (image.loadSTBImage("images/ship_4k_rgba.png")) {
        std::cout << "--------------------------   Load PNG Image     ---------------------" << std::endl;
    }
    else {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    std::cout << std::endl;

    std::cout << "----------------------  Run Sequential: Invert Color   ----------------" << std::endl;
    std::cout << std::endl;
    image.invertColors();       // Sequential Code
    std::cout << std::endl;

    std::cout << "----------------------  Run Parallel: Invert Color   ------------------" << std::endl;
    std::cout << std::endl;
    image.threadsInvertColors(); // Parallel Code
    std::cout << std::endl;

    // Save as PNG or JPG using STB
    if (image.saveSTBImage("images/output/output.png", "png")) {
        std::cout << "--------------------------   Save PNG Image     ----------------------" << std::endl;
    }
    else {
        std::cerr << "Failed to save image" << std::endl;
        return -1;
    }

    std::cout << std::endl;
    std::cout << "                               Code: END                  " << std::endl;

    return 0;
}
