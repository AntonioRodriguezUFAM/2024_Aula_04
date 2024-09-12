
#include <fstream>
#include <iostream>

using namespace std;

int main() { // Thread

// Read Image
	ifstream Image_Read;
	Image_Read.open("images/output/New_Images_2.ppm");

// Write Image
	ofstream Image_write;
	Image_write.open("images/apollo.ppm");

	// Copy Memory
	//Image_Read >> memory>> Image_Write

	//Image Header
	// Type = P3 ou P6
	string type = "", width = "", height = "", RGBMax = "";

	//int width = 0, height = 0, RGBMax = 0, red, g, b;


	// Copy Memory
	//Image_Read >> memory
	Image_Read >> type;
	Image_Read >> width;
	Image_Read >> height;
	Image_Read >> RGBMax;


	

	// Copy Memory to new Image
	//memory>> Image_Write
	Image_write << type << endl;
	Image_write << width << " " << height << endl;
	Image_write << RGBMax << endl;


	// Image Body
	string red = "", green = "", blue = "";



	while (!Image_Read.eof()) { // ImageRead numero Pixel = 611 * 480 = 293.280 Pixels - 20Mbytes

		// Read Image and Write to Memory
		Image_Read >> red;
		Image_Read >> green;
		Image_Read >> blue;

		// Write to new Images
		Image_write << red << " " << green << " " << blue << " " << endl;
	}


	//  Close Images
	Image_Read.close();
	Image_write.close();





	return 0;

}