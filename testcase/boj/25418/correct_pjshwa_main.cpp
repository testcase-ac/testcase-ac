#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, INF = 0x3f3f3f3f;
int cdist[MAX + 1];

void solve() {
  int A, K;
  cin >> A >> K;

  fill(cdist, cdist + MAX + 1, INF);
  queue<int> q;
  q.push(A);
  cdist[A] = 0;

  while (!q.empty()) {
    int v = q.front(); q.pop();
    
    int a = v + 1;
    if (a <= MAX && cdist[a] > cdist[v] + 1) {
      cdist[a] = cdist[v] + 1;
      q.push(a);
    }
    int b = 2 * v;
    if (b <= MAX && cdist[b] > cdist[v] + 1) {
      cdist[b] = cdist[v] + 1;
      q.push(b);
    }
  }

  cout << cdist[K] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
