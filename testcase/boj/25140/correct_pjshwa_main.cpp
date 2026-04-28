#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

void solve() {
  string B[3][3], I = "";
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    cin >> B[i][j];
    if (B[i][j] == "X") I += "0";
    else I += B[i][j];
  }

  string E = "123456780";
  queue<string> q;
  map<string, int> cdist;
  map<string, pair<string, int>> from;
  q.push(I);
  cdist[I] = 0;
  from[I] = {"", -1};

  while (!q.empty()) {
    string C = q.front(); q.pop();
    if (C == E) break;

    string B[3][3]; int xi, xj;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
      B[i][j] = C[i * 3 + j];
      if (B[i][j] == "0") xi = i, xj = j;
    }

    for (int k = 0; k < 4; k++) {
      int ni = xi + dx[k], nj = xj + dy[k];
      if (ni < 0 || ni >= 3 || nj < 0 || nj >= 3) continue;
      swap(B[xi][xj], B[ni][nj]);

      string N = "";
      for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) N += B[i][j];

      if (!cdist.count(N) || cdist[N] > cdist[C] + 1) {
        cdist[N] = cdist[C] + 1;
        from[N] = {C, stoi(B[xi][xj])};
        q.push(N);
      }
      swap(B[xi][xj], B[ni][nj]);
    }
  }

  cout << cdist[E] << '\n';
  if (cdist[E] == 0) return;

  stack<int> traj;
  while (from[E].second != -1) {
    traj.push(from[E].second);
    E = from[E].first;
  }
  while (!traj.empty()) {
    cout << traj.top() << ' ';
    traj.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
