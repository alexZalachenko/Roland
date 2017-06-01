#pragma once

enum EntityTypes
{
	CameraType, 
	ImageType,
	LightType,
	MeshType,
	TransformType
};

class IEntity
{

public:
	IEntity(EntityTypes p_entityType)
		: c_entityType(p_entityType)
	{

	}
	EntityTypes GetEntityType()
	{
		return c_entityType;
	}
	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;

private :
	EntityTypes c_entityType;
};

