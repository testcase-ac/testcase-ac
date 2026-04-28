#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K;
  cin >> N >> K;

  int q = sqrt(N - 1); q++;
  if (K < q) return cout << "-1\n", void();

  deque<int> dq;
  for (int i = N; i >= N - (K - q) + 1; i--) dq.push_back(i);
  
  int l = N - (K - q);
  stack<int> w;
  for (int i = 1; i <= l; i++) {
    w.push(i);
    if (w.size() == q) {
      while (!w.empty()) {
        dq.push_back(w.top());
        w.pop();
      }
    }
  }
  while (!w.empty()) {
    dq.push_back(w.top());
    w.pop();
  }

  for (int i = 0; i < N; i++) {
    cout << dq[i] << " \n"[i == N - 1];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
