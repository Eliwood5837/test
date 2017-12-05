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
void explorethefile(unordered_map<string, unordered_set<string>> &themap, string filename);
void findedges(unordered_map<string, unordered_set<string>> &themap, int &edge, unordered_map <string, int> &indegs);
void allvertex(unordered_map<string, unordered_set<string>> &themap);
int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cerr << "Usage: spellchecker inputfile=input.txt" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);
	const std::string script = am.get("script");
	std::cout << "input script file name is " << script << std::endl;
	ofstream graph("graph.txt");

	unordered_map<string, unordered_set<string>> Graph;
	explorethefile(Graph, script);
	allvertex(Graph);
	//sets all to 0 by default
	unordered_map <string, int> indegrees;
	for (auto& x : Graph) {
		indegrees.insert(make_pair(x.first, 0));
	}
	
	
	
	//used to find number of edges, also gets indegrees
	int edges = 0;
	findedges(Graph, edges, indegrees);
	
	//used to get decreasing order of degrees, also only keeps one of each
	map<int, string> order;
	for (auto&x : indegrees) {
		order.insert(make_pair(x.second, x.first));
	}
	for (auto& x : Graph) {
		cout << x.first << ": ";
		for (std::unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end(); ++itr) {
			cout << *itr << " ";
		}
		cout << endl;
	}
	//only have individual indegrees, no dupes so can get the next indegree if the largest one doesn't have 3
	priority_queue<int> indegs;
	for (auto&x : order) {
		indegs.push(x.first);
	}
	for(auto&x : indegrees) {
		cout << x.first << ": " << x.second << endl;
	}
	//key = filename, value=indegree
	int current_indegree = indegs.top();
	
	//final set to output
	set<string> top3;
	for (auto& x : indegrees) {
		if (x.second == 0) {
			graph << "isolated=" << x.first << endl;
		}
		if (x.second == current_indegree) {
			top3.insert(x.first);
		}
	}

	//makes sure always at least 3 in top3
	if (top3.size() < 3) {
		while (top3.size() < 3) {
			indegs.pop();
			current_indegree = indegs.top();
			for (auto&x : indegrees) {
				if (x.second == current_indegree) {
					top3.insert(x.first);
				}
			}
		}
	}

	//m is number of edges
	//n is number of vertices
	graph << "m=" << edges << endl;
	graph << "n=" << Graph.size() << endl;
	for (string x : top3) {
		graph << "top3=" << x << endl;
	}

	system("pause");
	graph.close();
	return 0;
}

void allvertex(unordered_map<string, unordered_set<string>> &themap) {
	unordered_set<string> empty;
	for (auto&x : themap) {
		for (unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end(); itr++) {
			if (themap.find(*itr) == themap.end()) {
				themap.insert(make_pair(*itr, empty));
			}
		}
	}
}

void explorethefile(unordered_map<string, unordered_set<string>> &themap, string filename){
	ifstream input(filename);
	unordered_set<string> V;
	string line;
	while (getline(input, line)) {
		if (line.substr(0, 7) == "explore") {
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == '(' || line[i] == ')' || line[i] == '\'') {
					line[i] = ' ';
				}
			}
			stringstream explore(line);
			string func, file;
			explore >> func >> file;
			ifstream filelist(file);
			string listoffiles;
			while (getline(filelist, listoffiles)) {
				ifstream thefiles(listoffiles);
				string thelines;
				while (getline(thefiles, thelines)) {
					if (thelines.substr(0, 7) == "<a href") {
						int file = thelines.find_first_of("\"");
						string c = thelines.substr(file + 1);
						int file2 = c.find_last_of("\"");
						c.erase(file2, c.length());
						//c is what it links to
						V.insert(c);
					}

				}
				thefiles.close();
				themap.insert(make_pair(listoffiles, V));
				V.clear();

			}
			filelist.close();
		}

	}
	input.close();
}

void findedges(unordered_map<string, unordered_set<string>> &themap, int &edge, unordered_map <string, int> &indegs) {
	for (auto& x : themap) {
		for (unordered_set<string>::iterator itr = x.second.begin(); itr != x.second.end(); itr++) {
			edge++;
			if (indegs.find(*itr) != indegs.end()) {
				indegs.find(*itr)->second++;
			}
			
		}
	}
}