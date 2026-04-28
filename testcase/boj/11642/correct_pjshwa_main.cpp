#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

char B[4][4];
void rotate_r(string& s, int r, int x) {
  for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) B[i][j] = s[i * 4 + j];
  for (int j = 0; j < 4; ++j) s[r * 4 + j] = B[r][(j + x) % 4];
}

void rotate_c(string& s, int c, int x) {
  for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) B[i][j] = s[i * 4 + j];
  for (int i = 0; i < 4; ++i) s[i * 4 + c] = B[(i + x) % 4][c];
}

const int MAXD = 6;
const string DONE = "RRRRGGGGBBBBYYYY", CHARS = "RGBY";
unordered_map<ll, int> dp1, dp2;

ll s2l(string& s) {
  ll ret = 0;
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (s[i] == CHARS[j]) {
        ret = ret * 4 + j;
        break;
      }
    }
  }
  return ret;
}

string l2s(ll l) {
  string ret = "";
  for (int i = 0; i < 16; ++i) {
    ret += CHARS[l % 4];
    l /= 4;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

void solve() {
  string U = "";
  for (int i = 0; i < 4; ++i) {
    string s; cin >> s;
    U += s;
  }

  queue<ll> Q;
  dp1[s2l(U)] = 0; Q.push(s2l(U));

  while (!Q.empty()) {
    ll cur_l = Q.front(); Q.pop();
    string cur = l2s(cur_l);
    if (cur == DONE) {
      cout << dp1[cur_l] << '\n';
      return;
    }

    int d = dp1[cur_l];
    if (d == MAXD) continue;

    for (int r = 0; r < 4; ++r) {
      for (int x = 1; x <= 3; x += 2) {
        string nxt_s = cur;
        rotate_r(nxt_s, r, x);
        ll nxt = s2l(nxt_s);
        if (!dp1.count(nxt)) {
          dp1[nxt] = d + 1;
          Q.push(nxt);
        }
      }
    }

    for (int c = 0; c < 4; ++c) {
      for (int x = 1; x <= 3; x += 2) {
        string nxt_s = cur;
        rotate_c(nxt_s, c, x);
        ll nxt = s2l(nxt_s);
        if (!dp1.count(nxt)) {
          dp1[nxt] = d + 1;
          Q.push(nxt);
        }
      }
    }
  }

  string done_s = DONE;
  ll done_l = s2l(done_s);
  dp2[done_l] = 0; Q.push(done_l);

  while (!Q.empty()) {
    ll cur_l = Q.front(); Q.pop();
    if (dp1.count(cur_l)) {
      cout << dp1[cur_l] + dp2[cur_l] << '\n';
      return;
    }

    int d = dp2[cur_l];
    if (d == MAXD) continue;

    string cur = l2s(cur_l);
    for (int r = 0; r < 4; ++r) {
      for (int x = 1; x <= 3; x += 2) {
        string nxt = cur;
        rotate_r(nxt, r, x);
        ll nxt_l = s2l(nxt);
        if (!dp2.count(nxt_l)) {
          dp2[nxt_l] = d + 1;
          Q.push(nxt_l);
        }
      }
    }

    for (int c = 0; c < 4; ++c) {
      for (int x = 1; x <= 3; x += 2) {
        string nxt = cur;
        rotate_c(nxt, c, x);
        ll nxt_l = s2l(nxt);
        if (!dp2.count(nxt_l)) {
          dp2[nxt_l] = d + 1;
          Q.push(nxt_l);
        }
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
