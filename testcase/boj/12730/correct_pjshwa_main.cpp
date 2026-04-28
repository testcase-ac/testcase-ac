#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

unordered_map<string, int> fmi;
int fm_count;

int fm_index(string f) {
  auto found = fmi.find(f);
  if (fmi.end() == found) {
    fmi.insert({f, fm_count++});
    return fm_count;
  }
  else return found->second;
}

int qs[1000], sc, qc, d[100][1000];

int r(int c, int qi) {
  if (qi == qc) return 0;

  if (d[c][qi] == -1) {
    if (qs[qi] == c) {
      int ans = 2e9;
      for (int i = 0; i < sc; i++) {
        if (i == c) continue;
        ans = min(ans, 1 + r(i, qi + 1));
      }
      d[c][qi] = ans;
    }
    else d[c][qi] = r(c, qi + 1);
  }
  return d[c][qi];
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    memset(d, -1, sizeof(d));
    fmi.clear();
    fm_count = 0;

    string s, q;

    // Consume newline
    cin >> sc;
    getline(cin, s);
    for (int i = 0; i < sc; i++) {
      getline(cin, s);
      fm_index(s);
    }

    cin >> qc;
    getline(cin, q);
    for (int i = 0; i < qc; i++) {
      getline(cin, q);
      qs[i] = fm_index(q);
    }

    int ans = 2e9;
    for (int i = 0; i < sc; i++) ans = min(ans, r(i, 0));
    cout << "Case #" << tc << ": " << ans << '\n';
  }
}
