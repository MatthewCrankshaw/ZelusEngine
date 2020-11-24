#pragma once

#include "render_commands.h"
#include "../log.h"
#include "../entity_component_manager.h"
#include "../ref.h"
#include "entity.h"

extern Log* gLog;
extern EntityComponentManager* gECM;

class Renderer
{
public: 
	static void BeginScene(); 

	static void EndDeferredScene();

	static void EndScene();

	static void Submit(Ref<Entity> entity);

	static inline std::vector<Ref<Entity>> GetEntities(){
		
	}

private:
};

