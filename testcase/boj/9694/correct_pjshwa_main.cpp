#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#define MAX 100
using namespace std;

typedef tuple<int,int,int> P;
int dist[21];
int visited[21];

int main(void){
  int t; cin >> t;
  int n, m, x, y, z;
  for (int tc = 1; tc <= t; tc++) {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
      dist[i] = MAX;
      visited[i] = -2;
    }

    vector<pair<int, int>> w_graph[21];
    while (n--) {
      cin >> x >> y >> z;
      w_graph[x].push_back(make_pair(y, z));
      w_graph[y].push_back(make_pair(x, z));
    }

    priority_queue<P, vector<P>, greater<P> > pq;
	  pq.push(make_tuple(0, 0, -1));

    while (!pq.empty()) {
      int cur_dist, cur_vtx, prev_vtx;
      tie(cur_dist, cur_vtx, prev_vtx) = pq.top();
      pq.pop();

      if (visited[cur_vtx] != -2) continue;
      dist[cur_vtx] = cur_dist;
      visited[cur_vtx] = prev_vtx;

      for(int i = 0; i < w_graph[cur_vtx].size(); i++){
        int vtx, wgt;
        tie(vtx, wgt) = w_graph[cur_vtx][i];

        pq.push(
          make_tuple(wgt + cur_dist, vtx, cur_vtx)
        );
      }
    }

    cout << "Case #" << tc << ": ";
    if (dist[m - 1] == MAX) cout << -1;
    else {
      vector<int> path;
      int res = m - 1;
      while (res != -1) {
        path.push_back(res);
        res = visited[res];
      }
      reverse(path.begin(), path.end());
      for (auto &x : path) cout << x << ' ';
    }
    cout << '\n';
  }
}
