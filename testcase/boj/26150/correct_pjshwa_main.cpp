#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<tuple<string, int, int>> V;
  for (int i = 0; i < N; i++) {
    string S;
    int A, B;
    cin >> S >> A >> B;
    V.emplace_back(S, A, B);
  }
  sort(V.begin(), V.end(), [](auto a, auto b) {
    auto [S1, A1, B1] = a;
    auto [S2, A2, B2] = b;
    return A1 < A2;
  });

  for (int i = 0; i < N; i++) {
    auto [S, A, B] = V[i];
    char c = S[B - 1];
    if ('a' <= c && c <= 'z') c = c - 'a' + 'A';
    cout << c;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
