#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int MAX = 1 << 10;
bool vis[MAX];
int n;

bool winning(int state) {
  int dt = 0;
  for (int i = 0; i < n; i++) {
    if (state & (1 << (2 * i))) dt++;
    if (state & (1 << (2 * i + 1))) dt--;
  }
  return dt > 0;
}

int bfront(int state, int pos) {
  int mseg = state % (1 << pos), mdig = (state / (1 << pos)) % 2;
  state = state / (1 << (pos + 1)) * (1 << (pos + 1));
  return state + mseg * 2 + mdig;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> n;
  int istate = 0;
  for (int i = 0; i < n; i++) {
    string s1, s2;
    cin >> s1 >> s2;
    if (s1 == "O") istate |= (1 << (2 * i));
    if (s2 == "O") istate |= (1 << (2 * i + 1));
  }

  queue<pii> q;
  q.push({istate, 0});
  vis[istate] = true;

  while (!q.empty()) {
    auto [s, d] = q.front();
    q.pop();

    if (winning(s)) {
      cout << d << '\n';
      return 0;
    }

    for (int i = 1; i < 2 * n; i++) {
      int nstate = bfront(s, i);
      if (!vis[nstate]) vis[nstate] = true, q.push({nstate, d + 1});
    }
  }
}
