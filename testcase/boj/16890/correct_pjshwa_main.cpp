#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll A[MAXN];

void solve() {
  string S, T; cin >> S >> T;
  int N = S.size();
  sort(S.begin(), S.end());
  sort(T.begin(), T.end(), greater<char>());

  deque<char> d1, d2;
  for (int i = 0; i < (N + 1) / 2; ++i) d1.push_back(S[i]);
  for (int i = 0; i < N / 2; ++i) d2.push_back(T[i]);
  reverse(d2.begin(), d2.end());

  string ans(N, ' '); int f = 1, l = 0, r = N - 1;
  while (N--) {
    if (f) {
      if (!d2.empty() && d1.front() < d2.back()) {
        ans[l++] = d1.front();
        d1.pop_front();
      }
      else {
        ans[r--] = d1.back();
        d1.pop_back();
      }
    }
    else {
      if (!d1.empty() && d1.front() < d2.back()) {
        ans[l++] = d2.back();
        d2.pop_back();
      }
      else {
        ans[r--] = d2.front();
        d2.pop_front();
      }
    }

    f = !f;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
