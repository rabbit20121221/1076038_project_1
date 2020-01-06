// 1076038 hw1

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#pragma warning(disable : 4996)

using namespace std;

#define TAKEN "T"
#define NOT_TAKEN "N"

#define STATE_SN "00"	// strong not taken
#define STATE_WN "01"	// weak not taken
#define STATE_WT "10"	// weak taken
#define STATE_ST "11"	// strong taken

#define MISS "X"
#define NO_MISS "O"

char filename[100] = "test1.txt";
char output_name[] = "output.txt";
ofstream out;

int two_bit_predictor(int index);	// 預測功能
void show();
vector<string> read_in, pre_state, prediction, miss_or_not;
int counting_miss = 0;

int main() {
	string read_file;
	pre_state.resize(1);	// 初始 state 狀態
	pre_state[0] = "00";

	// 開檔
	cout << "輸入檔案: ";
	cin >> filename; cout << endl;
	ifstream infile(filename);
	out.open(output_name);

	while (getline(infile, read_file)) {
		istringstream iss(read_file);
		for (std::string s; iss >> s; )	// 切割輸入序列 存入vector中
			read_in.push_back(s);
		for (int i = 0; i < read_in.size(); i++) {
			// 接收預測結果
			if (two_bit_predictor(i) == 0)
				prediction.push_back(NOT_TAKEN);
			else
				prediction.push_back(TAKEN);
			// 判斷 miss_or_not
			if (read_in[i] == TAKEN) {
				if (prediction[i] == TAKEN)
					miss_or_not.push_back(NO_MISS);
				else {	// prediction == N
					miss_or_not.push_back(MISS);
					counting_miss++;
				}
			}
			else {	// input == N
				if (prediction[i] == TAKEN) {
					miss_or_not.push_back(MISS);
					counting_miss++;
				}
				else	// prediction == N
					miss_or_not.push_back(NO_MISS);
			}
		}
		show();	// 輸出檔案
		read_in.clear(); pre_state.clear(); prediction.clear(); miss_or_not.clear();
		pre_state.resize(1); pre_state[0] = "00"; counting_miss = 0;
	}
	cout << "預測完成!" << endl;
	cout << "Output file: output.txt\n" << endl;
	system("pause");
	return 0;
}


int two_bit_predictor(int index) {
	int prediction_result = 0; // 預測結果，0為N 1為T
	if (pre_state[index] == STATE_SN) {
		prediction_result = 0;
		if (read_in[index] == TAKEN)
			pre_state.push_back(STATE_WN);
		else	// not taken
			pre_state.push_back(STATE_SN);
	}
	else if (pre_state[index] == STATE_WN) {
		prediction_result = 0;
		if (read_in[index] == TAKEN)
			pre_state.push_back(STATE_WT);
		else 	// not taken
			pre_state.push_back(STATE_SN);
	}
	else if (pre_state[index] == STATE_WT) {
		prediction_result = 1;
		if (read_in[index] == TAKEN)
			pre_state.push_back(STATE_ST);
		else 	// not taken
			pre_state.push_back(STATE_WN);
	}
	else if (pre_state[index] == STATE_ST) {
		prediction_result = 1;
		if (read_in[index] == TAKEN)
			pre_state.push_back(STATE_ST);
		else	// not taken
			pre_state.push_back(STATE_WT);
	}
	return prediction_result;
}


void show() {
	// 結果
	out << "State: ";
	for (int i = 0; i < pre_state.size() - 1; i++) 
		out << pre_state[i] << " ";
	out << "\nInput: ";
	for (int i = 0; i < read_in.size(); i++) 
		out << read_in[i] << " ";
	out << "\nPrediction: ";
	for (int i = 0; i < prediction.size(); i++) 
		out << prediction[i] << " ";
	out << "\nMiss or not: ";
	for (int i = 0; i < miss_or_not.size(); i++)
		out << miss_or_not[i] << " ";
	out << "\nMisprediction rate: " << counting_miss << "/" << read_in.size() << endl << endl;
}

