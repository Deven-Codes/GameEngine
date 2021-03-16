#include "Camera2D.h"
namespace Bengine {
	Camera2D::Camera2D() : _screenWidth(500),
		_screenHeight(500),
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f), // setting to identity matrix
		_orthoMatrix(1.0f), // setting to identity matrix
		_scale(1.0f), 
		_needsMatrixUpdate(1)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		
		/*
		 *	glOrtho describes a transformation that produces a parallel projection.
		 *	The current matrix(see glMatrixMode) is multiplied by this matrix and the result replaces the current matrix,
		 *	as if glMultMatrix were called with the following matrix as its argument :

		 *	| 2/(right - left) | 0                | 0                     | tx |
		 *	| 0                | 2/(top - bottom) | 0                     | ty |
		 *	| 0                | 0                | -2/(farVal - nearVal) | tz |
		 *	| 0                | 0                | 0                     | 1  |

		 *	where
		 *	tx = -right + left /right - left

		 *	ty = -top + bottom /top - bottom

		 *	tz = -farVal + nearVal /farVal - nearVal
		 */
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate) {
			// translating matrix will move object around by changing camera matrix
			// for the object to move in one dir we'll be moving the view port in opposite direction
			// by making a vec3 translate (-_position.x, -_position.y, 0.0f) of negative transition 
			// so when camera viewport moves to the right everything goes to the left

			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate); 

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(_cameraMatrix, scale);

			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {

		//Invert y coordinates
		screenCoords.y = _screenHeight - screenCoords.y;

		// origin of world coordinates is at centre of the screen 
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);

		// Scale the coordinate
		screenCoords /= _scale;

		//Translate the camera position 
		screenCoords += _position;

		return screenCoords;
	}
}