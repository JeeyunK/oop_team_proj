#pragma once

#include <iostream>
// file struct consisted of name and path.
struct file_struct {
	std::string name;
	std::string PATH;
};
//this is file class to manage the file system in this program.
//consist of file_list and size. 
// when we use get_file() function, we update file_list same as the file's contents.
class file final{
public:
	struct file_struct file_list[100];
	int size;

public:
	void show_path();
	void get_file();
	void update_filepath(int tag);
	bool add_file(int tag,std::string filename, std::string path);
	void show_list();


};