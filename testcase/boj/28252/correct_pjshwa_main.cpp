#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void report_impossible() {
  cout << "-1\n";
  exit(0);
}

const int MAX = 1e5;
int A[MAX];
vector<int> adj[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  if (A[N - 1] > 2) report_impossible();
  if (N >= 2 && A[N - 2] <= 1) report_impossible();
  for (int i = 1; i < N; i++) {
    if (A[i] > A[i - 1]) report_impossible();
  }

  int it = 0;
  queue<int> q;
  if (A[N - 1] == 2) adj[1].push_back(2);
  for (int v = 0; v < A[N - 1]; v++) q.push(++it);

  for (int i = N - 2; i >= 0; i--) {
    queue<int> nq; int u;
    for (int v = 0; v < A[i]; v++) {
      int p = ++it;
      if (!q.empty()) u = q.front(), q.pop();
      adj[u].push_back(p); nq.push(p);
    }
    q = nq;
  }

  cout << it << '\n';
  for (int i = 1; i <= it; i++) {
    for (int j : adj[i]) cout << i << ' ' << j << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
