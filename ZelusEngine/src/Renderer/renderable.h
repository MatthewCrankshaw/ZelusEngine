#pragma once
#include "../ref.h"
#include "../camera.h"
class Renderable
{
public:
	virtual void Draw(const Ref<Camera> camera) = 0;
	virtual void Update() = 0;
};

