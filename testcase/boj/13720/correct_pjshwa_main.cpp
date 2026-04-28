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
  cin >> N;
  if (N == 2) return cout << "-1\n", void();

  if (N % 2 == 1) fill_odd();
  else fill_even();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) cout << A[i][j] << ' ';
    cout << '\n';
  }

  // assert(check());
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
