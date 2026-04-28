#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
int A[MAX];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N, greater<int>());

  map<int, int> target;
  for (int i = 0; i < min(N, K); i++) {
    int x = N - i;
    target[x % K] = x;
  }

  for (int i = 0; i < N; i++) {
    int r = A[i] % K;
    if (target[r] < A[i]) return cout << "0\n", void();
    A[i] = target[r];
    target[r] -= K;
  }
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
