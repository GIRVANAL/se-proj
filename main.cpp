#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
string getKey(map<string, int>&m, int value);
string getKey(map<string, int>&m, int value) {
	map<string, int>::iterator it = m.begin();
	for (;it != m.end();++it) {
		if (it->second == value)
			return it->first;
	}
	return "";
}
int main() {
	set<string>lexicon;
	ifstream infile;
	infile.open("dictionary.txt");
	while (true) {
		string word;
		getline(infile, word);
		if (infile.fail()) break;
		lexicon.insert(word);
	}
	int n;
	cout << "please give a number:";
	cin >> n;
	map<string, int>freq;
	string word;
	for (string word : lexicon) {
		if (word.size() < n) {
			continue;
		}
		else {
			string suffix = word.substr(word.size() - n);
			freq[suffix] ++;
		}
	}
	cout << freq["ing"] << endl;
	vector<int>value;
	map<string, int>::iterator it = freq.begin();
	for (;it != freq.end();++it) {
		value.push_back(it->second);
	}
	sort(value.begin(), value.end());
	for (int i = 0;i < 10;i++) {
		int n = value[value.size() - i - 1];
		cout << "suffix:" << getKey(freq, n) << "\t";
		cout << n << endl;
	}
	string text = "abcdefghijking";
	cout << text.substr(text.size() - 3);
	cout << "what suffix do you want enter:";
	string SUFFIX;
	cin >> SUFFIX;
	int count = 0;
	map<int, set<string>>length;
	for (string word : lexicon) {
		if (word.size() < SUFFIX.size()) {
			continue;
		}
		else {
			string suffix = word.substr(word.size() - SUFFIX.size());
			if (suffix == SUFFIX) {
				count++;
				length[word.size()].insert(word);
			}
		}
	}
	cout << count << endl;
	vector<int>len;
	map<int, set<string>>::iterator IT = length.begin();
	for (;IT != length.end();++IT) {
		len.push_back(IT->first);
	}
	sort(len.begin(), len.end());
	for (int i = len[len.size() - 1];i > 0;i--) {
		for (string word : length[i]) {
			cout << word <<endl;
		}
	}
	infile.close();
	system("pause");
	return 0;
}