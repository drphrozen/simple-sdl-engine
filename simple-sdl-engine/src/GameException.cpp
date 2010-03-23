/*
 * GameException.cpp
 *
 *  Created on: 23/03/2010
 *      Author: drphrozen
 */

#include "GameException.h"

GameException::GameException(const string& message)
	: runtime_error(message) {
}

GameException::~GameException() throw() {
}
