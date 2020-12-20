#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <cwchar>

using namespace std;

class Start
{
private:
	unsigned int choice;
	bool running;
public:
	Start();
	virtual ~Start();

	//Functions
	void mainMenu();
	inline bool getRunning() const { return running; }
	void progressBar();
	void fontsizeChange(int x, int y);
};

