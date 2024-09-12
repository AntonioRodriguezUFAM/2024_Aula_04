#include<iostream>
#include<stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

// Number of Images channels

#define CHANNEL_NUM 3

using namespace std;


#include<iostream>

int main() {

	std::cout << std::endl;
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << "-------------------------- IMPACT LAB 2023 ---------------------------" << std::endl;
	std::cout << "--------------------------  ICOMP - UFAM   ---------------------------" << std::endl;
	std::cout << "--------------------------   TURMA 2023    ---------------------------" << std::endl;
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
	int width, height, bpp;

	// Load the Images and save

	unsigned char* rgb_image = stbi_load("Mountain.jpg", &width, &height, &bpp, CHANNEL_NUM);

	if (rgb_image == NULL) {
		printf("Error in loading the image\n");
		exit(1);
	}


	//printf("Loaded image with a width of %dpx, a height of %dpx. The original image had %d channels, the loaded image has %d channels.\n", width, height, original_no_channels, desired_no_channels);

	//stbi_write_png("images/output/ImagePNG.png", width, height, desired_no_channels, rgb_image, width * desired_no_channels);
	stbi_write_png("images/output/ImagePNG.png", width, height, CHANNEL_NUM, rgb_image, width * CHANNEL_NUM);
	//stbi_write_jpg("images/output/imageJPG.jpg", width, height, desired_no_channels, rgb_image, 100);

	stbi_image_free(rgb_image);

	return 0;


}