#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include "Vec3.h"

class Calcs3D
{
public:
	Calcs3D();
	
	Vec3 Cross(Vec3 vVector1, Vec3 vVector2);

	Vec3 Vector(Vec3 Point1, Vec3 Point2);

	float Magnitude(Vec3 vNormal);

	Vec3 Normalize(Vec3 vNormal);

	Vec3 Normal(Vec3 Triangle[]);

	float PlaneDistance(Vec3 vNormal, Vec3 vPoint);

	bool IntersectedPlane(Vec3 vPoly[], Vec3 vLine[], Vec3 &vNormal, float &originDistance);

	float Dot(Vec3 vVector1, Vec3 vVector2);

	double AngleBetweenVectors(Vec3 vVector1, Vec3 vVector2);

	Vec3 IntersectionPoint(Vec3 vNormal, Vec3 vLine[], double distance);

	bool InsidePolygon(Vec3 vIntersection, Vec3 Poly[], long verticeCount);

	bool IntersectedPolygon(Vec3 vPoly[], Vec3 vLine[], int verticeCount);

};

