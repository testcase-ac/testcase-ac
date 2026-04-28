#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<string> W = {
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",
    "Never gonna say goodbye",
    "Never gonna tell a lie and hurt you",
    "Never gonna stop"
  };

  cin.ignore();
  for (int i = 0; i < N; ++i) {
    string S; getline(cin, S);
    bool found = false;
    for (auto& w : W) {
      found |= S == w;
    }
    if (!found) return cout << "Yes\n", void();
  }
  cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
