#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX][MAX];
int N;

bool check() {
  for (int i = 0; i < N; i++) {
    ll s = 0;
    set<int> u;
    for (int j = 0; j < N; j++) s += A[i][j], u.insert(A[i][j]);

    if (s % N) return false;
    if (u.size() != N) return false;
    if (!u.count(s / N)) return false;
  }

  for (int j = 0; j < N; j++) {
    ll s = 0;
    set<int> u;
    for (int i = 0; i < N; i++) s += A[i][j], u.insert(A[i][j]);

    if (s % N) return false;
    if (u.size() != N) return false;
    if (!u.count(s / N)) return false;
  }

  return true;
}

void fill_odd() {
  int v = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) A[i][j] = ++v;
}

void fill_even() {
  int last = 0;
  for (int i = 0; i < N - 1; i++) {
    ll s = 0;
    for (int j = 0; j < N - 1; j++) {
      A[i][j] = ++last;
      s += A[i][j];
    }
    A[i][N - 1] = N * last - s;
    last = A[i][N - 1];
  }

  for (int j = 0; j < N; j++) {
    ll s = 0;
    for (int i = 0; i < N - 1; i++) s += A[i][j];
    A[N - 1][j] = N * A[N - 2][j] - s;
  }
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) cin >> A[i];

  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int L, R, v;
      cin >> L >> R >> v;
      for (int i = L; i <= R; i++) A[i] = v;
    }
    if (op == 2) {
      int L, R;
      cin >> L >> R;
      int cnt = 0;
      for (int l = L; l <= R; l++) for (int r = l; r <= R; r++) {
        int s = 0;
        for (int i = l; i <= r; i++) s ^= (A[i] % 2);
        if (s == 0) cnt++;
      }
      cout << cnt << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
