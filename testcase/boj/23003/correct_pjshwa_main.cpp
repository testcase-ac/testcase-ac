#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; string S;
  cin >> N >> S;
  for (int i = 0; i < N; i++) {
    char l = S[i]; int acc = 1;
    for (int j = i - 1; j >= 0; j--) {
      if (S[j] < l) {
        acc++;
        l = S[j];
      }
      else break;
    }
    cout << acc << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
