#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

ll f(int x, int y, int i) {
  ll ret = (abs(x) + 1) ^ (abs(y) + 1);
  return ret * i + i;
}

void solve() {
  int n; string s; cin >> n >> s;

  vector<int> C;
  for (char c : s) {
    if (c == 'U') C.push_back(0);
    else if (c == 'R') C.push_back(1);
    else if (c == 'D') C.push_back(2);
    else C.push_back(3);
  }

  ll S[4]{}; map<pii, int> V[4];
  for (int l = 0; l < 4; ++l) {
    int x = dx[l], y = dy[l];
    for (int c : C) {
      x += dx[c], y += dy[c];
      S[l] += f(x, y, ++V[l][{x, y}]);
    }
  }

  int X[4], Y[4], cx = 0, cy = 0;
  for (int l = 0; l < 4; ++l) X[l] = dx[l], Y[l] = dy[l];

  for (int i = 0; i < n; ++i) {
    for (int l = 0; l < 4; ++l) {
      X[l] += dx[C[i]], Y[l] += dy[C[i]];
      S[l] -= f(X[l], Y[l], V[l][{X[l], Y[l]}]--);
      S[l] += f(cx, cy, ++V[l][{cx, cy}]);
    }
    cout << S[(C[i] + 2) % 4] << '\n';
    cx += dx[C[i]], cy += dy[C[i]];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
