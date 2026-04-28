#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 123;
int pos[MAX + 1];
vector<pii> traj;
stack<int> ss[4];

void move(int u, int v) {
  pos[ss[u].top()] = v;
  ss[v].push(ss[u].top());
  ss[u].pop();
  traj.push_back({u, v});
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    pos[x] = 1;
    ss[1].push(x);
  }

  for (int c = n; c >= 1; c--) {
    int p = pos[c];
    while (ss[p].top() != c) move(p, p == 1 ? 2 : 1);
    move(p, 3);
  }

  cout << traj.size() << '\n';
  for (auto [u, v] : traj) cout << u << ' ' << v << '\n';
}
