#include "Geometry_local.h"

std::vector<Point> ComputeLocus(int Radius, int MaxPoints, int Inverted) {
	std::vector<Point> ListOfPoints = {};

	float AngleStep = 6.28319 / MaxPoints;

	// Create a point for each angle step
	for (int Factor = 0; (Factor * AngleStep) < 6.28319; Factor++) {

		Point LocusPoint(0, Radius * Inverted);

		// Angle is negative to ensure a clockwise rotation
		float Angle = -Factor * AngleStep;

		// Perform Euclidean rotation
		float ResultX, ResultY;

		ResultX = LocusPoint.x * cosf(Angle) - LocusPoint.y * sinf(Angle);
		ResultY = LocusPoint.x * sinf(Angle) + LocusPoint.y * cosf(Angle);

		LocusPoint.x = ResultX;
		LocusPoint.y = ResultY;

		ListOfPoints.push_back(LocusPoint);

	}

	return ListOfPoints;
}