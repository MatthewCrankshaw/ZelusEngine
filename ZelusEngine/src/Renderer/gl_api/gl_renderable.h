#pragma once
#include<glm/glm.hpp>

#include "../renderable.h"

class GLRenderable : public Renderable
{
protected:
	GLuint mVao;
	GLuint mVbo;
	GLuint mEbo;

public:
	virtual void Draw(const Ref<Camera> camera) = 0;
	virtual void Update() = 0;
};