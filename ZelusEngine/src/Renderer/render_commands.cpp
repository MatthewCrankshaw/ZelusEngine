#include "render_commands.h"
#include "gl_api/opengl_renderer_api.h"


RendererAPI* RenderCommands::sAPI = new OpenGLRendererAPI;