#pragma once
#include "Camera.h"
#include <string>

class PerspectiveCamera : public Camera
{

public:
	PerspectiveCamera(float p_far, float p_near, float p_fov, float p_width, float p_height);
	virtual ~PerspectiveCamera();
	void BeginDraw() override;
	void EndDraw() override;
	void DisplayEntityData(std::string p_tab) override;

private:
	float c_far;
	float c_near;
	float c_fov;
	float c_width;
	float c_height;
};

