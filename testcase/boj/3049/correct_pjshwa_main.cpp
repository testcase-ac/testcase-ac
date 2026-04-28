#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int N;
  cin >> N;

  int ans = 1;
  for (int i = 1; i <= 4; i++) {
    ans *= (N - i + 1);
    ans /= i;
  }

  // Pentatope number
  cout << ans << '\n';
}
