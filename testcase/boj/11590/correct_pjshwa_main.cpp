#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e6;
int pi[MAXN];
vector<string> A;

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S; 
    A.push_back(S);
  }
  sort(A.begin(), A.end(), [](const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
  });

  for (int i = 0; i < N; ++i) {
    string S = A[i];
    int Z = S.size();

    for (int i = 1, j = 0; i < Z; ++i) {
      while (j && S[i] != S[j]) j = pi[j - 1];
      if (S[i] == S[j]) pi[i] = ++j;
    }

    cout << "i = " << i << ", S = " << S << ", pi = ";
    for (int k = 0; k < Z; ++k) cout << pi[k] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
