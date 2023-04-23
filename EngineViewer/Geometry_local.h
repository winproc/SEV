#pragma once
#include <vector>

class Point {

public:
	int x;
	int y;

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

std::vector<Point> ComputeLocus(int Radius, int MaxPoints, int Inverted);
