#include<iostream>
#include<stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// Number of Images channels

#define CHANNEL_NUM 4

using namespace std;


#include<iostream>

int main() {

	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "-------------------------- IMPACT LAB 2024 ---------------------------" << std::endl;
	std::cout << "--------------------------  ICOMP - UFAM   ---------------------------" << std::endl;
	std::cout << "--------------------------   TURMA 2024    ---------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << "--------------------------   Programação em Image Filter --------------------" << std::endl;


	std::cout << "                     Prog. Antonio Souto Rodriguez                    " << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << std::endl;


	// images size and properties bpp = bit per pixel
	//int width, height, bpp;
	//int width, height, original_no_channels;
	//int desired_no_channels = 5;


	// Load the Images and save
	//unsigned char* rgb_image = stbi_load("Mountain.jpg", &width, &height, &original_no_channels, desired_no_channels);
	//unsigned char* rgb_image = stbi_load("image/Mountain.jpg", &width, &height, &bpp, CHANNEL_NUM);


	// images size and properties bpp = bit per pixel
	int width, height, channels;

	// Load the Images and save

	unsigned char* img = stbi_load("Mountain.jpg", &width, &height, &channels, 4);
	//unsigned char* img = stbi_load("apple.jpg", &width, &height, &channels, 3);


	if (img == NULL) {
		printf("Error in loading the image\n");
		exit(1);
	}

	cout << "Loaded image with a width of : " << width << " a height of: " << height << " Channel number : " << channels<< endl;
	cout << "Image size: " << width * height * CHANNEL_NUM << endl;

	// Process the image to make green!!

	for (int i = 0;i < width * height * 3;i += 3) {

		img[i + 1] = 255;
		img[i + 2] = 55;
	}



	// write images JPG ou PNG
	stbi_write_png("images/output/GreenPNG_01.png", width, height, channels, img, width * channels);
//	stbi_write_jpg("images/output/GreenJPG_01.jpg", width, height, channels, img, 100);

	stbi_image_free(img);

	return 0;


}