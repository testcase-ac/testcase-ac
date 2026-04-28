#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int H[MAX], lis_l[MAX], lis_r[MAX];

void solve() {
  int N; string S;
  cin >> N >> S;
  for (int i = 0; i < N; i++) cin >> H[i];

  vector<int> v;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'L') {
      if (v.empty()) v.push_back(H[i]);
      else if (v.back() < H[i]) v.push_back(H[i]);
      else {
        auto it = upper_bound(v.begin(), v.end(), H[i] - 1);
        *it = H[i];
      }
    }
    lis_l[i] = v.size();
  }

  v.clear();
  for (int i = N - 1; i >= 0; i--) {
    if (S[i] == 'R') {
      if (v.empty()) v.push_back(H[i]);
      else if (v.back() < H[i]) v.push_back(H[i]);
      else {
        auto it = upper_bound(v.begin(), v.end(), H[i] - 1);
        *it = H[i];
      }
    }
    lis_r[i] = v.size();
  }

  int ans = max(lis_l[N - 1], lis_r[0]);
  for (int i = 0; i < N - 1; i++) {
    int cur = lis_l[i] + lis_r[i + 1];
    ans = max(ans, cur);
  }

  cout << N - ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
