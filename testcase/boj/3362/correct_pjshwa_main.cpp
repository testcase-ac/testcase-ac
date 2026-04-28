#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K;
  cin >> N >> K;

  vector<ll> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int left = 1, right = N + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    ll sum = 0, reach;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < mid; i++) pq.push(A[i]);

    if (pq.top() > 1) reach = 1;
    else {
      while (1) {
        int v = pq.top(); pq.pop();
        sum += v;

        if (pq.empty() || pq.top() > sum + 1) {
          reach = sum + 1;
          break;
        }
      }
    }

    if (reach >= K) right = mid;
    else left = mid + 1;
  }

  if (left == N + 1) cout << "-1\n";
  else cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
