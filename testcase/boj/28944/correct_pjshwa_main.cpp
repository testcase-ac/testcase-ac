#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], A[i] += i;

  vector<int> lis;
  for (int i = 0; i < N; ++i) {
    auto it = lower_bound(lis.begin(), lis.end(), A[i]);
    if (it == lis.end()) lis.push_back(A[i]);
    else *it = A[i];
  }
  cout << lis.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
