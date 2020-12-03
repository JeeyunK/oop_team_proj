#include "Score.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#pragma warning (disable: 4996)

// this function just update Score class object
// this will find initial_file.txt and update the info in txt file.
// if there's no text in file, just print "there is no save file"
void Score::update_score() {
	std::string name;
	int speed;
	double correctness;

	std::ifstream file;
	file.open("INITIAL_FILE.txt");
	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);
	if (length == 0) {
		//std::cout << "there is no score now\n";
		return;
	}
	size = 0;
	if (file.is_open()) {
		while (!file.eof()) {
			char tmp[256];
			file.getline(tmp, 256);
			char* ptr = strtok(tmp, "_");
			int index = 0;
			name = ptr;
			//std::cout << name << std::endl;
			ptr = strtok(NULL, "_");
			correctness = atof(ptr);
			//std::cout << correctness << std::endl;
			ptr = strtok(NULL, "_");
			speed = strtol(ptr, NULL, 10);
			//std::cout << speed << std::endl;
			//ptr = strtok(NULL, "_");
			struct form rnk { name, correctness, speed };
			rank_list.push_back(rnk);
			size++;
		}
	}
	file.close();
}

//show score and correctness, name in decreasing order. 
//that means you can see this just a rank.
void Score::show_Score() {
	if (!rank_list.size()) {
		std::cout << "There is no ranking now" << std::endl;
		return;
	}
	int i = 1;
	for (struct form tmp: rank_list) {
		std::cout << i;
		if (i == 1) std::cout << "ST ";
		else if (i == 2) std::cout << "ND ";
		else if (i == 3) std::cout << "RD ";
		else std::cout <<"TH ";
		std::cout << tmp.name << " " << tmp.speed << " " << tmp.correctness<< std::endl;
		++i;
	}
}

void Score::add_score(std::string name, double correctness, int speed) {
	for (std::list<form>::iterator it = rank_list.begin(); it != rank_list.end(); ++it) {
		if ((*it).speed < speed) {
			struct form rnk { name, correctness, speed };
			rank_list.insert(it, rnk);
			if (rank_list.size() == 21) rank_list.pop_back();
			Write_score();
			size++;
			return;
		}
	}
	if (rank_list.size() == 20) return;
	struct form rnk2 { name, correctness, speed };
	rank_list.push_back(rnk2);
	Write_score();
	size++;
}

//use this function to add the info about someone's score to the Initial_file.txt file.
void Score::Write_score() {
	std::list<form>::iterator it = rank_list.begin();
	std::ofstream file;
	file.open("INITIAL_FILE.txt", std::ios::trunc);
	if (!file.is_open()) std::cout << "file open failed" << std::endl;

	std::string score = writer((*it).name, (*it).correctness, (*it).speed, 1);
	//std::cout << score << std::endl;
	file.write(score.c_str(), score.size());
	++it;
	for (; it != rank_list.end(); ++it) {
		score = writer((*it).name, (*it).correctness, (*it).speed, 0);
		file.write(score.c_str(), score.size());
		//std::cout << score << std::endl;
	}
	file.close();
}

std::string Score::writer(std::string name, double correctness, int speed, bool first) {
	std::string s;
	if (correctness == 100) s = std::to_string(correctness) + '0';
	else s = std::to_string(correctness);
	std::string ret;
	if (!first) ret += "\n";
	ret += name + "_" + s.substr(0,4) + "_" + std::to_string(speed);
	return ret;
}
