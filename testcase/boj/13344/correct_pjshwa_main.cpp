#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 5e4;
int parent[MAX];
vector<int> graph[MAX];
int indegree[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) parent[i] = i;

  vector<pair<int, int>> wait_f, wait_b;

  while (m--) {
    int a, b;
    string o;
    cin >> a >> o >> b;
    if (o == "=") Union(a, b);
    else if (o == ">") wait_f.push_back({a, b});
    else wait_b.push_back({a, b});
  }

  for (auto [a, b] : wait_f) {
    graph[Find(a)].push_back(Find(b));
    indegree[Find(b)]++;
  }
  for (auto [a, b] : wait_b) {
    graph[Find(b)].push_back(Find(a));
    indegree[Find(a)]++;
  }

  set<int> w;
  for (int i = 0; i < n; i++) w.insert(Find(i));

  queue<int> q;
  for (int wi : w) {
    if (!indegree[wi]) q.push(wi);
  }

  int a;
  for (int i = 0; i < w.size(); i++) {
    if (q.empty()) return cout << "inconsistent\n", 0;

    a = q.front();
    q.pop();

    for (int dst : graph[a]) {
      if (Find(a) == Find(dst)) return cout << "inconsistent\n", 0;
      if (!--indegree[dst]) q.push(dst);
    }
  }

  cout << "consistent\n";
}
