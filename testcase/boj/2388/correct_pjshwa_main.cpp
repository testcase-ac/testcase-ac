#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, M;
  cin >> N >> M;

  ll maxv = 0, minv = 0;
  priority_queue<int> ax, bx;
  priority_queue<int, vector<int>, greater<int>> am, bm;

  vector<int> A(N), B(M);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    ax.push(A[i]); am.push(A[i]);
  }
  for (int i = 0; i < M; i++) {
    cin >> B[i];
    bx.push(B[i]); bm.push(B[i]);
  }
  if (ax.top() != bx.top()) return cout << "-1\n", void();

  while (!ax.empty() && !bx.empty()) {
    if (ax.top() == bx.top()) {
      minv += ax.top();
      ax.pop();
      bx.pop();
    }
    else if (ax.top() > bx.top()) {
      minv += ax.top();
      ax.pop();
    }
    else {
      minv += bx.top();
      bx.pop();
    }
  }
  while (!ax.empty()) {
    minv += ax.top();
    ax.pop();
  }
  while (!bx.empty()) {
    minv += bx.top();
    bx.pop();
  }

  ll asz = am.size(), bsz = bm.size();
  int last = 0;
  while (!am.empty() && !bm.empty()) {
    if (am.top() == bm.top()) {
      maxv += asz * bsz * (am.top() - last);
      asz--; bsz--;
      last = am.top();
      am.pop();
      bm.pop();
    }
    else if (am.top() < bm.top()) {
      maxv += asz * bsz * (am.top() - last);
      asz--;
      last = am.top();
      am.pop();
    }
    else {
      maxv += asz * bsz * (bm.top() - last);
      bsz--;
      last = bm.top();
      bm.pop();
    }
  }

  cout << minv << ' ' << maxv << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
