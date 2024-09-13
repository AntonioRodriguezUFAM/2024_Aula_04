#include <iostream>
#include <stdint.h>
#include <vector>
#include <thread>
#include <chrono>  // For performance timing

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// Number of Image channels
#define CHANNEL_NUM 4

using namespace std;

// Function to process a portion of the image in a separate thread (for multithreading)
void process_image_chunk(unsigned char* img, int start, int end) {
    for (int i = start; i < end; i += 3) {
        img[i + 1] = 255; // Set the green channel to maximum
        img[i + 2] = 55;  // Modify the blue channel to 55
    }
}

// Function to process the image in a single-threaded way
void process_image_single_thread(unsigned char* img, int total_pixels) {
    for (int i = 0; i < total_pixels; i += 3) {
        img[i + 1] = 255; // Set the green channel to maximum
        img[i + 2] = 55;  // Modify the blue channel to 55
    }
}

int main() {
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "-------------------------- IMPACT LAB 2024 ---------------------------" << std::endl;
    std::cout << "--------------------------  ICOMP - UFAM   ---------------------------" << std::endl;
    std::cout << "--------------------------   TURMA 2024    ---------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------- Programação em Image Filter --------------------" << std::endl;
    std::cout << "                     Prog. Antonio Souto Rodriguez                    " << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;

    // Load the image
    int width, height, channels;
    unsigned char* img = stbi_load("Mountain.jpg", &width, &height, &channels, CHANNEL_NUM);
    if (img == NULL) {
        cout << "Error in loading the image\n";
        return 1;
    }

    cout << "Loaded image with width: " << width << ", height: " << height << ", Channel number: " << channels << endl;
    cout << "Image size: " << width * height * CHANNEL_NUM << " bytes" << endl;

    // Total number of pixels to process (for RGB channels)
    int total_pixels = width * height * 3;

    // ---------------- Single-Threaded Processing ----------------
    unsigned char* single_thread_img = (unsigned char*)malloc(width * height * channels);
    memcpy(single_thread_img, img, width * height * channels);

    auto start_single_thread = std::chrono::high_resolution_clock::now();
    process_image_single_thread(single_thread_img, total_pixels);
    auto stop_single_thread = std::chrono::high_resolution_clock::now();
    auto duration_single_thread = std::chrono::duration_cast<std::chrono::milliseconds>(stop_single_thread - start_single_thread);

    // Write single-threaded result to PNG
    stbi_write_png("images/output/SingleThreaded_GreenPNG.png", width, height, channels, single_thread_img, width * channels);
    free(single_thread_img);

    // ---------------- Multithreaded Processing ----------------
    unsigned char* multi_thread_img = (unsigned char*)malloc(width * height * channels);
    memcpy(multi_thread_img, img, width * height * channels);

    const int num_threads = 4;
    int chunk_size = total_pixels / num_threads;
    vector<thread> threads;

    auto start_multi_thread = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? total_pixels : (i + 1) * chunk_size;
        threads.push_back(thread(process_image_chunk, multi_thread_img, start, end));
    }

    for (auto& th : threads) {
        th.join();
    }

    auto stop_multi_thread = std::chrono::high_resolution_clock::now();
    auto duration_multi_thread = std::chrono::duration_cast<std::chrono::milliseconds>(stop_multi_thread - start_multi_thread);

    // Write multithreaded result to PNG
    stbi_write_png("images/output/MultiThreaded_GreenPNG.png", width, height, channels, multi_thread_img, width * channels);
    free(multi_thread_img);

    // Free original image memory
    stbi_image_free(img);

    // Display timing results
    cout << "Single-threaded image processing time: " << duration_single_thread.count() << " ms" << endl;
    cout << "Multithreaded image processing time: " << duration_multi_thread.count() << " ms" << endl;

    cout << "Image processing completed." << endl;

    return 0;
}
