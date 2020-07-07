#pragma once

#include "render_commands.h"
#include "../log.h"
#include "../ref.h"
#include "entity.h"

extern Log* gLog;

class Renderer
{
public: 
	static void BeginScene(); 

	static void EndScene();

	static void Submit(Ref<Entity> entity);

	static inline std::vector<Ref<Entity>> GetEntities(){
		return sEntities;
	}

private:
	static std::vector<Ref<Entity>> sEntities;
};

