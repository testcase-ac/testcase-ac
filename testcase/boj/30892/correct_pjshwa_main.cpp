#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX];

void solve() {
  ll N, K, T; cin >> N >> K >> T;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  int l = 0; priority_queue<int> pq;
  while (K--) {
    while (l < N && A[l] < T) {
      pq.push(A[l]);
      ++l;
    }
    if (pq.empty()) break;
    T += pq.top(); pq.pop();
  }
  cout << T << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
