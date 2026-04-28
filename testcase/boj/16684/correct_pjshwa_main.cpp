#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 60;
__int128_t K, T[MAXN + 1][4][4];
int N, A[MAXN + 1];

void solve_M1() {
  function<__int128_t(int, int, int)> f = [&](int l, int i, int j) {
    if (l == 1) return (__int128_t)1;
    if (T[l][i][j] != -1) return T[l][i][j];

    int m = i ^ j;
    __int128_t ret = f(l - 1, i, m) + 1 + f(l - 1, m, j);
    return T[l][i][j] = ret;
  };
  function<void(int, int, int, __int128_t)> g = [&](int l, int i, int j, __int128_t k) {
    if (l == 1) {
      if (k == 1) A[l] = j;
      else A[l] = i;
      return;
    }

    int m = i ^ j;
    if (k <= f(l - 1, i, m)) {
      A[l] = i;
      g(l - 1, i, m, k);
    }
    else {
      A[l] = j;
      g(l - 1, m, j, k - f(l - 1, i, m) - 1);
    }
  };
  g(N, 1, 3, K);
}

void solve_M2() {
  function<__int128_t(int, int, int)> f = [&](int l, int i, int j) {
    if (l == 1) return (__int128_t)abs(i - j);
    if (T[l][i][j] != -1) return T[l][i][j];

    __int128_t ret, cost = abs(i - j), m = i ^ j;
    if (cost == 1) {
      ret = f(l - 1, i, m) + 1 + f(l - 1, m, j);
    }
    else {
      ret = f(l, i, m) + f(l, m, j);
    }
    return T[l][i][j] = ret;
  };
  function<void(int, int, int, __int128_t)> g = [&](int l, int i, int j, __int128_t k) {
    if (l == 1) {
      if (abs(i - j) == 2) {
        if (k == 2) A[l] = j;
        else if (k == 1) A[l] = (i ^ j);
        else A[l] = i;
      }
      else {
        if (k == 1) A[l] = j;
        else A[l] = i;
      }
      return;
    }

    int cost = abs(i - j), m = i ^ j;
    if (cost == 1) {
      if (k <= f(l - 1, i, m)) {
        A[l] = i;
        g(l - 1, i, m, k);
      }
      else {
        A[l] = j;
        g(l - 1, m, j, k - f(l - 1, i, m) - 1);
      }
    }
    else {
      if (k < f(l, i, m)) {
        A[l] = i;
        g(l, i, m, k);
      }
      else if (k < f(l, i, m) + f(l, m, j)) {
        A[l] = m;
        g(l, m, j, k - f(l, i, m));
      }
      else {
        fill(A, A + l + 1, j);
      }
    }
  };
  g(N, 1, 3, K);
}

void solve_M3() {
  function<__int128_t(int, int, int)> f = [&](int l, int i, int j) {
    if (l == 1) return (__int128_t)(i > j ? j - i + 3 : j - i);
    if (T[l][i][j] != -1) return T[l][i][j];

    __int128_t ret, cost = (i > j ? j - i + 3 : j - i), m = i ^ j;
    if (cost == 1) {
      ret = f(l - 1, i, m) + 1 + f(l - 1, m, j);
    }
    else {
      ret = f(l - 1, i, j) + 1 + f(l - 1, j, i) + 1 + f(l - 1, i, j);
    }
    return T[l][i][j] = ret;
  };
  function<void(int, int, int, __int128_t)> g = [&](int l, int i, int j, __int128_t k) {
    if (l == 1) {
      int cost = (i > j ? j - i + 3 : j - i);
      if (cost == 2) {
        if (k == 2) A[l] = j;
        else if (k == 1) A[l] = (i ^ j);
        else A[l] = i;
      }
      else {
        if (k == 1) A[l] = j;
        else A[l] = i;
      }
      return;
    }

    int cost = (i > j ? j - i + 3 : j - i), m = i ^ j;
    if (cost == 1) {
      if (k <= f(l - 1, i, m)) {
        A[l] = i;
        g(l - 1, i, m, k);
      }
      else {
        A[l] = j;
        g(l - 1, m, j, k - f(l - 1, i, m) - 1);
      }
    }
    else {
      if (k <= f(l - 1, i, j)) {
        A[l] = i;
        g(l - 1, i, j, k);
      }
      else if (k <= f(l - 1, i, j) + 1 + f(l - 1, j, i)) {
        A[l] = m;
        g(l - 1, j, i, k - f(l - 1, i, j) - 1);
      }
      else {
        A[l] = j;
        g(l - 1, i, j, k - f(l - 1, i, j) - 1 - f(l - 1, j, i) - 1);
      }
    }
  };
  g(N, 1, 3, K);
}

void solve() {
  ll M; string Ks; cin >> M >> N >> Ks;
  K = 0;
  for (char c : Ks) K = K * 10 + c - '0';

  memset(T, -1, sizeof T);
  fill(A, A + N + 1, 1);

  if (M == 1) solve_M1();
  else if (M == 2) solve_M2();
  else if (M == 3) solve_M3();
  else assert(false);

  for (int i = 1; i <= N; i++) cout << A[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
