// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;



void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited, int &count) {
	if (!visited[node])
	{
		//cout << node << endl;
		count++;
	}
	visited[node] = true;


	for (int& s : graph[node])
	{
		if (!visited[s])
		{
			dfs(s, graph, visited,count);
		}
	}
}



int main()
{
	/*
	vector<int>test({ 1,2,3 });

	vector<int>::iterator index  = find(test.begin(), test.end(), 2);
	test.erase(index	);
	*/

	int tnodes, tedges;
	cin >> tnodes >> tedges;
	vector<vector<int>> graph(tnodes + 1);
	vector<pair<int,int>> nodepairs; //pairs in here to be invalidated later



	for (size_t i = 0; i < tedges; i++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);

		nodepairs.push_back(make_pair(a, b));

	}


	int subtrees = 0;
	int count = 0; 
	int removedEdges = 0;

	for (pair<int, int>& par : nodepairs) {
		//disable the edge in the graph 
		vector<int>::iterator index = find(graph[par.first].begin(),
			graph[par.first].end(), par.second);
		vector<int>::iterator ind2 = find(graph[par.second].begin(),
			graph[par.second].end(), par.first);

		//check if the value exists
		if (index!=graph[par.first].end())
		{
			graph[par.first].erase(index);
			graph[par.second].erase(ind2);
		}

		vector<bool> visited(tnodes + 1);
		for (size_t i = 0; i < visited.size(); i++)
		{
			visited[i] = 0;
		}

		for (size_t i = 1; i <= tnodes; i++)
		{
			if (!visited[i])
			{
				count = 0;
				dfs(par.first, graph, visited, count);
				if (count%2 !=0)
				{
					//re add the node and break. 
					graph[par.first].push_back(par.second);
					graph[par.second].push_back(par.first);
					i = tnodes;
				}
				else
				{
					removedEdges++;
					i = tnodes;
				}
				//cout << "------" << count << endl;
				subtrees++;

			}
		}
	}

	cout << removedEdges;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
