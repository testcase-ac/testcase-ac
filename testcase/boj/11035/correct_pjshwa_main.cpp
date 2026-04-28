#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, K;
void solve() {
  vector<bool> sieve(N + 1, false);
  int cnt = 0;

  for (int i = 2; i <= N; i++) {
    if (sieve[i]) continue;

    for (int j = i; j <= N; j += i) {
      if (sieve[j]) continue;

      cnt++;
      sieve[j] = true;
      if (cnt == K) return cout << j << '\n', void();
    }
  }
}

int main() {
  fast_io();

  while (cin >> N >> K) solve();
}
