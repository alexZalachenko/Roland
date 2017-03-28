#pragma once
#include <vector>
class IEntity;

class Node
{

public:
	Node();
	Node(Node* p_father, IEntity* p_IEntity);
	~Node();
	bool		SetIEntity(IEntity* p_IEntity);
	IEntity*	GetIEntity();
	void		Setfather(Node* p_father) { c_father = p_father; }
	Node*		GetFather();
	int			AddChildren(Node* p_children);
	int			RemoveChildren(Node* p_children);
	void		Draw();

private:
	IEntity* c_IEntity;
	std::vector<Node*> c_children;
	Node* c_father;
	bool c_removeFromFather;
};

