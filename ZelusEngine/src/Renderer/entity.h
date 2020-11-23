#pragma once
#include<string>
#include "gl_api/gl_renderable.h"
#include "transform.h"
#include "../shader.h"
#include "../ref.h"
#include "../shader_manager.h"

class Entity
{
public: 
	Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, Ref<Transform> transform, bool deferredShading = true);

	Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, bool deferredShading = true);

	void Draw();
	void Update();

	inline Ref<Transform> GetTransform(){
		return mTransform;
	}

	inline std::string GetName(){
		return mName;
	}

	inline bool IsDeferredShading(){
		return mDeferredShading;
	}
	
private: 
	std::string mName;
	Ref<Transform> mTransform;
	Ref<Renderable> mRenderable;
	Ref<Camera> mCamera;

	bool mDeferredShading;
};

