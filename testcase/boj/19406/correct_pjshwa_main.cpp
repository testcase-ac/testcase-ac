#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void print_winner(int x) {
  if (x == 0) cout << "Apfelmann\n";
  else cout << "Bananenfrau\n";
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  int ci;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'C') ci = i;
  }

  vector<int> L, R;
  for (int i = 0; i < ci; i++) L.push_back(S[i] - 'A');
  for (int i = N - 1; i > ci; i--) R.push_back(S[i] - 'A');

  if (L.empty()) return print_winner(R[0] ^ 1);
  if (R.empty()) return print_winner(L[0] ^ 1);
  if (L[0] == R[0]) return print_winner(L[0] ^ 1);

  bool f = L[0] == 0;
  while (!L.empty() && !R.empty()) {
    // Apfelmann turn
    if (L.back() == 0) {
      if (R.back() == 0) {
        if (f) L.pop_back();
        else R.pop_back();
      }
      else L.pop_back();
    }
    else {
      if (R.back() == 0) R.pop_back();
    }

    if (L.empty() || R.empty()) break;

    // Bananenfrau turn
    if (L.back() == 1) {
      if (R.back() == 1) {
        if (f) R.pop_back();
        else L.pop_back();
      }
      else L.pop_back();
    }
    else {
      if (R.back() == 1) R.pop_back();
    }
  }

  if (L.empty()) return print_winner(R[0] ^ 1);
  if (R.empty()) return print_winner(L[0] ^ 1);
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
