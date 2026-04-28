#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAX_INT = 2000000000;

// dijkstra twice

int main(){
	int n, m, x;
	scanf("%d%d%d", &n, &m, &x);
	std::vector<std::pair<int, int> > connectivity_array[1001]; // endpoint and ti
	std::vector<std::pair<int, int> > reverse_connectivity_array[1001]; // endpoint and ti
	for(int i = 0; i < m; i++){
		int s, e, t;
		scanf("%d%d%d", &s, &e, &t);
		connectivity_array[s].push_back(std::make_pair(e, t));
		reverse_connectivity_array[e].push_back(std::make_pair(s, t));
	}
	int come_distance[n+1];
	bool come_visited[n+1];
	int come_count = 1;
	for(int i = 0; i < n+1; i++){
		come_distance[i] = MAX_INT;
		come_visited[i] = false;
	}
	come_distance[x] = 0;
	come_visited[x] = true;
	for(auto &conn_pair : connectivity_array[x]){
		int reach_vertex = conn_pair.first;
		int reach_distance = conn_pair.second;
		come_distance[reach_vertex] = reach_distance;
	}
	while(come_count != n){
		int smallest_index = -1;
		int smallest_distance = MAX_INT;
		for(int i = 1; i < n+1; i++){
			if(!come_visited[i] && smallest_distance > come_distance[i]){
				smallest_distance = come_distance[i];
				smallest_index = i;
			}
		}
		come_visited[smallest_index] = true;
		for(auto &conn_pair : connectivity_array[smallest_index]){
			int reach_vertex = conn_pair.first;
			int reach_distance = conn_pair.second;
			if (come_distance[reach_vertex] > come_distance[smallest_index] + reach_distance)
				come_distance[reach_vertex] = come_distance[smallest_index] + reach_distance;
			// distance update
		}
		come_count++;
	}
	int go_distance[n+1];
	bool go_visited[n+1];
	int go_count = 1;
	for(int i = 0; i < n+1; i++){
		go_distance[i] = MAX_INT;
		go_visited[i] = false;
	}
	go_distance[x] = 0;
	go_visited[x] = true;
	for(auto &conn_pair : reverse_connectivity_array[x]){
		int reach_vertex = conn_pair.first;
		int reach_distance = conn_pair.second;
		go_distance[reach_vertex] = reach_distance;
	}
	while(go_count != n){
		int smallest_index = -1;
		int smallest_distance = MAX_INT;
		for(int i = 1; i < n+1; i++){
			if(!go_visited[i] && smallest_distance > go_distance[i]){
				smallest_distance = go_distance[i];
				smallest_index = i;
			}
		}
		go_visited[smallest_index] = true;
		for(auto &conn_pair : reverse_connectivity_array[smallest_index]){
			int reach_vertex = conn_pair.first;
			int reach_distance = conn_pair.second;
			if (go_distance[reach_vertex] > go_distance[smallest_index] + reach_distance)
				go_distance[reach_vertex] = go_distance[smallest_index] + reach_distance;
			// distance update
		}
		go_count++;
	}
	int longest_distance = 0;
	for(int i = 1; i < n+1; i++){
		if(longest_distance < go_distance[i] + come_distance[i])
			longest_distance = go_distance[i] + come_distance[i];
	}
	printf("%d\n", longest_distance);
}