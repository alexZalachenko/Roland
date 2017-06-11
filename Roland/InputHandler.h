#pragma once
class IInputReceiverEntity;
#include <vector>

class InputHandler
{
public:
	void HandleMouseMovementInput(double p_newPositionX, double p_newPositionY);
	void HandleKeyboardInput(int p_key, int p_action);
	void RegisterInputReceiver(IInputReceiverEntity* p_newEntity)
	{
		c_receivers.push_back(p_newEntity);
	}
	static InputHandler* Instance();
	~InputHandler() {};

private:
	InputHandler() {};
	static InputHandler* c_instance;
	std::vector<IInputReceiverEntity*> c_receivers;
};

