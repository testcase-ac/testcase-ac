#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S;
  cin >> S;
  int N = S.size();

  string ans = "";
  for (int s1 = 1; s1 < N; s1++) for (int s2 = s1 + 1; s2 < N; s2++) {
    string S1 = S.substr(0, s1), S2 = S.substr(s1, s2 - s1), S3 = S.substr(s2);
    if (S1.empty() || S2.empty() || S3.empty()) continue;

    reverse(S1.begin(), S1.end());
    reverse(S2.begin(), S2.end());
    reverse(S3.begin(), S3.end());
    string R = S1 + S2 + S3;
    if (ans.empty() || ans > R) ans = R;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
