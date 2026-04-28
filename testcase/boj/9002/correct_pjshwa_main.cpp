#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

queue<int> mpf[1001];
int wpf[1001][1001], wmatch[1001];
bool wfree[1001];
int n;

bool wPrefersm1Tom2(int w, int m1, int m2) {
  int m1i = -1, m2i = -1;
  for (int i = 1; i <= n; i++) {
    if (wpf[w][i] == m1) m1i = i;
    if (wpf[w][i] == m2) m2i = i;
  }
  return m1i < m2i;
}

void solve() {
  cin >> n;
  memset(wmatch, 0, sizeof(wmatch));
  for (int i = 1; i <= n; i++) while (!mpf[i].empty()) mpf[i].pop();

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    int s;
    cin >> s;
    mpf[i].push(s);
  }
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> wpf[i][j];
  for (int i = 1; i <= n; i++) wfree[i] = true;

  queue<int> mq;
  for (int i = 1; i <= n; i++) mq.push(i);

  while (!mq.empty()) {
    int cm = mq.front();
    mq.pop();

    int cw = mpf[cm].front();
    mpf[cm].pop();

    if (wfree[cw]) {
      wmatch[cw] = cm;
      wfree[cw] = false;
    }
    else {
      if (wPrefersm1Tom2(cw, cm, wmatch[cw])) {
        mq.push(wmatch[cw]);
        wmatch[cw] = cm;
      }
      else mq.push(cm);
    }
  }

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    if (wmatch[j] == i) cout << j << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
