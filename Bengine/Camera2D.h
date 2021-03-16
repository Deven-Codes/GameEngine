#pragma once

#include "glm/ext.hpp"
#include <glm/glm.hpp> // for vec2, vec3, vec4, mat4 etc.
#include <glm/gtc/matrix_transform.hpp> // for glm::ortho "this fuction will let us build orthographic projection matrix"

//We'll be using orthographic projection matrix to map world space coordinates to normalized device coordinates



namespace Bengine {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		//initilaizing _screenWidth and _screenHeight
		void init(int screenWidth, int screenHeight);

		//Update matrix is needed
		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		//setters

		//set camera position 
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }

		//set scale
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

		//getters

		//get posiition of the camera
		glm::vec2 getPosition() { return _position; }

		//get scaling factor
		float getScale() { return _scale; }

		//get camera matrix
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		int _screenWidth, _screenHeight; // camera screen width and height
		bool _needsMatrixUpdate; // flag for updating _cameraMatrix
		float _scale; // scaling factor
		glm::vec2 _position; // camera position
		glm::mat4 _cameraMatrix; // camera matrix
		glm::mat4 _orthoMatrix; // orthographic projection matrix
	};

}