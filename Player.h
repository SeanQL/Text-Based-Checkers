#pragma once

#include <iostream>
#include "string"
using namespace std;

class Player {
private:

	// Creating player attributes
	string playerName;

public:

	void setName(string playerName) {
		//This will allow the users to creater their own usernames
		this->playerName = playerName;
	}

	string getName() {
		return playerName;
	}
};