#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "pixel.h"

std::vector<Pixel> pixel_list;

void read_file_data(std::string filename, std::vector<Pixel> &pixel_list) {
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        Pixel p;

        std::string x_str, y_str, r_str, g_str, b_str;

        std::getline(ss, x_str, ',');
        std::getline(ss, y_str, ',');
        std::getline(ss, r_str, ',');
        std::getline(ss, g_str, ',');
        std::getline(ss, b_str, ',');

        p.x = std::stoi(x_str);
        p.y = std::stoi(y_str);
        p.r = std::stof(r_str);
        p.g = std::stof(g_str);
        p.b = std::stof(b_str);

    
        pixel_list.push_back(p);
    }
}

void avg_colors(std::vector<Pixel>& pixel_list)
{
  
	float total_r = 0.0f, total_g = 0.0f, total_b = 0.0f;
	int pixel_count = pixel_list.size();
	for(const auto& pixel : pixel_list) {

        	total_r += pixel.r;
        	total_g += pixel.g;
        	total_b += pixel.b;
	}
		

	if(pixel_list.size() > 0) {
	   float avg_r = total_r / pixel_list.size();
	   float avg_g = total_g / pixel_list.size();
	   float avg_b = total_b / pixel_list.size();


	   std::cout << "Average R: " << avg_r << std::endl;
	   std::cout << "Average G: " << avg_g << std::endl;
	   std::cout << "Average B: " << avg_b << std::endl;
	} else { 
	   std::cout << "No pixels to process." << std::endl;
	}
}


void vertical_flip(std::vector<Pixel>& pixel_list)
{

	int y_length = 256;  // y-length 
	int x_length = 512; // x-length

	for(int y = 0; y < y_length / 2; ++y) {
        	for (int x = 0; x < x_length; ++x) {
		    std::swap(pixel_list[y * x_length + x], pixel_list[(y_length - 1 - y) * x_length + x]);

        }

    }

}

void save_image_flip(const std::vector<Pixel>& pixel_list, const std::string& output_file) 
{
    std::ofstream output(output_file);

	if(output) {
	for(const auto& pixel : pixel_list) {
            output << pixel.x << "," << pixel.y << ","
                   << pixel.r << "," << pixel.g << "," << pixel.b << "\n";
        }

        output.close();

    } else {
 
	std::cerr << "Could not open output file for writing." << std::endl;
    
	}
}
 
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_name>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    read_data(filename);
    std::cout << "Successfully loaded " << pixel_list.size() << " pixels from " << filename << "\n";

    read_file_data(pixel_list);
    avg_colors(pixel_list);
    vertical_flip(pixel_list);
    save_image_flip("flipped.dat", pixel_list);

    return 0;
}
