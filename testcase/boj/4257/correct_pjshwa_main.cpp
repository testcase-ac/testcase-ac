#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll C(int n, int k) {
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

int m; string T1, T2;
int rec(int s1, int e1, int s2, int e2) {
  assert(T1[s1] == T2[e2]);
  if (s1 == e1) return 1;

  int cnt[26]{}, chks = 0, ret = 1, lasti = 0, len = e1 - s1 + 1;
  for (int i = 0; i < len - 1; ++i) {
    ++cnt[T1[s1 + i + 1] - 'a']; --cnt[T2[s2 + i] - 'a'];

    int allz = 1;
    for (int j = 0; j < 26; ++j) allz &= cnt[j] == 0;
    if (!allz) continue;

    ret *= rec(s1 + lasti + 1, s1 + i + 1, s2 + lasti, s2 + i);
    lasti = i + 1; ++chks;
  }
  return ret * C(m, chks);
}

void solve() {
  cin >> T1 >> T2; int n = T1.size();
  cout << rec(0, n - 1, 0, n - 1) << '\n';
}

int main() {
  fast_io();

  while (cin >> m) {
    if (m == 0) break;
    solve();
  }
}
