#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MAXV = 3e6;
int A[MAX], G[MAXV + 1];
bool C[20];
vector<int> fib{1, 1};

void solve() {
  int N;
  cin >> N;

  int x = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    x ^= G[A[i]];
  }

  if (x == 0) cout << "cubelover\n";
  else cout << "koosaga\n";
}

int main() {
  fast_io();

  while (1) {
    int f1 = fib.back(); fib.pop_back();
    int f2 = fib.back(); fib.pop_back();
    int f3 = f1 + f2;

    fib.push_back(f2);
    fib.push_back(f1);
    fib.push_back(f3);

    if (f3 > MAXV) break;
  }

  G[0] = 0;
  for (int i = 1; i <= MAXV; i++) {
    memset(C, 0, sizeof(C));

    for (int f : fib) {
      if (f > i) break;
      C[G[i - f]] = true;
    }

    int mex = 0;
    while (C[mex]) mex++;
    G[i] = mex;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
