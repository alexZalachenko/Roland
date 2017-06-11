#pragma once
class IInputReceiverEntity
{
public:
	IInputReceiverEntity() {};
	virtual ~IInputReceiverEntity() {};
	virtual void ReceiveKeyboardInput(int p_key, int p_action) = 0;
	virtual void ReceiveMouseMovementInput(double p_newPositionX, double p_newPositionY) = 0;
};

