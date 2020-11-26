#include <string.h>
#include <iostream>

struct form {
	std::string name; 
	double correctness; 
	int speed;
};
class Score {
private:
	int size;
	struct form list[100];
public:
	void update_score();
	void show_Score();
	void Add_Score(std::string name, double correctness, int speed);
	

};