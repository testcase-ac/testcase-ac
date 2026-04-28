#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Segment {
  ll x1, x2, h1, h2;

  bool operator < (Segment &rhs) const {
    ll ols = (h2 - h1) * (rhs.x2 - rhs.x1), ors = (rhs.h2 - rhs.h1) * (x2 - x1);
    if (ols == ors) return x2 < rhs.x2;
    return ols < ors;
  }
};

const int MAX = 2e3;
int a[MAX], dp[MAX];
vector<Segment> v;

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    v.push_back({i, j, a[i], a[j]});
  }
  sort(v.begin(), v.end());

  for (auto vi : v) {
    dp[vi.x2] = max(dp[vi.x2], dp[vi.x1] + 1);
  }

  int rem = *max_element(dp, dp + n) + 1;
  cout << n - rem;
}
