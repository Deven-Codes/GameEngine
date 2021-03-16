#include "InputManager.h"

namespace Bengine {

	InputManager::InputManager() : _mouseCoords(0.0f)
	{

	}

	InputManager::~InputManager() {

	}

	void InputManager::pressKey(unsigned int keyID) {
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		// _keyMap[keyID] : will created the element associated with keyID and return true or false randomly
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end()) {
			return it->second;
		}
		else {
			return false;
		}
	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}
}