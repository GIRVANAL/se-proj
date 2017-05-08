#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include"std_lib_facilities.h"
using namespace std;

int main() {
	set<string>lexicon;
	ifstream infile;
	infile.open("dictionary.txt");
	if (infile.fail()) error("Can't open EnglishWords.txt");
	while (true) {
		string word;
		getline(infile, word);
		if (infile.fail()) break;
		lexicon.insert(word);
	}
	int n;
	while (cout << "please give a number:", cin>>n) {
	map<string, int>freq;
	map<string, int>::iterator it = freq.begin();
	string word;
	for (string word:lexicon) {
		if (word.size() < n) {
			continue;
		}
		else {
			string suffix = word.substr(word.size() - n);
			freq[suffix] ++;
		}
	}
	vector<int>value;
	for (;it != freq.end();++it) {
		value.push_back(it->second);
	}
	sort(value.begin(), value.end());
	for (int i = 0;i < 10;i++) {
		cout << "suffix:";
		cout << value[value.size() - i - 1];
	}
	}

	infile.close();
	system("pause");
	return 0;
}