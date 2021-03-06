// JPEC.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <streambuf>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

const char hx[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

std::string c2h(char c) {
	return "";
}

static std::vector<char> ReadAllBytes(char const* filename)
{
	ifstream ifs(filename, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

int main()
{
	//string path = "C:\\Users\\jadeon.sheppard\\Desktop\\benedict-cumberbatch7.jpg";
	string path = "C:\\Users\\jadeon.sheppard\\Desktop\\Jadeon.jpg"; 
	
	vector<char> data = ReadAllBytes(path.c_str());

	std::vector<char> out = vector<char>();
	out.reserve(data.size() * 2);

	for (int i = 0; i < data.size(); i++) {
		unsigned char v = data[i];
		char b = (v >> 4) & 0x0F;
		char s = v & 0x0F;

		out.push_back(hx[b]);
		out.push_back(hx[s]);
	}

	size_t imgMarker = 0;

	for (size_t i = 0; i < data.size(); i++) {
		if ((unsigned char)data[i] == 0xFF && (unsigned char)data[i + 1] == 0xC0){
			imgMarker = i;
			break;
		}
	}

	imgMarker += 2;
	while (data[imgMarker] == 0x0) {
		imgMarker++;
	}

	uint16_t width = 0;
	uint16_t height = 0;

	unsigned char b = data[imgMarker + 2];
	unsigned char s = data[imgMarker + 3];

	height  = (uint16_t)b * 256;
	height += (uint16_t)s;

	b = data[imgMarker + 4];
	s = data[imgMarker + 5];

	width = (uint16_t)b * 256;
	width += (uint16_t)s;

	cout << width << ", " << height;

	srand(time(0));

	double vv = 0.0;

	for (int i = imgMarker + 256 * 4; i < data.size() - 256 * 4; i += rand() % 4096 * 3) {
		//if (data[i] > 10)
		//vv = (vv * 0.01) + ((double)data[i] * 0.99);
		
		//data[i] = vv;

		/*int alg = rand() % 4;

		if (alg == 0) {
			data[i] &= 0xFE;
		}
		else if (alg == 1) {
			data[i] |= 3;
		}
		else if (alg == 2) {
			//data[i] += 1;
		}
		else if (alg == 3) {
			//data[i] /= 2;
		}
		*/
		data[i] = 0;
		//data[i] &= 0xFE;
//		data[i + 1] = 0x0;
	}


	ofstream outfile("output.jpg", ios::out | ios::binary);
	outfile.write(&data[0], data.size());
	outfile.close();

	cout << "\n\nDone";

	/*
	for (int i = 0; i < out.size(); i++) {
		cout << out[i];
	}*/

	/*
	char output[100];
	char hexOut[200];
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;

			for (int i = 0; i < 100; i++) {
				unsigned char v = output[i];
				char b = (v >> 4) & 0x0F;
				char s = v & 0x0F;

				hexOut[i * 2] = hx[b];
				hexOut[(i * 2) + 1] = hx[s];
			}

			cout << output;
		}
	}
	myReadFile.close();
	*/
	while (true) {

	}

    return 0;
}

