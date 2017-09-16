#include "Calcs3D.h"

Calcs3D::Calcs3D()
{
}


Vec3 Calcs3D::Cross(Vec3 vVector1, Vec3 vVector2)
{
	Vec3 Normal;
	Normal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

	Normal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

	Normal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return Normal;										
}


Vec3 Calcs3D::Vector(Vec3 Point1, Vec3 Point2)
{
	Vec3 vVector;

	vVector.x = 0;
	vVector.y = 0;
	vVector.z = 0;
														
	vVector.x = Point1.x - Point2.x;					
	vVector.y = Point1.y - Point2.y;					
	vVector.z = Point1.z - Point2.z;					

	return vVector;										
}


float Calcs3D::Magnitude(Vec3 vNormal)
{
	return (float)sqrt((vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
}


Vec3 Calcs3D::Normalize(Vec3 vNormal)
{
	float magnitude = Magnitude(vNormal);				

	vNormal.x /= magnitude;							
	vNormal.y /= magnitude;								
	vNormal.z /= magnitude;																					

	return vNormal;										
}


Vec3 Calcs3D::Normal(Vec3 Triangle[])
{													
	Vec3 Vector1 = Vector(Triangle[2], Triangle[0]);
	Vec3 Vector2 = Vector(Triangle[1], Triangle[0]);

	Vec3 vNormal = Cross(Vector1, Vector2);

	vNormal = Normalize(vNormal);					
	return vNormal;										
}


float Calcs3D::PlaneDistance(Vec3 vNormal, Vec3 vPoint)
{
	float distance = 0;									
	distance = -((vNormal.x * vPoint.x) + (vNormal.y * vPoint.y) + (vNormal.z * vPoint.z));

	return distance;									
}

bool Calcs3D::IntersectedPlane(Vec3 vPoly[], Vec3 vLine[], Vec3 &vNormal, float &originDistance)
{
	float distance1 = 0, distance2 = 0;						

	vNormal = Normal(vPoly);							
	originDistance = PlaneDistance(vNormal, vPoly[0]);


	distance1 = ((vNormal.x * vLine[0].x) +					
		(vNormal.y * vLine[0].y) +					
		(vNormal.z * vLine[0].z)) + originDistance;	

	distance2 = ((vNormal.x * vLine[1].x) +					
		(vNormal.y * vLine[1].y) +					
		(vNormal.z * vLine[1].z)) + originDistance;	

	if (distance1 * distance2 >= 0)			
		return false;						

	return true;							
}


float Calcs3D::Dot(Vec3 vVector1, Vec3 vVector2)
{
	return ((vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z));
}

double Calcs3D::AngleBetweenVectors(Vec3 vVector1, Vec3 vVector2)
{

	float dotProduct = Dot(vVector1, vVector2);

	float vectorsMagnitude = Magnitude(vVector1) * Magnitude(vVector2);

	double angle = acos(dotProduct / vectorsMagnitude);

	if (_isnan(angle))
		return 0;

	return(angle);
}

Vec3 Calcs3D::IntersectionPoint(Vec3 vNormal, Vec3 vLine[], double distance)
{
	Vec3 vPoint, vLineDir;

	vPoint.x = 0;
	vPoint.y = 0;
	vPoint.z = 0;

	vLineDir.x = 0;
	vLineDir.y = 0;
	vLineDir.z = 0;

	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	vLineDir = Vector(vLine[1], vLine[0]);		
	vLineDir = Normalize(vLineDir);				
												
	Numerator = -(vNormal.x * vLine[0].x +		
		vNormal.y * vLine[0].y +
		vNormal.z * vLine[0].z + distance);

	Denominator = Dot(vNormal, vLineDir);		

	if (Denominator == 0.0)			
		return vLine[0];

	dist = Numerator / Denominator;															

	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;						
}


bool Calcs3D::InsidePolygon(Vec3 vIntersection, Vec3 Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.9999;		
	double Angle = 0.0;						
	Vec3 vA, vB;

	for (int i = 0; i < verticeCount; i++)		
	{
		vA = Vector(Poly[i], vIntersection);	
												
		vB = Vector(Poly[(i + 1) % verticeCount], vIntersection);

		Angle += AngleBetweenVectors(vA, vB);	
	}

	if (Angle >= (MATCH_FACTOR * (2.0 * M_PI)))	
		return true;							

	return false;
}


bool Calcs3D::IntersectedPolygon(Vec3 vPoly[], Vec3 vLine[], int verticeCount)
{
	Vec3 vNormal;
	vNormal.x = 0;
	vNormal.y = 0;
	vNormal.z = 0;

	float originDistance = 0;

	if (!IntersectedPlane(vPoly, vLine, vNormal, originDistance))
		return false;

	Vec3 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	if (InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;

	return false;								
}

