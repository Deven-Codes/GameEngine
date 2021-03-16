#include "Window.h"

namespace Bengine {
	Window::Window()
	{

	}

	Window::~Window()
	{

	}

	int Window::create(std::string windoName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		/*
		 * Setting up Flags
		 */
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN; // set window to hidden 
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP; // set window to fullscreen 
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS; // set window to borderless
		}


		/*
		* SDL_WINDOW_OPENGL: Window usable with OpenGL context.
		*                    Creating an Window pointer to support OpenGL
		*/
		_sdlWindow = SDL_CreateWindow(windoName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr) {
			fatalError("SDL window could not created!");
		}

		/*
		* SDL_GL_CreateContext(): Use this function to create an OpenGL context for use with an OpenGL window, and make it current
		*
		* SDL_GLContext: An enumeration of OpenGL context configuration flags.
		*/
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr) {
			fatalError("SDL_GL context could not be created!");
		}


		/*
		* glewInit(): This function returns unsigned int (GLenum)
		*			  returns GLEW_OK on success
		*/
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Could not initialize GLEW!");
		}

		//Print OpenGL Version
		printf("**** OpenGL Version: %s ****\n", glGetString(GL_VERSION));

		//Set VSYNC
		SDL_GL_SetSwapInterval(0);

		//Enacle alpha blending 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		/*
		 * Swap our buffer and draw everything to the screen
		 * SDL_GL_SwapWindow(): Use this function to update a window with OpenGL rendering.
		 */
		SDL_GL_SwapWindow(_sdlWindow);
	}
}