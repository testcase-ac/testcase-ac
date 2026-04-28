#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
bitset<MAX + 1> vis;
int sv, tv;

char s[8], nxt[8];

char rotate(char o) {
  if (o == 'F') return 'A';
  else return o + 1;
}

int bfs() {
  queue<pii> q;
  q.push({sv, 0});
  vis[sv] = 1;

  while (!q.empty()) {
    auto [v, cnt] = q.front();
    q.pop();

    if (v == tv) return cnt;

    for (int i = 0; i < 8; i++) {
      s[i] = (v % 6) + 'A';
      v /= 6;
    }

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) nxt[j] = s[j];
      if (s[i] == 'A') {
        if (i > 0) nxt[i - 1] = rotate(nxt[i - 1]);
        if (i < 7) nxt[i + 1] = rotate(nxt[i + 1]);
      }
      if (s[i] == 'B') {
        if (i == 0 || i == 7) continue;
        nxt[i + 1] = nxt[i - 1];
      }
      if (s[i] == 'C') nxt[7 - i] = rotate(nxt[7 - i]);
      if (s[i] == 'D') {
        if (i == 0 || i == 7) continue;
        if (i <= 3) for (int j = 0; j < i; j++) nxt[j] = rotate(nxt[j]);
        else for (int j = i + 1; j < 8; j++) nxt[j] = rotate(nxt[j]);
      }
      if (s[i] == 'E') {
        if (i == 0 || i == 7) continue;
        if (i <= 3) {
          nxt[0] = rotate(nxt[0]);
          nxt[2 * i] = rotate(nxt[2 * i]);
        }
        else {
          nxt[7] = rotate(nxt[7]);
          nxt[2 * i - 7] = rotate(nxt[2 * i - 7]);
        }
      }
      if (s[i] == 'F') {
        if (i == 0) nxt[4] = rotate(nxt[4]);
        if (i == 1) nxt[0] = rotate(nxt[0]);
        if (i == 2) nxt[5] = rotate(nxt[5]);
        if (i == 3) nxt[1] = rotate(nxt[1]);
        if (i == 4) nxt[6] = rotate(nxt[6]);
        if (i == 5) nxt[2] = rotate(nxt[2]);
        if (i == 6) nxt[7] = rotate(nxt[7]);
        if (i == 7) nxt[3] = rotate(nxt[3]);
      }

      int nv = 0, pw = 1;
      for (int i = 0; i < 8; i++) {
        nv += (nxt[i] - 'A') * pw;
        pw *= 6;
      }

      if (vis[nv]) continue;
      vis[nv] = 1;
      q.push({nv, cnt + 1});
    }
  }

  return -1;
}

int main() {
  fast_io();

  string s, t;
  cin >> s >> t;

  int pw = 1;
  for (int i = 0; i < 8; i++) {
    sv += (s[i] - 'A') * pw;
    tv += (t[i] - 'A') * pw;
    pw *= 6;
  }
  cout << bfs() << '\n';
}
