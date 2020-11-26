#include "Score.h"
#include "file.h"
int main() {
	
	file f; 
	f.update_filepath();
	f.show_list();
	std::string s, s1;
	std::cin >> s >> (s1);
	s1 = s1;
	f.add_file(s, s1);
	f.show_list();





}