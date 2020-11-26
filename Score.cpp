#include "Score.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#pragma warning (disable: 4996)


void Score::update_score() {
	std::string name[100];
	int speed[100];
	double correctness[100];

	std::ifstream file;
	file.open("C:\\Users\\kim\\Documents\\INITIAL_FILE.txt");
	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);
	if (length == 0) {

		std::cout << "there is no save file\n";
		return;
	}
	size = 0;
	int count = 0;
	if (file.is_open()) {
		while (!file.eof()) {
			char tmp[256];
			file.getline(tmp, 256);
			
			char* ptr = strtok(tmp, "_");
			
			int index = 0;
			name[count] = ptr;
			
			while (ptr != NULL) {
				index++;
				if (index == 1) {
					ptr = strtok(NULL, "_"); 
					correctness[count] = atof(ptr);
					
				}
				else if (index ==2) {
					ptr = strtok(NULL, "_");
					speed[count] = strtol(ptr, NULL, 10);
				}
				else {
					ptr = strtok(NULL, "_");
				}
			}
			count++;
			size++;
			
		}
		//sort by matric : speed. 
		for (int i = 0; i < size -1; i++) {
			for (int j = i+1 ; j < size ; j++){
				if (speed[j] > speed[i]) {
					//sorting
					int tmp = speed[j];
					speed[j] = speed[i];
					speed[i] = tmp;

					std::string tmp_name = name[j];
					name[j] = name[i];
					name[i] = tmp_name; 

					double tmp_corr = correctness[j];
					correctness[j] = correctness[i];
					correctness[i] = tmp_corr;
				}
			}
		}
		for (int i = 0; i < size; i++) {
			list[i].name = name[i];
			list[i].speed = speed[i];
			list[i].correctness = correctness[i];
		}
	}
	file.close();
	
	

}
void Score::show_Score() {
	for (int i = 0; i < size; i++) {
		std::cout << list[i].speed << " " << list[i].correctness <<" " << list[i].name << std::endl;
	}
}

void Score::Add_Score(std::string name, double correctness, int speed) {
	std::ofstream file;
	file.open("C:\\Users\\kim\\Documents\\INITIAL_FILE.txt", std::ios::app);
	file.seekp(0, std::ios::end);
	int length = file.tellp();
	if (length == 0) {
		file.write(name.c_str(),name.size());
		file.write("_", 1);
		if (correctness == 100) {
			std::string s = std::to_string(correctness) + '0';
			file.write(s.c_str(), 5);
			file.write("_", 1);
			file.write(std::to_string(speed).c_str(), std::to_string(speed).size());
		}
		else {
			std::string s = std::to_string(correctness);
			file.write(s.c_str(), 4);
			file.write("_", 1);
			file.write(std::to_string(speed).c_str(), 3);
		}

	}
	else {
		file.write("\n", 1);
		file.write(name.c_str(), sizeof(name.c_str())-1);
		file.write("_", 1);
		if (correctness == 100) {
			std::string s = std::to_string(correctness) + '0';
			file.write(s.c_str(), 5) ;
			file.write("_", 1);
			file.write(std::to_string(speed).c_str(), 3);
		}
		else {
			std::string s = std::to_string(correctness);
			file.write(s.c_str(), 4);
			file.write("_", 1);
			file.write(std::to_string(speed).c_str(), 3);
		}

	}
	file.close();

}
