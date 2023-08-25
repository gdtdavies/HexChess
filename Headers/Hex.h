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

	std::vector<float> xcoords;
	std::vector<float> ycoords;
};


