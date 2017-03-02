#pragma once
#include <vector>
class Entity;

class Node
{

public:
	Node(Node* p_father, Entity* p_entity);
	~Node();
	bool	SetEntity(Entity* p_entity);
	Entity* GetEntity();
	Node*	GetFather();
	int		AddChildren(Node* p_children);
	int		RemoveChildren(Node* p_children);
	void	Draw();

private:
	Entity* c_entity;
	std::vector<Node*> c_children;
	Node* c_father;
};

