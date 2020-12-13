#pragma once
#include "../../ref.h"
#include "../../shader.h"

class abstractShaderFactory
{
public:
	virtual Ref<Shader> loadShader() = 0;
};

