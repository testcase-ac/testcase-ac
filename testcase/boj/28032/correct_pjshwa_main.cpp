#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 18;
int cdist[MAX];

void solve() {
  int C, N; cin >> C >> N;

  int mask = (1 << C) - 1;
  memset(cdist, 0x3f, sizeof(cdist));

  vector<int> A; queue<int> q;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    int cur = 0;
    for (char c : S) cur = (cur * 2) + (c == 'G');
    A.push_back(cur);

    cdist[cur ^ mask] = 0;
    q.push(cur ^ mask);
  }

  while (!q.empty()) {
    int cur = q.front(); q.pop();
    for (int i = 0; i < C; i++) {
      int nxt = cur ^ (1 << i);
      if (cdist[nxt] > cdist[cur] + 1) {
        cdist[nxt] = cdist[cur] + 1;
        q.push(nxt);
      }
    }
  }

  for (int i = 0; i < N; i++) cout << C - cdist[A[i]] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
