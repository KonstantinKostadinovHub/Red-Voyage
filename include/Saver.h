#pragma once

#include <fstream>
#include <istream>

using namespace std;

class Saver
{
public:
	Saver();
	Saver(string location);
	~Saver();
	string m_location;
	void saveSession();
	void loadSession();
};