#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> A[i];

  int l = 0, r = N;
  while (l < r) {
    int m = (l + r) / 2;

    priority_queue<int> pq;
    ll acc = 0, cnt = 0;
    for (int i = 0; i < N; i++) {
      pq.push(A[i]); acc += A[i];
      if (acc >= M) {
        int t = pq.top(); pq.pop();

        cnt++;
        acc -= 2 * t;
      }
    }

    if (cnt <= m) r = m;
    else l = m + 1;
  }
  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
