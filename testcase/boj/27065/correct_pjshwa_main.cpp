#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
int A[MAX + 1], B[MAX + 1], C[MAX + 1];

void solve() {
  int N;
  cin >> N;

  if (C[N]) cout << "Good Bye\n";
  else cout << "BOJ 2022\n";
}

int main() {
  fast_io();

  for (int i = 1; i <= MAX; i++) {
    for (int j = i + i; j <= MAX; j += i) A[j] += i;
  }

  for (int i = 1; i <= MAX; i++) {
    if (A[i] > i) B[i] = 1;
    else if (A[i] < i) B[i] = -1;
    else B[i] = 0;
  }

  for (int i = 1; i <= MAX; i++) {
    if (B[i] != 1) continue;

    bool f = true;
    for (int j = 1; j < i; j++) {
      if (i % j) continue;
      if (B[j] == 1) f = false;
    }

    if (f) C[i] = 1;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
