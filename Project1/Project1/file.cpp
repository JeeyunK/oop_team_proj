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
		std::cout << i +1<< ". " << file_list[i].name << std::endl;
	}
	
}

void file::get_file() {
	int choice = 0;
restart:
	std::cout << "what stage file?" << std::endl;
	std::cout << "0.short stage" << std::endl;
	std::cout << "1.loger stage" << std::endl;
	std::cout << std::endl << "Choice: ";
	std::string input_tag;
	std::getline(std::cin, input_tag);
	int input_tag_stoi = atoi(input_tag.c_str());
	int tag = 0;
	if (input_tag_stoi == 1) {
		tag = 1;
	}
	else if (input_tag_stoi == 0) {
		tag = 0;
	}
	else {
		std::cout << "wrong tag number" << std::endl;
		goto restart;
	}

	std::cout << "Insert Game File" << std::endl;
	std::cout << "File name :";
	std::string fname;
	std::getline(std::cin, fname);
	std::cout << "File path :";
	std::string fpath;
	std::getline(std::cin, fpath);
	bool result = add_file(tag,fname, fpath);
	if (!result) {
		std::cout << "What do you want to do now?" << std::endl;
		std::cout << "1. try one more" << std::endl;
		std::cout << "2. go back to main menu" << std::endl;
		std::cout << "Choice :";
		std::cin >> choice;
		std::cin.ignore(32767, '\n');
		switch (choice) {
		case 1:
			system("cls");
			goto restart;
			break;
		case 2:
			system("cls");
			return;
		default: break;

		}
	}
}

//if you want to add file, just use this function.
//use like add_file(filename, path)
//this function add filename and path to the filepath.txt file to 
bool file::add_file(int tag, std::string tmp_filename, std::string path) {
	std::ofstream file;
	file.open("filepath.txt", std::ios::app);
	file.seekp(0, std::ios::end);
	int length = file.tellp();
	std::ifstream Readfile;
	Readfile.open(path);
	if (!Readfile.is_open()){
		std::cout << "there is no that's filename\n";
		return false;
	}
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
	Readfile.close();
	update_filepath(tag);
	return true;
}
//this will update the filename in tmp_filename,path[100] 
//it just open a file and update the contents in filepath.txt
void file::update_filepath(int tag) {
	std::string tmp_filename[100];
	std::string tmp_filepath[100];
	int length = 0;
	std::ifstream file;
	if (tag == 0) {
		file.open("filepath.txt");
	}
	else if(tag == 1) {
		file.open("longfilepath.txt");
	}
	
	file.seekg(0, std::ios::end);
	length = file.tellg();
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
			//std::cout << file_list[i].name << file_list[i].PATH << std::endl;
		}
	} else std::cout << "file didn't opened yet"<< std::endl;
	file.close();
}
