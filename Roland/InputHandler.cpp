#include "InputHandler.h"
#include "IInputReceiverEntity.h"

void InputHandler::HandleMouseMovementInput(double p_newPositionX, double p_newPositionY)
{
	for each (IInputReceiverEntity* t_receiver in c_receivers)
		t_receiver->ReceiveMouseMovementInput(p_newPositionX, p_newPositionY);
}

void InputHandler::HandleKeyboardInput(int p_key, int p_action)
{
	for each (IInputReceiverEntity* t_receiver in c_receivers)
		t_receiver->ReceiveKeyboardInput(p_key, p_action);
}
InputHandler* InputHandler::c_instance = 0;

InputHandler* InputHandler::Instance()
{
	if (c_instance == nullptr)
		c_instance = new InputHandler();
	return c_instance;
}


