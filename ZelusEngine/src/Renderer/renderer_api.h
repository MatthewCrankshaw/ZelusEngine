#pragma once

#include<glm/glm.hpp>
#include<glad/glad.h>

#include "renderable.h"
#include "transform.h"
#include "shader.h"
#include "../ref.h"
#include "../camera.h"
#include "texture.h"


class RendererAPI
{
public:
	enum class API { NONE = 0, OPENGL = 1};

	virtual void SetClearColour(const glm::vec4& colour) = 0; 
	virtual void Clear() = 0; 
	virtual void CullBackFaces() = 0;
	virtual void EnableDepthTest() = 0;
	virtual void DrawIndexed(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader, Ref<Camera> camera) = 0;
	virtual void SetSingleTexture(Ref<Shader> shader, Ref<Texture> texture) = 0;
	virtual void SetCubeMapTexture(Ref<Shader> shader, Ref<Texture> texture) = 0;

	inline static API GetAPI() { return sAPI; }

private:
	static API sAPI;
};

