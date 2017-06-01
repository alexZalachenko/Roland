#include "Node.h"
#include "IEntity.h"

Node::Node()
	:c_father(nullptr),
	c_IEntity(nullptr),
	c_removeFromFather(true)
{
	c_children = std::vector<Node*>();
}

Node::Node(Node* p_father, IEntity* p_IEntity)
	:c_father(p_father),
	 c_IEntity(p_IEntity),
	c_removeFromFather(true)
{
	c_children = std::vector<Node*>();
	if (p_father != nullptr)
		p_father->AddChildren(this);
}

Node::~Node()
{
	if (c_father != nullptr && c_removeFromFather)
		c_father->RemoveChildren(this);
		
	for each (Node* t_node in c_children)
	{
		t_node->c_removeFromFather = false;
		delete t_node;
	}
		
}

int Node::AddChildren(Node* p_children)
{
	if (p_children != nullptr)
	{
		c_children.push_back(p_children);
		return c_children.size() - 1;
	}
	else
		return -1;
}

/*remove the children if exists and return its position or -1 if it didn't existed*/
int Node::RemoveChildren(Node* p_children)
{
	if (p_children == nullptr)
		return -1;
	
	for (size_t t_index = 0; t_index < c_children.size(); ++t_index)
	{
		if (c_children[t_index] == p_children)
		{
			c_children.erase(c_children.begin() + t_index);
			return t_index;
		}
	}
	return -1;
}

/*if IEntity is valid set it as node IEntity and return true. Otherwise return false*/
bool Node::SetIEntity(IEntity* p_IEntity)
{
	if (p_IEntity != nullptr)
	{
		c_IEntity = p_IEntity;
		return true;
	}
	else
		return false;
}

IEntity* Node::GetIEntity()
{
	return c_IEntity;
}

Node* Node::GetFather()
{
	return c_father;
}

/*call every children draw method*/
void Node::Draw()
{
	if (c_IEntity != nullptr)
	{
		c_IEntity->BeginDraw();
		for (Node* t_children : c_children)
			t_children->Draw();
		c_IEntity->EndDraw();
	}
	else
	{
		for (Node* t_children : c_children)
			t_children->Draw();
	}
}

Node * Node::GetRoot()
{
	if (c_father != nullptr)
		return c_father->GetRoot();
	else
		return this;
}
