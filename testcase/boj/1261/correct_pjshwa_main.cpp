#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
#define MAX 1e9 + 7
using namespace std;

typedef tuple<int,int,int> P;
int dist[100][100];
bool visited[100][100];

int main(void){
  int n, m, x, y, z;
  cin >> m >> n;

  char board[n][m + 1];
  for(int i = 0; i < n; i++) {
    cin >> board[i];

    for(int j = 0; j < n; j++) {
      dist[i][j] = MAX;
      visited[i][j] = false;
    }
  }

  priority_queue<P, vector<P>, greater<P>> pq;
  pq.push(make_tuple(0, 0, 0));

  while (!pq.empty()) {
    int cur_dist, cur_i, cur_j;
    tie(cur_dist, cur_i, cur_j) = pq.top();
    pq.pop();

    if (visited[cur_i][cur_j]) continue;
    dist[cur_i][cur_j] = cur_dist;
    visited[cur_i][cur_j] = true;
    
    if (cur_i < n - 1) pq.push(make_tuple((board[cur_i + 1][cur_j] == '1' ? 1 : 0) + cur_dist, cur_i + 1, cur_j));
    if (cur_i > 0) pq.push(make_tuple((board[cur_i - 1][cur_j] == '1' ? 1 : 0) + cur_dist, cur_i - 1, cur_j));
    if (cur_j < m - 1) pq.push(make_tuple((board[cur_i][cur_j + 1] == '1' ? 1 : 0) + cur_dist, cur_i, cur_j + 1));
    if (cur_j > 0) pq.push(make_tuple((board[cur_i][cur_j - 1] == '1' ? 1 : 0) + cur_dist, cur_i, cur_j - 1));
  }

  // for (auto &x : dist) {
  //   for (auto y : x) {
  //     cout << y << ' ';
  //   }
  //   cout << '\n';
  // }
  cout << dist[n - 1][m - 1] << '\n';
}
