#pragma once
#include<string>
#include "renderable.h"
#include "transform.h"
#include "../shader.h"
#include "../ref.h"

class Entity
{
public: 
	Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, Ref<Transform> transform);

	void Draw();
	void Update();

private: 
	std::string mName;
	Ref<Renderable> mRenderable;
	Ref<Camera> mCamera;
	Ref<Transform> mTransform;

};

