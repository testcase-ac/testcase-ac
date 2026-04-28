#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  vector<int> R, B;
  for (int i = 0; i < N; ++i) {
    string T; cin >> T;
    char c = T.back(); T.pop_back();
    int L = stoi(T);
    if (c == 'R') R.push_back(L);
    else B.push_back(L);
  }
  sort(R.begin(), R.end(), greater<int>());
  sort(B.begin(), B.end(), greater<int>());
  int K = min(R.size(), B.size()), ans = 0;
  for (int i = 0; i < K; ++i) ans += R[i] + B[i];
  ans -= 2 * K;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
