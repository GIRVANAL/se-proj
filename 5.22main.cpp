#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<map>
#include<set>
using namespace std;

int min(int a, int b) {			//min function
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}
map<int, set<vector<vector<char>>>>path;		//save all the path that can arrive at the terminal 
												// into a set ,and they have same length.Use a map.
															
vector<vector<char>>Maze;						//save the maze in the vector<vector<char>>

int r, c, num;									// r means row ,c means col, num means the smallest steps to the terminal 
												// n+1 means the smallest
void dfs(int x, int y, int s) {					// x,y mean the position now .USE DFS
	if (int(Maze[x][y] - '0')) {				// can't go
		return;
	}
	if (x == r - 1 && y == c - 1) {				//arrive at the terminal
		vector<vector<char>>temp;
		for (int i = 0;i < r;i++) {
			temp.push_back(Maze[i]);
		}
		path[s].insert(temp);
		num = min(s, num);						//compared with the last num
		return;
	}
	s++;										// have gone a step
	Maze[x][y] = '2';
	if (x > 0) {								// judge if out of vector
		dfs(x - 1, y, s);						// HERE!! RECURSIVE!
	}
	if (x < r - 1) {
		dfs(x + 1, y, s);
	}
	if (y > 0) {
		dfs(x, y - 1, s);
	}
	if (y < c - 1) {
		dfs(x, y + 1, s);
	}
	Maze[x][y] = '0';							// clean the revised maze
}
int main() {
	ifstream InFile;
	InFile.open("mg4.txt");	
	/*
	mg4.txt
	8 10
	0 1 1 1 1 1 1 1 1 1
	0 0 0 1 1 0 0 0 1 1
	1 1 0 1 0 0 1 0 1 1
	1 0 0 1 0 1 0 0 1 1
	1 0 1 1 0 0 1 0 1 1
	1 0 0 0 0 1 0 0 0 1
	1 0 1 1 0 0 1 1 0 1
	1 1 1 1 1 1 1 1 0 0
	*/
	string s;				// get the first line, row and col
	getline(InFile, s);
	stringstream ss(s);
	int row;
	int col;
	ss >> row >> col;
	r = row;
	c = col;
	for (int i = 0; i<row;i++) {
		string word;
		getline(InFile, word);
		if (InFile.fail()) {
			break;
		}
		for (int j = 0; j < col;j++) {
			vector<char>tmp;
			Maze.push_back(tmp);
			Maze[i].push_back(word[2 * j]);
		}
	}
	num = 10000;			// give num a  fake initial number
	dfs(0, 0, 0);
	cout << "The smallest length of the path =" << num+1 << endl;
	for (vector<vector<char>> tmp : path[num]) {			// print all the smallest paths 
		for (int i = 0;i < r;i++) {
			for (int j = 0;j < c;j++) {
				if (i == r - 1 && j == c - 1) {
					cout << '2' << " ";
				}
				else
					cout << tmp[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}