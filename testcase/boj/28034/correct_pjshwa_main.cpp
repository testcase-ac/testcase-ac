#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int base = 0, fstreak = 0, reach_edge = 0, reach = 0;
  char schar = ' ', echar;
  deque<pii> fs;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'F') {
      if (i > 0 && fstreak == 0) schar = S[i - 1];
      fstreak++;
    }
    else {
      if (fstreak) {
        echar = S[i];
        fs.push_back({fstreak, schar == echar});
        fstreak = 0;
      }

      if (i > 0 && S[i - 1] == S[i]) base++;
    }
  }

  if (S[0] == 'F') {
    if (fs.empty()) {
      // This means that the string consists of only 'F's.
      cout << N << '\n';
      for (int i = 0; i < N; i++) cout << i << '\n';
      return;
    }

    reach_edge += fs.front().first;
    fs.pop_front();
  }
  if (fstreak) {
    reach_edge += fstreak;
  }

  for (auto [fc, same] : fs) {
    if (same) {
      if (fc & 1) {
        reach += (fc + 1) / 2;
      }
      else {
        base += 1;
        reach += fc / 2;
      }
    }
    else {
      if (fc & 1) {
        base += 1;
        reach += (fc - 1) / 2;
      }
      else {
        reach += fc / 2;
      }
    }
  }

  if (reach_edge) {
    int max_value = base + 2 * reach + reach_edge;
    cout << max_value - base + 1 << '\n';
    for (int i = base; i <= max_value; i++) {
      cout << i << '\n';
    }
  }
  else {
    cout << reach + 1 << '\n';
    for (int i = 0; i <= reach; i++) {
      cout << base + 2 * i << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
