#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int A[MAX];

void solve() {
  int N, C;
  cin >> N >> C;
  for (int i = 0; i < N; i++) cin >> A[i];

  for (int i = 0; i < N; i++) {
    if (A[i] == C) return cout << "1\n", void();
  }

  set<int> p;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      int v = A[i] + A[j];
      if (v == C) return cout << "1\n", void();
      if (v <= C && p.count(C - v)) return cout << "1\n", void();
    }
    p.insert(A[i]);
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
