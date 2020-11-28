#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class PracticeInfo {
	int correct;
	int wrong;
	double user_correctness;

public:
	PracticeInfo();
	~PracticeInfo() {}
	virtual double check_info(queue <string> written_vector, string user_sentence, int& entire_correct);
};

class Sentence : public PracticeInfo {
public:
	queue <string> _writtenQueue;
	vector <string> _userVector;
	string _userSentence;
	int _writtenNum;
	ifstream _writtenFile;
	double _userTime;

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


class UserInterface        : public Sentence {
	string _userInfo;
	double _entireCorrectness;
	double _entireTime;
	int _entireCorrect;

public:
	UserInterface();
	~UserInterface() {}
	virtual void basic_out();
	virtual void load_info();
};

