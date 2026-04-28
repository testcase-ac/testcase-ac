#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int N;

int s2i(string s) {
  int n = s.size(), r = 0;
  for (int i = 0; i < n; i++) {
    r = (r * 3 + s[i] - 'A');
  }
  return r;
}

string i2s(int n) {
  string s;
  while (n) {
    s += (n % 3) + 'A';
    n /= 3;
  }
  for (int d = s.size(); d < N; d++) s += 'A';
  reverse(s.begin(), s.end());
  return s;
}

const int MAX = 2e6;
vector<int> all;
int cur = 0;
int cdist[MAX];

void f(int i) {
  if (i == N) {
    all.push_back(cur);
    return;
  }

  int pre = cur;
  for (int a = cur % 3; a < 3; a++) {
    cur = (cur * 3 + a);
    f(i + 1);
    cur = pre;
  }
}

void solve() {
  int Q;
  cin >> N >> Q;
  f(0);
  memset(cdist, -1, sizeof(cdist));

  queue<pii> q;
  for (int e : all) {
    q.push({e, 0});
    cdist[e] = 0;
  }

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    string s = i2s(v);
    for (int k = 2; k <= N; k++) {
      reverse(s.begin(), s.begin() + k);
      int u = s2i(s);
      if (cdist[u] == -1 || cdist[u] > c + 1) {
        cdist[u] = c + 1;
        q.push({u, c + 1});
      }
      reverse(s.begin(), s.begin() + k);
    }
  }

  while (Q--) {
    string s;
    cin >> s;
    cout << cdist[s2i(s)] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
