#include "stdafx.h"
#include "VecMath.h"


/*
Triangle::Triangle(float verts[9])
{
	this->verts[0] = Vector3(verts[0], verts[1], verts[2]);
	this->verts[1] = Vector3(verts[3], verts[4], verts[5]);
	this->verts[2] = Vector3(verts[6], verts[7], verts[8]);
}
*/

Triangle::Triangle()
{
	this->verts[0] = Vector3();
	this->verts[1] = Vector3();
	this->verts[2] = Vector3();
}


Mesh::Mesh()
{

}

void MultiplyMatrix(const Vector3& i, Vector3& o, Matrix4x4 mat)
{
	o.x = i.x * mat.mat[0][0] + i.y * mat.mat[0][1] + i.z * mat.mat[0][2] + 1.0f  * mat.mat[0][3];
	o.y = i.x * mat.mat[1][0] + i.y * mat.mat[1][1] + i.z * mat.mat[1][2] + 1.0f  * mat.mat[1][3];
	o.z = i.x * mat.mat[2][0] + i.y * mat.mat[2][1] + i.z * mat.mat[2][2] + 1.0f  * mat.mat[2][3];
	float w = i.x * mat.mat[3][0] + i.y * mat.mat[3][1] + i.z * mat.mat[3][2] + 1.0f * mat.mat[3][3];

	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
}


Vector3 RotatePointX(Vector3 point3, float angle)
{
	float theta = angle * 0.017453f;

	Matrix4x4 rotationMat;
	rotationMat.mat[0][0] = 1.0f;
	rotationMat.mat[1][1] = cosf(theta);
	rotationMat.mat[2][2] = cosf(theta);
	rotationMat.mat[1][2] = sinf(theta);
	rotationMat.mat[1][2] = -sinf(theta);
	rotationMat.mat[3][3] = 1.0f;

	Vector3 rotated(0, 0, 0);
	MultiplyMatrix(point3, rotated, rotationMat);

	return Vector3(rotated.x, rotated.y, rotated.z);

}

Vector3 RotatePointY(Vector3 point3, float angle)
{
	float theta = angle * 0.017453f;

	Matrix4x4 rotationMat;
	rotationMat.mat[0][0] = cosf(theta);
	rotationMat.mat[1][1] = 1.0f;
	rotationMat.mat[2][2] = cosf(theta);
	rotationMat.mat[2][0] = sinf(theta);
	rotationMat.mat[0][2] = -sinf(theta);
	rotationMat.mat[3][3] = 1.0f;

	Vector3 rotated(0, 0, 0);
	MultiplyMatrix(point3, rotated, rotationMat);

	return Vector3(rotated.x, rotated.y, rotated.z);
}

Vector3 RotatePointZ(Vector3 point3, float angle)
{
	float theta = angle * 0.017453f;

	Matrix4x4 rotationMat;
	rotationMat.mat[0][0] = cosf(theta);
	rotationMat.mat[1][1] = cosf(theta);
	rotationMat.mat[2][2] = 1.0f;
	rotationMat.mat[1][0] = sinf(theta);
	rotationMat.mat[0][1] = -sinf(theta);
	rotationMat.mat[3][3] = 1.0f;

	Vector3 rotated(0, 0, 0);
	MultiplyMatrix(point3, rotated, rotationMat);

	return Vector3(rotated.x, rotated.y, rotated.z);

}


Vector2 ProjectedPoint(Vector3 point3, float viewAngle, float aspectRatio)
{
	float near = 0.5f;
	float far = 1000.0f;
	float rtan = 1.0f / tanf(viewAngle*0.5f / 180.0f * 3.1415f);

	Matrix4x4 projectionMat;
	projectionMat.mat[0][0] = aspectRatio*rtan;
	projectionMat.mat[1][1] = rtan;
	projectionMat.mat[2][2] = far / (far - near);
	projectionMat.mat[3][2] = -far*near / (far - near);
	projectionMat.mat[2][3] = 1.0f;

	Vector3 projected(0, 0, 0);
	MultiplyMatrix(point3, projected, projectionMat);

	return Vector2(projected.x, projected.y);

}