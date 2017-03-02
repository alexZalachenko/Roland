#pragma once
#include "Entity.h"

class Camera : public Entity
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

