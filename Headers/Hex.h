#pragma once
#include <vector>

class Hex {
public:

	//    2----3
	//   /      \
   //  1        4
	//	  \      /
	//    0----5    

	int id;
	float x_c, y_c;

	std::vector<float> xcoords;
	std::vector<float> ycoords;
};


