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

  int N, M; cin >> N >> M;

  int p[N]; iota(p, p + N, 1);
  map<int, int> sep_tal;
  map<int, vector<vector<int>>> sep_v;

  do {
    int maxx = -1, sep = 0;
    for (int i = 0; i < N; ++i) {
      maxx = max(maxx, p[i]);
      if (i + 1 == maxx) ++sep;
    }

    if (sep != 5) {

      cout << "perm = ";
      for (int i = 0; i < N; ++i) cout << p[i] << " ";
      cout << ", sep = " << sep << "\n";

    }

    sep_tal[sep]++;
    sep_v[-sep].push_back(vector<int>(p, p + N));

  } while (next_permutation(p, p + N));

  // vector<pii> V;
  // for (auto [sep, tal] : sep_tal) {
  //   V.emplace_back(sep, tal);
  // }
  // sort(V.begin(), V.end(), [&](pii a, pii b) {
  //   return a.first < b.first;
  // });
  // for (auto [sep, tal] : V) {
  //   cout << "sep = " << sep << ", tal = " << tal << "\n";
  // }

  for (auto [sep, v] : sep_v) {
    cout << "sep = " << -sep << "\n";
    for (auto p : v) {
      for (int i = 0; i < N; ++i) cout << p[i] << " ";
      cout << "\n";
    }
  }
  
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
