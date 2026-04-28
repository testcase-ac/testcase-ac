#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int H, W; cin >> H >> W;

  vector<vector<int>> A(H, vector<int>(W));
  for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) cin >> A[i][j];

  vector<int> dL(W), dR(W);

  function<int(int, vector<int>&)> Find = [&](int a, vector<int>& parent) {
    if (parent[a] == a) return a;
    return parent[a] = Find(parent[a], parent);
  };
  function<void(int, int, vector<int>&)> Union = [&](int a, int b, vector<int>& parent) {
    a = Find(a, parent), b = Find(b, parent);
    if (a == b) return;
    parent[a] = b;
  };

  {
    int siz = 0;
    vector<int> parent(H * W);
    iota(parent.begin(), parent.end(), 0);

    for (int j = 0; j < W; j++) {
      siz++;
      for (int i = 1; i < H; i++) {
        if (A[i][j] == A[i - 1][j]) {
          Union(i * W + j, (i - 1) * W + j, parent);
        }
        else siz++;
      }

      if (j > 0) {
        for (int i = 0; i < H; i++) {
          if (A[i][j] == A[i][j - 1] && Find(i * W + j, parent) != Find(i * W + j - 1, parent)) {
            siz--;
            Union(i * W + j, i * W + j - 1, parent);
          }
        }
      }

      dL[j] = siz;
    }
  }
  {
    int siz = 0;
    vector<int> parent(H * W);
    iota(parent.begin(), parent.end(), 0);

    for (int j = W - 1; j >= 0; j--) {
      siz++;
      for (int i = 1; i < H; i++) {
        if (A[i][j] == A[i - 1][j]) {
          Union(i * W + j, (i - 1) * W + j, parent);
        }
        else siz++;
      }

      if (j < W - 1) {
        for (int i = 0; i < H; i++) {
          if (A[i][j] == A[i][j + 1] && Find(i * W + j, parent) != Find(i * W + j + 1, parent)) {
            siz--;
            Union(i * W + j, i * W + j + 1, parent);
          }
        }
      }

      dR[j] = siz;
    }
  }

  int ans = INF;
  for (int j = 0; j < W - 1; j++) {
    ans = min(ans, dL[j] + dR[j + 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
