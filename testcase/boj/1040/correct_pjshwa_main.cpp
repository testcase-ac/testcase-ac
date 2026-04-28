#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string S;
int z, K;
int d[20][1 << 10][2];

// current digit, digit use state, following original number
bool r(int i, int state, bool f) {
  if (d[i][state][f] != -1) return d[i][state][f];

  int cnt = __builtin_popcount(state);
  if (cnt > K) return d[i][state][f] = 0;
  if (i == z) return d[i][state][f] = (cnt == K);

  bool ret = false;
  if (f) {
    int c = S[i] - '0';
    for (int u = c; u < 10; u++) {
      if (state & (1 << u)) ret |= r(i + 1, state, u == c);
      else ret |= r(i + 1, state | (1 << u), u == c);
    }
  }
  else {
    for (int u = 0; u < 10; u++) {
      if (state & (1 << u)) ret |= r(i + 1, state, 0);
      else ret |= r(i + 1, state | (1 << u), 0);
    }
  }

  return d[i][state][f] = ret;
}

stack<int> traj;
bool trace(int i, int state, bool f) {
  int cnt = __builtin_popcount(state);
  if (cnt > K) return false;
  if (i == z) return (cnt == K);

  bool cur = d[i][state][f];
  if (f) {
    int c = S[i] - '0';
    for (int u = c; u < 10; u++) {
      if (state & (1 << u)) {
        if (cur == d[i + 1][state][u == c] && trace(i + 1, state, u == c)) {
          traj.push(u);
          return true;
        }
      }
      else {
        if (cur == d[i + 1][state | (1 << u)][u == c] && trace(i + 1, state | (1 << u), u == c)) {
          traj.push(u);
          return true;
        }
      }
    }
  }
  else {
    for (int u = 0; u < 10; u++) {
      if (state & (1 << u)) {
        if (cur == d[i + 1][state][0] && trace(i + 1, state, 0)) {
          traj.push(u);
          return true;
        }
      }
      else {
        if (cur == d[i + 1][state | (1 << u)][0] && trace(i + 1, state | (1 << u), 0)) {
          traj.push(u);
          return true;
        }
      }
    }
  }

  return false;
}

void solve() {
  cin >> S >> K;
  z = S.size();
  memset(d, -1, sizeof(d));

  bool q = r(0, 0, 1);
  while (!q) {
    // impossible with z digits
    S = "1";
    for (int i = 0; i < z; i++) S += '0';
    memset(d, -1, sizeof(d));

    z++;
    q = r(0, 0, 1);
  }

  // backtrack
  trace(0, 0, 1);
  while (!traj.empty()) {
    cout << traj.top();
    traj.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
