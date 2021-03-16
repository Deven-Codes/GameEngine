#include "MainGame.h"


/*
* Initializes private variables
*/
MainGame::MainGame(): _screenWidth(1024),
					_screenHeight(680),
					_time(0),
					_gameState(GameState::PLAY),
					_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}

/*
* Destructor
*/
MainGame::~MainGame()
{

}

/*
* Initializes SDL subsystem
* Initializes Sprite object
* Runs the game
* 
*/
void MainGame::run()
{
	initSystems();

	//Initialize our sprite 
	//_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	
	/*_sprites.push_back(new Bengine::Sprite());
	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterLeft_Standing.png");

	_sprites.push_back(new Bengine::Sprite());
	_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterLeft_Standing.png");*/

	//Loading 1000 sprites Slowwwwwwwwwwwwwwwwwwwwwww
	/*for (int i = 0; i < 1000; i++) {
		_sprites.push_back(new Sprite());
		_sprites.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	}*/

	//This only return when the game ends
	gameLoop();
}

/*
* Initialize SDL and Set OpenGL window attributes "SDL_GL_SetAttribute()"
* Create SDL Window with OpenGL Context 
* Initialize GLEW and set glClearColor()
*/
void MainGame::initSystems()
{
	/*
	* Initialize bengine
	*/
	Bengine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	/*
	* Initialize Shaders
	*/
	initShaders();

	/*
	 * Initialize Sprite Batch 
	 */
	_spriteBatch.init();

	/* 
	* Initialize fps limtier
	*/
	_fpsLimiter.init(_maxFPS);
}

/*
* Compile shaders and link them
*/
void MainGame::initShaders()
{
	/*
	* Compiling Vertex Shader and Fragment Shader from files
	*/
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");

	/*
	* Adding vertexPosition as Attribute (binding attribute location) 
	*/
	_colorProgram.addAttribute("vertexPosition");
	/*
	* Adding vertexColor as Attribute (binding attribute color)
	*/
	_colorProgram.addAttribute("vertexColor");

	/*
	* Adding vertexUV as Attribute (binding attribute UV or "texture coordinate")
	*/
	_colorProgram.addAttribute("vertexUV");

	/*
	* Linking shaders
	*/
	_colorProgram.linkShaders();

	
}

void MainGame::gameLoop()
{
	/*
	* Main game loop which will run until _gameState == EXIT
	*/
	while (_gameState != GameState::EXIT) {

		_fpsLimiter.begin();

		/*
		* Process user inputs
		*/
		processInput();

		/*
		 * increament _time 
		 */
		_time += 0.01f;

		//update all bullets
		for (int i = 0; i < _bullet.size(); ) {
			if (_bullet[i].update()) {
				_bullet[i] = _bullet.back();
				_bullet.pop_back();
			}
			else {
				i++;
			}
		}

		_camera.update();

		/*
	 	 * Clear buffer and Draw sprite
		 */
		drawGame();

		static int frameCounter = 0;
		frameCounter++;

		_fps = _fpsLimiter.end();

		if (frameCounter == 10000) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

			
	}
}

void MainGame::processInput()
{
	/*
	 * SDL_Event: A union that contains structures for the different event types. 
	 */
	SDL_Event evnt;

	const float CAMERASPEED = 5.0f;
	const float SCALESPEED = 0.1f;

	/*
	 * SDL_PollEvent(): Use this function to poll for currently pending events. 
	 */
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;

		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_s)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERASPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_w)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERASPEED));
	}

	if (_inputManager.isKeyPressed(SDLK_d)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERASPEED, 0.0));
	}

	if (_inputManager.isKeyPressed(SDLK_a)) {
		_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERASPEED, 0.0));
	}

	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() + SCALESPEED);
	}

	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() - SCALESPEED);
	}
	
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		//std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;

		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullet.emplace_back(playerPosition, direction, 1.0f, 1000);

	}
}

void MainGame::drawGame()
{
    /*
	 * glClearColor(r, g, ,b, a): specifies red, green, blue and alpha values
	 *							 used by glClear() to clear color buffer
	 *							 Values specified by glClearColor are clamped to the range [0,1].
	 */
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	/*
	 * glClearDepth(): Specifies the depth value used by glClear()
	 *				  to clear the depth buffer.
	 *				   Values specified by glClearDepth are clamped to the range [0,1].
	 * 
	 * Set base depth to 1.0
	 */
	glClearDepth(1.0);

	/*
	 * glClear(): sets bitplane area of window to value previously seleted by
	 *			 glClearColor, glClearDepth, and glClearStencil.
	 *			
	 * 
	 * glClear() takes a single argument that is the bitwise OR of several values indicating which buffer is to be cleared.
	 * 
	 * Clear the color and depth buffer
	 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*
	 * Enables the vertext attributes
 	 */
	_colorProgram.use();

	//We are using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	
	
	//Get uniform location 
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	//Tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set the constantly changing time variable
	/*GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);*/

	//Set the camera matrix
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	/*
	 * Draw sprite to the screen
	 
	 for (int i = 0; i < _sprites.size(); i++) {
		_sprites[i]->draw();
	 }

	*/

	_spriteBatch.begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture texture = Bengine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	Bengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	/*for (int i = 0; i < 1000; i++) {
		_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
		_spriteBatch.draw(pos + glm::vec4(50.0f, 0.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);
	}*/
	_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	//_spriteBatch.draw(pos + glm::vec4(50.0f, 0.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);

	for (int i = 0; i < _bullet.size(); i++) {
		_bullet[i].draw(_spriteBatch);
	}

	_spriteBatch.end();

	_spriteBatch.renderBatch();

	//Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	/*
	 * Disables the vertext attributes
 	 */
	_colorProgram.unuse();
	
	/*
	 * Swap our buffer and draw everything to the screen 
	 */
	_window.swapBuffer();
}
