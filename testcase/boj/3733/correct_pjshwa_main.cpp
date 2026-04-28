#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int N, S;
  while (cin >> N >> S) {
    cout << S / (N + 1) << '\n';
  }
}
