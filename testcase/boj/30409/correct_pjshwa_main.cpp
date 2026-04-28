#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll H[MAXN], L[MAXN], R[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> H[i];

  {
    ll run = 0; stack<int> s;
    for (int i = 0; i < N; ++i) {
      while (!s.empty() && H[s.top()] < H[i]) {
        int t = s.top(); s.pop();
        if (!s.empty()) {
          int u = s.top();
          ll xd = t - u, yd = H[t] - H[u];
          run -= xd * xd + yd * yd;
        }
      }

      if (!s.empty()) {
        int u = s.top();
        ll xd = i - u, yd = H[i] - H[u];
        run += xd * xd + yd * yd;
      }
      L[i] = run;
      s.push(i);
    }
  }

  {
    ll run = 0; stack<int> s;
    for (int i = N - 1; i >= 0; --i) {
      while (!s.empty() && H[s.top()] < H[i]) {
        int t = s.top(); s.pop();
        if (!s.empty()) {
          int u = s.top();
          ll xd = t - u, yd = H[t] - H[u];
          run -= xd * xd + yd * yd;
        }
      }

      if (!s.empty()) {
        int u = s.top();
        ll xd = u - i, yd = H[i] - H[u];
        run += xd * xd + yd * yd;
      }
      R[i] = run;
      s.push(i);
    }
  }

  int Q; cin >> Q;
  while (Q--) {
    int t; cin >> t; --t;
    cout << L[t] + R[t] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
