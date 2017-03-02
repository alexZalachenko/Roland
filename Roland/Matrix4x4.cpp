#include "Matrix4x4.h"

template <typename T>
Matrix4x4<T>::Matrix4x4()
{
}

template <typename T>
Matrix4x4<T>::~Matrix4x4()
{
}

template <typename T>
void Matrix4x4<T>::SetIdentity()
{
	for (size_t t_index1 = 0; t_index1 < c_matrix[]; t_index1++)
	{
		for (size_t t_index2 = 0; t_index2 < c_matrix[][]; t_index2++)
			c_matrix[t_index1][t_index2] = (T)0;
	}
	c_matrix[0][0] = (T)1;
	c_matrix[1][1] = (T)1;
	c_matrix[2][2] = (T)1;
	c_matrix[3][3] = (T)1;
}
