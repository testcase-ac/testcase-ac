#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX];

void solve() {
  int N;
  cin >> N;

  int x = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];

    int g = A[i];
    if (A[i] % 8 == 0) g--;
    if (A[i] % 8 == 7) g++;
    x ^= g;
  }

  if (x == 0) cout << "Second\n";
  else cout << "First\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
