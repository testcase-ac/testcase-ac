#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e7;
int lp[MAX + 1];
vector<int> pr, CP{-1};
int cur;

bool is_prime(int n) {
  if (n < 2) return false;
  return lp[n] == n;
}

void dfs(int i) {
  if (i >= 3) {
    bool able = !is_prime(cur);
    for (int s = 0; s < i; ++s) for (int e = s + 1; e < i; ++e) {
      string cur_s = to_string(cur);
      string sub = cur_s.substr(s, e - s + 1);
      if (s == 0 && e == i - 1) continue;

      able &= is_prime(stoi(sub));
    }
    if (able) CP.push_back(cur);
  }
  if (i == 7) return;

  for (int c : {1, 3, 7, 9}) {
    cur = cur * 10 + c;
    dfs(i + 1);
    cur /= 10;
  }
}

void solve() {
  int N; cin >> N;
  cout << *prev(upper_bound(CP.begin(), CP.end(), N)) << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (int c = 1; c <= 9; ++c) {
    cur = c;
    dfs(1);
  }
  sort(CP.begin(), CP.end());

  int t = 1;
  cin >> t;
  while (t--) solve();
}
