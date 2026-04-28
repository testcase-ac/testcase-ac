#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500;
int lp[MAX + 1];
vector<int> pr;

void solve() {
  int N;
  cin >> N;
  map<int, int> pc;
  map<int, map<int, int>> ic;
  for (int i = 2; i <= N; i++) {
    for (int p : pr) {
      if (p > i) break;
      int c = p;
      while (c <= i) {
        pc[-p] += i / c;
        ic[i][-p] += i / c;
        c *= p;
      }
    }
    for (auto& [k, v] : ic[i]) v = (v & 1);
  }
  for (auto& [k, v] : pc) v = (v & 1);

  // Use one factorial
  for (int i = 1; i <= N; i++) {
    for (auto& [k, v] : ic[i]) pc[k] ^= v;
    bool f = true;
    for (auto& [k, v] : pc) {
      if (v) {
        f = false;
        break;
      }
    }
    if (f) {
      cout << i << '\n';
      return;
    }
    for (auto& [k, v] : ic[i]) pc[k] ^= v;
  }

  // Use two factorials
  for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) {
    for (auto& [k, v] : ic[i]) pc[k] ^= v;
    for (auto& [k, v] : ic[j]) pc[k] ^= v;
    bool f = true;
    for (auto& [k, v] : pc) {
      if (v) {
        f = false;
        break;
      }
    }
    if (f) {
      cout << i << ' ' << j << '\n';
      return;
    }
    for (auto& [k, v] : ic[i]) pc[k] ^= v;
    for (auto& [k, v] : ic[j]) pc[k] ^= v;
  }

  // Use three factorials
  for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) for (int k = j + 1; k <= N; k++) {
    for (auto& [l, v] : ic[i]) pc[l] ^= v;
    for (auto& [l, v] : ic[j]) pc[l] ^= v;
    for (auto& [l, v] : ic[k]) pc[l] ^= v;
    bool f = true;
    for (auto& [l, v] : pc) {
      if (v) {
        f = false;
        break;
      }
    }
    if (f) {
      cout << i << ' ' << j << ' ' << k << '\n';
      return;
    }
    for (auto& [l, v] : ic[i]) pc[l] ^= v;
    for (auto& [l, v] : ic[j]) pc[l] ^= v;
    for (auto& [l, v] : ic[k]) pc[l] ^= v;
  }
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

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
