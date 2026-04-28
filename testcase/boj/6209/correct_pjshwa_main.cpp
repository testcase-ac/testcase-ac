#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
vector<int> a;
int n, m;

bool feasible(int cd) {
  int last = 0, rem = 0;
  for (int i = 0; i < n + 1; i++) {
    if (a[i] - last < cd) rem++;
    else last = a[i];
  }
  return rem <= m;
}

void solve() {
  int d;
  cin >> d >> n >> m;
  for (int i = 0, x; i < n; i++) cin >> x, a.push_back(x);
  a.push_back(d);
  sort(a.begin(), a.end());

  int left = 1, right = INF;
  while (left < right) {
    int mid = (left + right) / 2;
    if (feasible(mid)) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
