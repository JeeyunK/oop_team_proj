#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Practice_info {
	int correct;
	int wrong;
	double user_correctness;

public:
	Practice_info();
	~Practice_info() {}
	virtual double check_info(queue <string> written_vector, string user_sentence, int& entire_correct);
};

class Sentence : public Practice_info {
public:
	queue <string> written_queue;
	vector <string> user_vector;
	string user_sentence;
	int written_num;
	ifstream written_file;
	double user_time;

public:
	Sentence();
	virtual ~Sentence() {}
	virtual void load_written();
	virtual void in_sentence();
	//virtual void out_sentence();
};
/*
class Time_check {
	int user_time;
	Correctness user_cort;

public:
	Time_check();
	~Time_check();
	void check_time();
};*/

class Interface : public Sentence {
	string user_info;
	double entire_correctness;
	double entire_time;
	int entire_correct;

public:
	Interface();
	~Interface() {}
	virtual void basic_out();
	virtual void load_info();
};

