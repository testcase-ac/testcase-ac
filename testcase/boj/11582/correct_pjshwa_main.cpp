#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1 << 20;
int A[MAX];

void solve() {
  int N, K;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  cin >> K;

  K = N / K;
  for (int i = 0; i < N; i += K) sort(A + i, A + i + K);

  for (int i = 0; i < N; i++) cout << A[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
