#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int dcnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
ll pw10[19];
string S;
int z, K = 0;
int d[20][200][2];

// current digit, digit sum, following original number
bool r(int i, int tot, bool f) {
  if (d[i][tot][f] != -1) return d[i][tot][f];
  if (i == z) return d[i][tot][f] = (tot == K);

  bool ret = false;
  if (f) {
    int c = S[i] - '0';
    for (int u = c; u < 10; u++) {
      if (i == z - 1 && u == c) continue;
      ret |= r(i + 1, tot + dcnt[u], u == c);
    }
  }
  else {
    for (int u = 0; u < 10; u++) ret |= r(i + 1, tot + dcnt[u], 0);
  }

  return d[i][tot][f] = ret;
}

stack<int> traj;
bool trace(int i, int tot, bool f) {
  if (i == z) return (tot == K);

  bool cur = d[i][tot][f];
  if (f) {
    int c = S[i] - '0';
    for (int u = c; u < 10; u++) {
      if (i == z - 1 && u == c) continue;
      if (cur == d[i + 1][tot + dcnt[u]][u == c] && trace(i + 1, tot + dcnt[u], u == c)) {
        traj.push(u);
        return true;
      }
    }
  }
  else {
    for (int u = 0; u < 10; u++) {
      if (cur == d[i + 1][tot + dcnt[u]][0] && trace(i + 1, tot + dcnt[u], 0)) {
        traj.push(u);
        return true;
      }
    }
  }

  return false;
}

void solve() {
  cin >> S;
  z = S.size();
  for (int i = 0; i < z; i++) {
    K += dcnt[S[i] - '0'];
  }
  memset(d, -1, sizeof(d));

  bool q = r(0, 0, 1);
  if (!q) {
    memset(d, -1, sizeof(d));
    r(0, 0, 0);
    trace(0, 0, 0);
  }
  else trace(0, 0, 1);

  string res = "";
  while (!traj.empty()) {
    res += traj.top() + '0';
    traj.pop();
  }

  ll ans = stoll(res) - stoll(S);
  if (ans <= 0) ans += pw10[z];
  cout << ans << '\n';
}

int main() {
  fast_io();

  pw10[0] = 1;
  for (int i = 1; i < 19; i++) pw10[i] = pw10[i - 1] * 10;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
