#include "ingame.h"

PracticeInfo::PracticeInfo() {
	correct = 0;
	wrong = 0;
	tot_letters = 0;
	user_correctness = 0;
}

double PracticeInfo::check_info(queue <string> written_vector, string user_sentence) {
	string written_buffer;
	string user_buffer;
	written_buffer = written_vector.front();
	written_vector.pop();
	user_buffer = user_sentence;

	int i = 0;
	while (user_buffer[i] != '\0') {
		if (i > written_buffer.size()) {
			wrong += user_buffer.size() - i;
			break;
		}
		if (user_buffer[i] == written_buffer[i]) {
			correct++;
		}
		else {
			wrong++;
			_wrongLetterIndex.push(i);
		}
		++tot_letters;
		i++;
	}
	if (i < written_buffer.size()) {

		wrong += (written_buffer.size() - i);
		for (int j = i; j < written_buffer.size(); j++) {
			_wrongLetterIndex.push(j);
		}
	}
	//entire_correct = correct;
	user_correctness = (double)((correct * 100) / (correct + wrong));
	Sleep(500);
	return user_correctness;
}