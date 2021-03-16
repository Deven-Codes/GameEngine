#include "Bengine.h"

namespace Bengine {
	int init()
	{
		//initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		/*
		* SDL_GL_DOUBLEBUFFER : Use this function to set an OpenGL window attribute before window creation.
		*						Instead of drawing and clearing single window
		*						SDL_GL_DOUBLEBUFFER will give us 2 windows so we can draw on one window while other
		*						window is being cleared and vice versa. This keeps the window from flikering
		*
		* SDL_GL_SetAttribute(): This function set an OpenGL window attribute before window creation
		*						 attr: the OpenGL attribute to set; see Remarks for details
		*                        value: the desired value for the attribute
		*/
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}