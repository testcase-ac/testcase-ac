#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 250;
int board[MAXN][MAXN], N;
vector<tuple<int, int, int, int>> history;

void process(int i1, int j1, int i2, int j2) {
  history.emplace_back(i1 + 1, j1 + 1, i2 + 1, j2 + 1);
  for (int i = i1; i <= i2; ++i) for (int j = j1; j <= j2; ++j) {
    board[i][j] ^= 1;
  }
}

void print() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << board[i][j];
    cout << '\n';
  }
}

void solve() {
  cin >> N;
  vector<pii> diffs;
  for (int i = 0; i <= N; ++i) {
    if (i < N) {
      string S; cin >> S;
      for (int j = 0; j < N; ++j) board[i][j] = S[j] == '1';
    }

    int cnt = 0;
    for (int j = 0; j < N; ++j) {
      if (i == 0) cnt += board[i][j] == 1;
      else if (i == N) cnt += board[i - 1][j] == 1;
      else cnt += board[i][j] != board[i - 1][j];
    }
    diffs.emplace_back(cnt, i);
  }
  sort(diffs.begin(), diffs.end(), greater<pii>());

  for (int i = 0; i < N; i += 2) {
    int dif1 = diffs[i].first, dif2 = diffs[i + 1].first;
    if (dif1 + dif2 < N) break;

    int i1 = diffs[i].second, i2 = diffs[i + 1].second;
    if (i1 > i2) swap(i1, i2);
    process(i1, 0, i2 - 1, N - 1);
  }

  for (int j = 0; j < N; ++j) {
    int flag = 0, si;
    for (int i = 0; i <= N; ++i) {
      int val = i == N ? 0 : board[i][j];
      if (!flag && val == 1) {
        flag = 1;
        si = i;
      } else if (flag && val == 0) {
        process(si, j, i - 1, j);
        flag = 0;
      }
    }
  }

  int ok = 1, z = (N + 2) / 2;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) ok &= board[i][j] == 0;
  assert(ok && (int)history.size() <= z * z);

  cout << history.size() << '\n';
  for (auto [i1, j1, i2, j2] : history) {
    cout << i1 << ' ' << j1 << ' ' << i2 << ' ' << j2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
