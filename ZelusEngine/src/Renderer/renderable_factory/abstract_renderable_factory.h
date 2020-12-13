#pragma once
#include <string>

#include "../../ref.h"
#include "../renderable.h"

class AbstractRenderableFactory
{
public:
	virtual Ref<Renderable> CreateCube() const = 0;
	virtual Ref<Renderable> CreateModel(std::string path) const = 0;
	virtual Ref<Renderable> CreateRectangle() const = 0;
};

