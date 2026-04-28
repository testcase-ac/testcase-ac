#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX];
bool vis[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  int it = 0, cnt = 0;
  while (cnt < N) {
    it++;

    int last = 0;
    for (int i = 0; i < N; i++) {
      if (vis[i]) continue;
      if (A[i] <= last) continue;

      vis[i] = true;
      cnt++;
      last = A[i];
    }
  }

  cout << it << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
