#include "Node.h"
#include "Entity.h"

Node::Node(Node* p_father, Entity* p_entity)
	:c_father(p_father),
	 c_entity(p_entity)
{
	if (p_father != nullptr)
		p_father->AddChildren(this);
}

Node::~Node()
{
	if (c_father != nullptr)
		c_father->RemoveChildren(this);
}

int Node::AddChildren(Node* p_children)
{
	if (p_children != nullptr)
		c_children.push_back(p_children);
}

/*remove the children if exists and return its position or -1 if it didn't existed*/
int Node::RemoveChildren(Node* p_children)
{
	if (p_children == nullptr)
		return;
	
	for (size_t t_index = 0; t_index < c_children.size; t_index++)
	{
		if (c_children[t_index] == p_children)
		{
			c_children.erase(c_children.begin() + t_index);
			return t_index;
		}
	}
	return -1;
}

/*if entity is valid set it as node entity and return true. Otherwise return false*/
bool Node::SetEntity(Entity* p_entity)
{
	if (p_entity != nullptr)
	{
		c_entity = p_entity;
		return true;
	}
	else
		return false;
}

Entity* Node::GetEntity()
{
	return c_entity;
}

Node* Node::GetFather()
{
	return c_father;
}

/*call every children draw method*/
void Node::Draw()
{
	if (c_entity != nullptr)
	{
		c_entity->BeginDraw();
		for (size_t t_index = 0; t_index < c_children.size; t_index++)
			c_children[t_index]->Draw();
		c_entity->EndDraw();
	}
	else
	{
		for (size_t t_index = 0; t_index < c_children.size; t_index++)
			c_children[t_index]->Draw();
	}
}
