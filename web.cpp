#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <map>
using namespace std;
int main(int argc, char* argv[]) {

	ifstream input("input.txt");
	string line;
	//typedef unordered_map<string, unordered_set<string>> mymap;
	unordered_map<string, unordered_set<string>> E;
	unordered_set<string> V;
	unordered_set<string> filenames;

	while (getline(input, line)) {
		if (line.substr(0, 7) == "explore") {
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '(' || line[i] == ')' || line[i] == '\'') {
					line[i] = ' ';
				}

			}
			stringstream test(line);
			string func, file;
			test >> func >> file;
			ifstream newinput(file);
			string newline;
			//newline is files
			while (getline(newinput, newline)) {
				ifstream fileinput(newline);
				string theline;
				cout << "FILE " << newline << endl;
				filenames.insert(newline);
				while (getline(fileinput, theline)) {
					//theline is inside
					
					if (theline.substr(0, 7) == "<a href") {
						
						int file = theline.find_first_of("\"");
						string c = theline.substr(file + 1);
						int file2 = c.find_last_of("\"");
						c.erase(file2, c.length());
						//c is what it links to
						V.insert(c);
						
					}
					for (auto i = V.begin(); i != V.end(); i++) {
						cout << "pass" << endl;
						//cout << *i << endl;
					}
					

				}
				E.insert(make_pair(newline, V));
				//E.insert_or_assign(newline, V);
				V.clear();
				cout << "new set" << endl;
				//V.insert(newline);
				//cout << "FILE " << newline << endl;
			}

		}
		
		

	}
	//cout << E.size();
	int k = 0;
	for (auto& x : E) {
		cout << x.first << ": ";
		for (unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end();itr++) {
			cout << *itr << " ";
			k++;
		}
		cout << endl;
	}
	cout << "edges"<<k;
	cout << "vertices" << E.size();
	unordered_map <string, int> indegrees;
	for (auto&x : E) {
		indegrees.insert(make_pair(x.first,0));
		//indegrees.insert_or_assign(x.first,0);
	}
	for (auto&x : indegrees) {
		cout << x.first << " " << x.second << endl;
	}
	for (auto& x : E) {
		int indeg = 0;
		//cout << x.first << ": ";
		for (unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end(); itr++) {
			//cout << *itr << " ";
			cout << indegrees.find(*itr)->second++ << "increment"<<endl;
		}
		//cout << endl;
	}
	for (auto&x : indegrees) {
		cout << x.first << " " << x.second << endl;
	}
	//key = filename, value=indegree
	priority_queue<int> q;
	for (auto&x : indegrees) {
		q.push(x.second);
	}
	for (int i = 0; i < q.size(); i++) {
		cout << q.top();
		q.pop();
	}
	system("pause");
	return 0;
}

