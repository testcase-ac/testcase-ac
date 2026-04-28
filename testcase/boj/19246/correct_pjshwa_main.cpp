#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = (1 << 20);
int A[MAXN];

void solve() {
  int N; cin >> N;
  int P = (1 << N) - 1;
  for (int i = 0; i < P; ++i) cin >> A[i];
  sort(A, A + P);

  vector<int> C{A[0]}, W;
  for (int it = 1; it < N; ++it) {
    queue<int> Q;
    for (int j = 1; j < P; ++j) {
      if (!Q.empty() && Q.front() == A[j]) Q.pop();
      else Q.push(A[j] + C.back()), W.push_back(A[j]);
    }
    if (Q.empty()) {
      P = (P + 1) / 2 - 1;
      assert(P == (int)W.size());
      for (int j = 0; j < P; ++j) A[j] = W[j];
      C.push_back(A[0]);
    }
    else return cout << "NO\n", void();
    W.clear();
  }

  for (int i = 0; i < N; ++i) cout << C[i] << " \n"[i == N - 1];
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
