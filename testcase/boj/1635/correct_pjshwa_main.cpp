#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void print(vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << ' ';
  }
  cout << '\n';
}

void solve() {
  int M, N;
  cin >> M >> N;

  vector<vector<int>> A(N, vector<int>(M));
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> A[i][j];

  vector<vector<int>> T;
  for (int i = 0; i < N; i++) {
    vector<int> v;
    for (int j = 0; j < M - i; j++) v.push_back(1);
    while (v.size() < M) v.push_back(-1);
    T.push_back(v);
  }

  for (int i = 0; i < N; i++) {
    bool found = false;
    for (auto& v : T) {
      int d = 0;
      for (int j = 0; j < M; j++) {
        if (v[j] != A[i][j]) d++;
      }
      if (d == M / 2) {
        print(v);
        found = true;
        break;
      }
    }

    assert(found);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
