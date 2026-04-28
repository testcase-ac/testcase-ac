#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll f(vector<int>& v) {
  ll ret = 0, Z = v.size();

  // returns number in base Z
  for (int i = 0; i < Z; ++i) {
    ret *= Z;
    ret += v[i];
  }

  return ret;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    B[i] = i + 1;
  }
  if (A == B) {
    cout << "0\n";
    return;
  }

  queue<vector<int>> Q;
  map<ll, int> cdist;
  Q.push(A); cdist[f(A)] = 0;

  while (!Q.empty()) {
    auto cur = Q.front(); Q.pop();
    int dist = cdist[f(cur)];

    // choose 2 consecutive chunks and swap them
    // [i, j], [j + 1, k]
    vector<int> nA(N);
    for (int i = 0; i < N; ++i) {
      for (int j = i; j < N; ++j) {
        for (int k = j + 1; k < N; ++k) {
          int it = 0;
          for (int l = 0; l < i; ++l) nA[it++] = cur[l];
          for (int l = j + 1; l <= k; ++l) nA[it++] = cur[l];
          for (int l = i; l <= j; ++l) nA[it++] = cur[l];
          for (int l = k + 1; l < N; ++l) nA[it++] = cur[l];

          if (!cdist.count(f(nA))) {
            cdist[f(nA)] = dist + 1;
            if (nA == B) {
              cout << dist + 1 << '\n';
              return;
            }
            if (cdist[f(nA)] < 2) Q.push(nA);
          }
        }
      }
    }
  }

  map<ll, int> rdist;
  Q.push(B); rdist[f(B)] = 0;

  while (!Q.empty()) {
    auto cur = Q.front(); Q.pop();
    int dist = rdist[f(cur)];

    // choose 2 consecutive chunks and swap them
    // [i, j], [j + 1, k]
    vector<int> nB(N);
    for (int i = 0; i < N; ++i) {
      for (int j = i; j < N; ++j) {
        for (int k = j + 1; k < N; ++k) {
          int it = 0;
          for (int l = 0; l < i; ++l) nB[it++] = cur[l];
          for (int l = j + 1; l <= k; ++l) nB[it++] = cur[l];
          for (int l = i; l <= j; ++l) nB[it++] = cur[l];
          for (int l = k + 1; l < N; ++l) nB[it++] = cur[l];

          if (!rdist.count(f(nB))) {
            rdist[f(nB)] = dist + 1;
            if (cdist.count(f(nB))) {
              cout << dist + 1 + cdist[f(nB)] << '\n';
              return;
            }
            if (rdist[f(nB)] < 2) Q.push(nB);
          }
        }
      }
    }

  }

  cout << "5 or more\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
