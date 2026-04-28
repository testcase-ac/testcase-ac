#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void inc(vector<int>& a) {
  a[N - 1]++;
  for (int i = N - 1; i >= 0; i--) {
    if (a[i] == 26) {
      a[i] = 0;
      if (i > 0) a[i - 1]++;
    }
  }
}

void print(vector<int>& a) {
  for (int i = 0; i < N; i++) cout << (char)(a[i] + 'a');
  cout << '\n';
}

void solve() {
  string K, Ss, Ts; cin >> N >> K >> Ss >> Ts;

  vector<int> S, T; int ki = K[0] - 'a';
  for (int i = 0; i < N; i++) {
    S.push_back(Ss[i] - 'a');
    T.push_back(Ts[i] - 'a');
  }

  for (int it = 0; it < 26; it++) {
    inc(S);
    if (S == T) return cout << "NO\n", void();

    bool f = false;
    for (int i = 0; i < N; i++) f |= S[i] == ki;
    if (f) return print(S);
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
