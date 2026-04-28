#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int n, p, k, d;

void solve_d1() {
  vector<int> ans; int v = p / k, u = 0;
  for (int i = 0; i < k; i++) {
    ans.push_back(v); u += v;
  }

  for (int i = 1; i <= n - k; i++) {
    if (u < p) {
      int a = min(v, p - u);
      ans.push_back(a); u += a;
    }
    else ans.push_back(0);
  }

  if (u < p) cout << "Wrong information\n";
  else for (int e : ans) cout << e << '\n';
}

void solve_drest() {
  vector<int> ans; int u = 0;
  for (int i = d - 1; i >= 0; i--) {
    ans.push_back(i); u += i;
  }
  for (int i = 0; i < k - d; i++) ans.push_back(0);

  if (u > p) return cout << "Wrong information\n", void();
  ans[0] += p - u;

  for (int e : ans) cout << e << '\n';
  for (int i = 1; i <= n - k; i++) cout << "0\n";
}

void solve() {
  cin >> n >> p >> k >> d;
  if (d == 1) solve_d1();
  else solve_drest();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
