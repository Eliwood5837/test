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
#include "ArgumentManager.h"
using namespace std;
int main(int argc, char* argv[]) {

	/*if (argc < 2) {
		std::cerr << "Usage: spellchecker inputfile=input.txt" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);
	const std::string script = am.get("script");
	std::cout << "input script file name is " << script << std::endl;*/
	//ifstream input(script);
	ifstream input("input.txt");
	ofstream graph("graph.txt");
	string line;
	unordered_map<string, unordered_set<string>> E;
	unordered_set<string> V;

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
			ifstream filelist(file);
			string newline;
			//newline is files
			while (getline(filelist, newline)) {
				ifstream thefiles(newline);
				string theline;
				//cout << "FILE " << newline << endl;
				while (getline(thefiles, theline)) {
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

					}

				}
				E.insert(make_pair(newline, V));
				V.clear();

			}

		}



	}
	int k = 0;
	for (auto& x : E) {
		//cout << x.first << ": ";
		for (unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end(); itr++) {
		//	cout << *itr << " ";
			k++;
		}
		//cout << endl;
	}

	unordered_map <string, int> indegrees;
	for (auto&x : E) {
		indegrees.insert(make_pair(x.first, 0));

	}
	for (auto& x : E) {
		int indeg = 0;

		for (unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end(); itr++) {
			indegrees.find(*itr)->second++;
		}

	}
	for (auto&x : indegrees) {
		//cout << x.first << " " << x.second << endl;
	}
	map<int, string> test;
	for (auto&x : indegrees) {
		//cout << x.first << " " << x.second << endl;
		test.insert(make_pair(x.second, x.first));
	}
	priority_queue<int> w;
	for (auto&x : test) {
		w.push(x.first);
	}
	//key = filename, value=indegree
	priority_queue<int> q;
	for (auto&x : indegrees) {
		q.push(x.second);
	}
	//int current_indegree = q.top();
	int current_indegree = w.top();
	//cout << "queue" << endl;
	for (int i = 0; i < q.size(); i++) {
		//cout << q.top()<<endl;
		//q.pop();
	}

	//cout << q.size() << endl;
	//cout << "indeg" << current_indegree << endl;
	set<string> top3;
	for (auto& x : indegrees) {
		if (x.second == 0) {
			graph << "isolated=" << x.first << endl;
		}
		if (x.second == current_indegree) {
			top3.insert(x.first);
		}
	}
	if (top3.size() < 3) {
		while (top3.size() < 3) {
			w.pop();
			current_indegree = w.top();
			for (auto&x : indegrees) {
				if (x.second == current_indegree) {
					top3.insert(x.first);
				}
			}
		}
	}

	graph << "m=" << k << endl;
	graph << "n=" << E.size() << endl;
	for (string x : top3) {
		graph << "top3=" << x << endl;
	}

	system("pause");
	return 0;
}

