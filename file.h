#include <iostream>
struct file_struct {
	std::string name;
	std::string PATH; 
};
class file {
private:
	struct file_struct file_list[100];
	int size;

public:
	void update_filepath();
	void show_path();
	
	void add_file(std::string filename, std::string path);
	void show_list();


};