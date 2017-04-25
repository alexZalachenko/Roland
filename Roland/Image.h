#pragma once
#include "IEntity.h"
class IImageResource;

class Image : public IEntity
{
public:
	Image();
	~Image();
	void BeginDraw() override;
	void EndDraw() override;
	void SetImageResource(IImageResource* p_imageResource)
	{
		c_imageResource = p_imageResource;
	}
	IImageResource* GetImageResource() { return c_imageResource; }

private:
	IImageResource* c_imageResource;
};

