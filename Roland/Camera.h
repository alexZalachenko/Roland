#pragma once
#include "IEntity.h"

class Camera : public IEntity
{
public:
	Camera();
	~Camera();
	bool GetIsActive();
	void SetIsActive(bool p_isActive);

private :
	bool c_isActive;
	bool c_isPerspective;
	float c_near;
	float c_far;
	void SetPerspective(float a, float b);
	void SetParallel(float a, float b);
	void BeginDraw();
	void EndDraw();
};

