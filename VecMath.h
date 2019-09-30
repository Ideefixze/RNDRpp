#include "Vector3.h"
#include <vector>

class Triangle
{
public:
	Vector3 verts[3];
	Triangle(Vector3 a, Vector3 b, Vector3 c) :verts{a, b, c} {};
	Triangle();
};

class Mesh
{
public:
	std::vector<Triangle> triangles;
	Mesh(std::vector<Triangle> tris) :triangles{ tris } {};
	Mesh();
};

struct Matrix4x4
{
	float mat[4][4] = { 0 };
};


Vector2 ProjectedPoint(Vector3 point3, float viewAngle, float aspectRatio);
void MultiplyProjectionMatrix(const Vector3& i, Vector3& o, Matrix4x4 mat);
Vector3 RotatePointX(Vector3 point3, float angle);
Vector3 RotatePointZ(Vector3 point3, float angle);
Vector3 RotatePointY(Vector3 point3, float angle);

