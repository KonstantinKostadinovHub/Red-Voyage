#pragma once

#include <fstream>

using namespace std;
class Saver
{
public:
	Saver();
	~Saver();
	string m_location;
	void saveSession();
};