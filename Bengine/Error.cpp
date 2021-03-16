#include "Error.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib> //for exit()

namespace Bengine {
	void fatalError(std::string errorString)
	{
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit.....";
		int tmp;
		std::cin >> tmp;
		SDL_Quit(); // Quitting SDL Subsystem
		exit(9); // exit the game
	}
}