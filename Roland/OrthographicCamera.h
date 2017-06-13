#pragma once
#include "Camera.h"
#include <string>

class OrthographicCamera : public Camera
{

public:
	OrthographicCamera(float p_near, float p_far, float p_left, float p_right, float p_top, float p_bottom);
	virtual ~OrthographicCamera();
	void DisplayEntityData(std::string p_tab) override;
	void BeginDraw() override;
	void EndDraw() override;

private:
	float c_near;
	float c_far;
	float c_left;
	float c_right;
	float c_top;
	float c_bottom;
};

