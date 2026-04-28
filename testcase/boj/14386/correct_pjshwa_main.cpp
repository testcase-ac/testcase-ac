#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void proc(int N, string& S) {
  cout << S << ' ';

  for (int p = 2; p <= 10; ++p) {
    ll d = 0, pw = 1;
    for (int i = 0; i < N / 2; ++i) {
      if (S[N - 1 - i] == '1') d += pw;
      pw *= p;
    }
    cout << d << ' ';
  }
  cout << '\n';
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ":\n";

  int N, J; cin >> N >> J;
  int H = N / 2;

  for (int i1 = 1; i1 < H; ++i1) for (int i2 = i1 + 1; i2 < H; ++i2) {
    if (J-- == 0) return;

    string S(N, '0'); S[0] = S[i1] = S[i2] = '1';
    int i = i2;
    while (i >= 0) S[N - 1 - i2 + i] = S[i], --i;
    proc(N, S);
  }

  for (int i1 = 1; i1 < H; ++i1) for (int i2 = i1 + 1; i2 < H; ++i2)
  for (int i3 = i2 + 1; i3 < H; ++i3) {
    if (J-- == 0) return;

    string S(N, '0'); S[0] = S[i1] = S[i2] = S[i3] = '1';
    int i = i3;
    while (i >= 0) S[N - 1 - i3 + i] = S[i], --i;
    proc(N, S);
  }

  for (int i1 = 1; i1 < H; ++i1) for (int i2 = i1 + 1; i2 < H; ++i2)
  for (int i3 = i2 + 1; i3 < H; ++i3) for (int i4 = i3 + 1; i4 < H; ++i4) {
    if (J-- == 0) return;

    string S(N, '0'); S[0] = S[i1] = S[i2] = S[i3] = S[i4] = '1';
    int i = i4;
    while (i >= 0) S[N - 1 - i4 + i] = S[i], --i;
    proc(N, S);
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
