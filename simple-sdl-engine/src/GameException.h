/*
 * GameException.h
 *
 *  Created on: 23/03/2010
 *      Author: drphrozen
 */

#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string;

class GameException : public runtime_error {
public:
	GameException(const string&);
	virtual ~GameException() throw();
};

#endif /* GAMEEXCEPTION_H_ */
