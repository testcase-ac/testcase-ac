#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int sum = 0;
  for (char c : S) sum += c - '0';

  for (int i = 0; i < N; ++i) {
    int pre = S[i] - '0';
    for (int nxt = 1; nxt <= 9; ++nxt) {
      if (pre == nxt) continue;
      int nsum = sum - pre + nxt;
      if (nsum > 3 && nsum % 3 == 0) {
        S[i] = nxt + '0';
        cout << S << ' ' << "3\n";
        S[i] = pre + '0';
        break;
      }
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
