#pragma once
#include "PerspectiveCamera.h"
#include "IInputReceiverEntity.h"

class FPSCamera : public PerspectiveCamera, public IInputReceiverEntity
{
public:
	FPSCamera(float p_far, float p_near, float p_fov, float p_width, float p_height, float p_startingMouseX, float p_startingMouseY);
	virtual ~FPSCamera();
	virtual glm::mat4 GetViewMatrix() override;
	void ReceiveKeyboardInput(int p_key, int p_action) override;
	void ReceiveMouseMovementInput(double p_newPositionX, double p_newPositionY) override;

private:
	float c_lastMousePositionX = 0;
	float c_lastMousePositionY = 0;
	//rotation around y in radians
	float c_yaw = 0;
	//rotation around x in radians
	float c_pitch = 0;
	//position
	glm::vec3 c_position;
	const float c_movementSpeed = 0.5f;
	const float c_rotationSpeed = 0.001f;
};

