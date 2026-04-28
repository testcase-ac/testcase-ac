#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; ++i) cin >> A[i];

  vector<int> ans;
  stack<int> sm, sp;
  for (int i = N; i >= 3; i--) {
    if (A[i] < 0) sm.push(i);
    else {
      if (sm.size()) {
        while (!sm.empty()) ans.push_back(sm.top()), sm.pop();
      }
      sp.push(i);
    }
  }
  if (sp.size()) {
    while (!sp.empty()) ans.push_back(sp.top()), sp.pop();
  }

  int i = 2;
  while (ans.size() < N - 1) ans.push_back(i++);

  ll sum = A[1];
  if (N >= 2) sum -= A[2];
  for (int i = 3; i <= N; i++) sum += abs(A[i]);

  cout << sum << '\n';
  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
