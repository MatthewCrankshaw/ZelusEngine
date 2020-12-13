#include "gl_renderable_factory.h"

Ref<Renderable> GLRenderableFactory::CreateCube() const
{
	Ref<Renderable> cube(new GLCube());
	return cube;
}

Ref<Renderable> GLRenderableFactory::CreateModel(std::string path) const
{
	Ref<GLRenderable> model(new GLModel(path));
	return model;
}

Ref<Renderable> GLRenderableFactory::CreateRectangle() const
{
	Ref<GLRenderable> rectangle(new GLRectangle());
	return rectangle;
}
