#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[10001];
int indegree[10001];
int duration[10001];
int result[10001];
int main() {
  fast_io();

  int n, d, j, c;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> d >> j;
    duration[i] = d;
    while (j--) {
      cin >> c;
      graph[c].push_back(i);
      indegree[i]++;
    }
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) {
      result[i] = duration[i];
      q.push(i);
    }
  }

  int a;
  for (int i = 1; i <= n; i++) {
    a = q.front();
    q.pop();

    for (int y : graph[a]) {
      result[y] = max(result[y], result[a] + duration[y]);
      if (!--indegree[y]) q.push(y);
    }
  }

  int mv = -1;
  for (int i = 1; i <= n; i++) mv = max(mv, result[i]);
  cout << mv << '\n';
}
