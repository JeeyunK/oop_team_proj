#pragma once

#include "file.h"
#include "Score.h"

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include <istream>
#include <fstream>
#include <time.h>
#include <cwchar>


using namespace std;

//checking correct/incorrect
class PracticeInfo {
public:
	int correct;   //the number of total correct letters
	int wrong;     //the number of total incorrect letters
	int tot_letters;	//the number of total letters, used in calculating speed
	double user_correctness;	//��Ȯ��
	queue <int> _wrongLetterIndex; // Index of wrong letters

public:
	PracticeInfo();
	~PracticeInfo() {}
	//compare user_sentence and stage_sentence(for correctness)
	virtual double check_info(queue <string> written_vector, string user_sentence);
};

class Sentence : public PracticeInfo {
public:
	queue <string> _writtenQueue;	//save the stage file
	//vector <string> _userVector;
	string _userSentence;	//save user input
	int _writtenNum;	//stage number
	ifstream _writtenFile;	//stage file
	double _userTime;	//time(sec) for the last sentence
	class file _file;
	class Score _score;
	double _entireCorrectness;	//��ü ��Ȯ��
	double _entireTime;		//��ü ��� �ð�

public:
	Sentence();
	virtual ~Sentence() {}
	//loading file
	virtual bool load_written();
	//print a sentence one by one
	virtual void in_sentence();
	virtual void in_stage();
	void progressBar(float);		//�ε��� ���
	virtual void print_last_sentence(int, int, std::string);
};


class UserInterface : public Sentence {
	string _userInfo;	//user nickname
	//int _entireCorrect;
	unsigned int choice;	//���� �޴� �Է�
	bool running;	//���α׷� ���� status

public:
	UserInterface();
	~UserInterface() {}
	virtual bool basic_out(int tag);	//managing total stage playing (invoke every methods)
	virtual void load_info();	//invoking basic_out()
	bool load_shortwriting(int tag);
	virtual void choose_option();
	inline bool getRunning() const { return	running; }	//���� �� ���
	void fontsizeChange();		//��Ʈ ũ�� ����
	void reset_score();
	void reset_input();
	void minigame_start();
};


/*class Start		//���� ȭ��
{
private:
	unsigned int choice;	//���� �޴� �Է�
	bool running;	//���α׷� ���� status
public:
	Start();
	~Start();

	//Functions
	void mainMenu();	//���� �޴� ���
	inline bool getRunning() const { return	running; }	//���� �� ���
	void progressBar();		//�ε��� ���
	void fontsizeChange(int x, int y);		//��Ʈ ũ�� ����
};
*/

