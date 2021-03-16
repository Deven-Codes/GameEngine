#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>

#include "Bullet.h"

#include <Bengine/Bengine.h>
#include <Bengine/Window.h>
#include <Bengine/Sprite.h>
#include <Bengine/Error.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/GLTexture.h>
#include <Bengine/Camera2D.h>
#include <Bengine/SpriteBatch.h>
#include <Bengine/ResourceManager.h>
#include <Bengine/InputManager.h>
#include <Bengine/Timing.h>


//#include "ImageLoader.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

	

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();


	/*Private variables for SDL Window*/
	Bengine::Window _window;
	int _screenWidth;
	int _screenHeight;
	float _time;
	GameState _gameState;
	int _fps;
	float _maxFPS;

	//std::vector<Bengine::Sprite*> _sprites;
	//Sprite _sprite;

	std::vector<Bullet> _bullet;

	Bengine::GLSLProgram _colorProgram;
	//GLTexture _playerTexture;

	Bengine::Camera2D _camera;

	Bengine::SpriteBatch _spriteBatch;

	Bengine::InputManager _inputManager;

	Bengine::FpsLimiter _fpsLimiter;

};

