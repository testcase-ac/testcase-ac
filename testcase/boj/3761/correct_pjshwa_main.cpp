#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<string> split(const string &str, const char delimiter) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delimiter, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

const int MAX = 30;
queue<int> mpf[MAX + 1];
int wpf[MAX + 1][MAX + 1], wmatch[MAX + 1];
bool wfree[MAX + 1];
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

  vector<string> m, w;
  string x;
  for (int i = 1; i <= n; i++) cin >> x, m.push_back(x);
  for (int i = 1; i <= n; i++) cin >> x, w.push_back(x);
  for (int i = 1; i <= n; i++) {
    cin >> x;
    auto fs = split(x, ':');
    string player = fs[0], prefs = fs[1];
    int pli = find(m.begin(), m.end(), player) - m.begin() + 1;
    for (char pref : prefs) {
      int pfi = find(w.begin(), w.end(), string(1, pref)) - w.begin() + 1;
      mpf[pli].push(pfi);
    }
  }
  for (int i = 1; i <= n; i++) {
    cin >> x;
    auto fs = split(x, ':');
    string player = fs[0], prefs = fs[1];
    int pli = find(w.begin(), w.end(), player) - w.begin() + 1, j = 0;
    for (char pref : prefs) {
      int pfi = find(m.begin(), m.end(), string(1, pref)) - m.begin() + 1;
      wpf[pli][++j] = pfi;
    }
  }
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

  vector<string> sorted = m;
  sort(sorted.begin(), sorted.end());

  for (auto &c : sorted) {
    int i = find(m.begin(), m.end(), c) - m.begin() + 1;
    cout << c << ' ';
    for (int j = 1; j <= n; j++) {
      if (wmatch[j] == i) cout << w[j - 1] << '\n';
    }
  }
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
