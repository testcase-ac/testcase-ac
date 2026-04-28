#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int t[26];

void solve() {
  string S, T;
  cin >> S >> T;
  memset(t, 0, sizeof(t));

  for (char& c : S) t[c - 'A']++;
  for (char& c : T) {
    t[c - 'A']--;
    if (t[c - 'A'] < 0) {
      cout << "NO\n";
      return;
    }
  }

  string R = "";
  for (char& c : S) {
    int i = c - 'A';
    if (t[i]) t[i]--;
    else R += c;
  }
  
  if (T == R) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
