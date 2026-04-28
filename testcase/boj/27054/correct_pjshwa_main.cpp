#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 8000;
int P[MAX];

vector<int> r(int i) {
  if (i == 0) return {0};

  auto ov = r(i - 1);
  vector<int> ret;
  for (int j = 0; j < ov.size(); j++) {
    ret.push_back(ov[j] >= P[i] ? ov[j] + 1 : ov[j]);
  }
  ret.push_back(P[i]);
  return ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i < N; i++) cin >> P[i];

  for (int e : r(N - 1)) cout << e + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
