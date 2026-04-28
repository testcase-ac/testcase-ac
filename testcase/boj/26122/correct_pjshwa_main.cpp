#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300000;

void solve() {
  int K; string S;
  cin >> K >> S;

  int streak = 0, last = -1;
  vector<int> H;
  for (char& c : S) {
    if (last == c) streak++;
    else {
      if (streak) H.push_back(streak);
      streak = 1;
      last = c;
    }
  }
  H.push_back(streak);

  int ans = 0;
  for (int i = 0; i < H.size() - 1; i++) {
    ans = max(ans, 2 * min(H[i], H[i + 1]));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
