#include "file.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#pragma warning (disable: 4996)
//show filepath.txt's filepaths

void file::show_path() {
	for (int i = 0; i < size; i++) {
		std::cout << i << ". " << file_list[i].PATH << std::endl;
	}
}
// show filenames like a list.
void file::show_list() {
	for (int i = 0; i < size; i++) {
		std::cout << i << ". " << file_list[i].name << std::endl;
	}

}
//if you want to add file, just use this function.
//use like add_file(filename, path)
//this function add filename and path to the filepath.txt file to 
void file::add_file(std::string tmp_filename, std::string path) {
	std::ofstream file;
	file.open("C:\\Users\\kim\\Documents\\filepath.txt", std::ios::app);
	file.seekp(0, std::ios::end);
	int length = file.tellp();
	if (length == 0) {
		file.write(tmp_filename.c_str(), tmp_filename.size());
		file.write("_", 1);
		file.write(path.c_str(), path.size());
	}
	else {
		file.write("\n", 1);
		file.write(tmp_filename.c_str(), tmp_filename.size());
		file.write("_", 1);
		file.write(path.c_str(), path.size());
	}
	file.close();
}
//this will update the filename in tmp_filename,path[100] 
//it just open a file and update the contents in filepath.txt
void file::update_filepath() {
	std::string tmp_filename[100];
	std::string tmp_filepath[100];

	std::ifstream file;
	file.open("C:\\Users\\kim\\Documents\\filepath.txt");
	file.seekg(0, std::ios::end);
	int length = file.tellg();
	file.seekg(0, std::ios::beg);
	if (length == 0) {

		std::cout << "there is no file\n";
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
			tmp_filename[count] = ptr;

			while (ptr != NULL) {
				index++;
				if (index == 1) {
					ptr = strtok(NULL, "_");
					tmp_filepath[count] = ptr;
				}
				else {
					ptr = strtok(NULL, "_");
				}
			}
			count++;
			size++;

		}
		for (int i = 0; i < size; i++) {
			file_list[i].name = tmp_filename[i];
			file_list[i].PATH = tmp_filepath[i];
		}
	}
	file.close();
}
