#pragma once

template <class T>
class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();
	void SetIdentity();

private:
	T c_matrix[4][4];
};

