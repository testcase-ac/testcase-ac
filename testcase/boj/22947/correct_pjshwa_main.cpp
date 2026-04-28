#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int st[MAX + 1], duration[MAX + 1], indegree[MAX + 1], nindegree[MAX + 1];
int n, s = 1, e;
vector<int> graph[MAX + 1];

void init() {
  for (int i = 1; i <= MAX; i++) st[i] = 0, nindegree[i] = indegree[i];
}

int min_time(int g1, int g2, int g3) {
  queue<int> q;
  q.push(s);

  init();
  for (int i = 1; i <= n; i++) {
    int a = q.front();
    q.pop();

    int dur;
    if (a == g1 || a == g2 || a == g3) dur = 0;
    else dur = duration[a];

    for (int dst : graph[a]) {
      st[dst] = max(st[dst], st[a] + dur);
      if (!--nindegree[dst]) q.push(dst);
    }
  }

  return st[e] + duration[e];
}

void mark_end() {
  queue<int> q;
  q.push(s);

  init();
  for (int i = 1; i <= n - 1; i++) {
    int a = q.front();
    q.pop();

    for (int dst : graph[a]) {
      if (!--nindegree[dst]) q.push(dst);
    }
  }
  e = q.front();
}

int main() {
  fast_io();

  int m, k;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) cin >> duration[i];
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    indegree[b]++;
  }
  mark_end();

  int ans = min_time(0, 0, 0);
  if (k == 1) {
    for (int i = 1; i <= n; i++) {
      if (i == s || i == e) continue;
      ans = min(ans, min_time(i, 0, 0));
    }
  }
  if (k == 2) {
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
      if (i == s || i == e || j == s || j == e) continue;
      ans = min(ans, min_time(i, j, 0));
    }
  }
  if (k == 3) {
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) for (int k = j + 1; k <= n; k++) {
      if (i == s || i == e || j == s || j == e || k == s || k == e) continue;
      ans = min(ans, min_time(i, j, k));
    }
  }

  cout << ans;
}
