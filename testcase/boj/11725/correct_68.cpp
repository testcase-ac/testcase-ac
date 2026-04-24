#include <stdio.h>
#include <vector>
#include <stack>

using namespace std;
int main() {
	int n, x, y;
	scanf("%d", &n);
	vector<int> adj[n+1];
	for(int i=0; i<n+1; i++) {
		adj[i].clear();
	}
	for(int i=0; i<n-1; i++) {
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	vector<bool> visited(n+1);
	vector<int> parent(n+1);

	stack<int> toVisit;
	toVisit.push(1);
	int visiting;
	while(!toVisit.empty()) {
		visiting = toVisit.top();
		toVisit.pop();
		for(int node : adj[visiting]) {
			if(!visited[node]) {
				parent[node] = visiting;
				toVisit.push(node);
			}
		}
		visited[visiting] = true;
	}
	//printf("dfs done\n");
	for(int i=2; i<=n; i++) {
		printf("%d\n", parent[i]);
	}

}
