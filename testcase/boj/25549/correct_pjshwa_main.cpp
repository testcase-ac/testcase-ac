#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int v[MAX + 1];
vector<int> graph[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int x;
    cin >> x;
    if (x == -1) continue;
    graph[x].push_back(i);
  }
  for (int i = 1; i <= N; i++) cin >> v[i];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
