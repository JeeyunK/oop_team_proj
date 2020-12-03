#pragma once

#include <string.h>
#include <iostream>
#include <list>

struct form {
	std::string name;
	double correctness;
	int speed;
};

class Score {
private:
	int size;
	std::list<struct form> rank_list;
public:
	void update_score();
	void show_Score();
	void add_score(std::string name, double correctness, int speed);
	void Write_score();
	std::string writer( std::string name, double correctness, int speed, bool first);
};