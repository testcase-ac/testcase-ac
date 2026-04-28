#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20;
int cdist[1 << MAXN], K;

int d2i(string& s) {
  int ret = 0;
  for (int i = 0; i < K; ++i) ret += (s[i] - '0') << i;
  return ret;
}

string i2d(int i) {
  string ret;
  for (int j = 0; j < K; ++j) ret += (i >> j & 1) + '0';
  return ret;
}

void solve() {
  int N; cin >> N >> K;

  memset(cdist, 0x3f, sizeof(cdist)); queue<int> q;
  for (int i = 0; i < N; ++i) {
    string ss; cin >> ss;
    int s = d2i(ss);
    q.push(s); cdist[s] = 0;
  }

  while (!q.empty()) {
    int cur = q.front(); q.pop();
    for (int i = 0; i < K; ++i) {
      int nxt = cur ^ (1 << i);
      if (cdist[nxt] > cdist[cur] + 1) {
        cdist[nxt] = cdist[cur] + 1;
        q.push(nxt);
      }
    }
  }

  int maxd = 0;
  for (int i = 0; i < (1 << K); ++i) maxd = max(maxd, cdist[i]);
  for (int i = 0; i < (1 << K); ++i) {
    if (cdist[i] != maxd) continue;
    cout << i2d(i) << '\n';
    break;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
