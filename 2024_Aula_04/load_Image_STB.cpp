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
	int width, height, bpp;

	// Load the Images and save

	unsigned char* rgb_image = stbi_load("Mountain.jpg", &width, &height, &bpp, CHANNEL_NUM);

	if (rgb_image == NULL) {
		printf("Error in loading the image\n");
		exit(1);
	}

	cout << "Loaded image with a width of : "<<width<<" a height of: "<<height<< " Channel number : "<< CHANNEL_NUM<<endl;
	cout << "Image size: " << width * height * CHANNEL_NUM << endl;
	

	// write images JPG ou PNG
	stbi_write_png("images/output/ImagePNG_02.png", width, height, CHANNEL_NUM, rgb_image, width * CHANNEL_NUM);
	stbi_write_jpg("images/output/imageJPG_01.jpg", width, height, CHANNEL_NUM, rgb_image, 100);

	stbi_image_free(rgb_image);

	return 0;


}