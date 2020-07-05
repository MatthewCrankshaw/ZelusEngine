#pragma once
#include<string>
#include "renderable.h"
#include "transform.h"
#include "../shader.h"
#include "../ref.h"
#include "../shader_manager.h"

class Entity
{
public: 
	Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, Ref<Transform> transform);

	Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera);

	void Draw();
	void Update();

	inline Ref<Transform> GetTransform(){
		return mTransform;
	}

	inline std::string GetName(){
		return mName;
	}
	
private: 
	std::string mName;
	Ref<Transform> mTransform;
	Ref<Renderable> mRenderable;
	Ref<Camera> mCamera;
};

