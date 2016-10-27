#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
# include <stdio.h>

using namespace std;

typedef vector<vector<pair<int, int> > > graph;

void dijkstra (graph &g, int start, int master){

	priority_queue<pair<int, int>, vector<pair<int, int> >, std::greater<pair<int, int> > > pq;
	vector<int> visited, cost;
	pair<int, int> walker, next;

	visited.resize (g.size(), 0);
	cost.resize (g.size(), 999999);

	walker.first = 0;
	walker.second = start;

	visited[walker.second] = 1;

	pq.push (walker);

	while (!pq.empty()){

		walker = pq.top();
		pq.pop();

		visited[walker.second] = 1;

		if (walker.second == master) break;

		for (int cont=0; cont<g[walker.second].size(); cont++){

			next = g[walker.second][cont];

			if (visited[next.second] == 0){
				if (cost[next.second] > (walker.first + next.first)){
					cost[next.second] = walker.first + next.first;
					pq.push (make_pair(cost[next.second], next.second));
				}
			}
		}
	}
	cout << cost[master] << endl;
}

int main (){
	
	graph g;
	int n, m, c, k, origin, master, distance;

	while (true){
		scanf("%d %d %d %d", &n, &m, &c, &k);

		if (n == 0 && m == 0 && c == 0 && k == 0) break;

		g.clear();
		g.resize (n);

		for (int cont=0; cont<m; cont++){
			scanf("%d %d %d", &origin, &master, &distance);

			if (origin < c && master < c){
				if (origin == master-1 || master == origin-1){
					if (origin == master-1){
						g[origin].push_back (make_pair(distance, master));
					}

					if (master == origin-1){
						g[master].push_back (make_pair (distance, origin));
					}
				}
			}
			else {
				if (origin < c && master >= c){
					g[master].push_back (make_pair(distance, origin));
				}
				else if (master < c && origin >= c){
					g[origin].push_back (make_pair (distance, master));
				}
				else if (origin >= c && master >= c){
					g[origin].push_back(make_pair (distance, master));
					g[master].push_back (make_pair (distance, origin));
				}
			}
		}
		dijkstra (g, k, c-1);
	}

	return 0;
}