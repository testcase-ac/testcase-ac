#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 4000, INF = 0x3f3f3f3f;
int A[MAXN], PO[MAXN], PE[MAXN], N;
int Cost[2][MAXN], dp[MAXN][2];

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N, greater<int>());
  if (N <= 4) return cout << 2 * (A[0] + A[1]) << '\n', void();

  PE[0] = A[0];
  for (int i = 1; i < N; ++i) {
    PO[i] = PO[i - 1];
    if (i % 2 == 1) PO[i] += A[i];
    PE[i] = PE[i - 1];
    if (i % 2 == 0) PE[i] += A[i];
  }

  memset(Cost, -1, sizeof(Cost));
  for (int i = 0; i + 1 < N; i += 2) {
    int min_area_i = INF, max_area_j = -INF, ok = 0;
    for (int j = i + 2; j + 1 < N; j += 2) {
      int area_i = (PE[i] + A[i + 1]) * 2 + PO[j] - PO[i + 1] + PE[N - 1] - PE[j];
      int area_j = (PO[i] + PE[j] - PE[i] + A[j + 1]) * 2 + PO[N - 1] - PO[j + 1];
      if (area_j > max_area_j) {
        max_area_j = area_j;
        min_area_i = area_i;
      } else {
        min_area_i = min(min_area_i, area_i);
      }
      ok = 1;
    }
    if (!ok) continue;
    Cost[0][i] = min_area_i;
    Cost[1][i] = max_area_j;
  }
  for (int j = 1; j + 1 < N; j += 2) {
    int min_area_j = INF, max_area_i = -INF, ok = 0;
    for (int i = j + 2; i + 1 < N; i += 2) {
      int area_j = (PO[j] + A[j + 1]) * 2 + PE[i] - PE[j + 1] + PO[N - 1] - PO[i];
      int area_i = (PE[j] + PO[i] - PO[j] + A[i + 1]) * 2 + PE[N - 1] - PE[i + 1];
      if (area_i > max_area_i) {
        max_area_i = area_i;
        min_area_j = area_j;
      } else {
        min_area_j = min(min_area_j, area_j);
      }
      ok = 1;
    }
    if (!ok) continue;
    Cost[0][j] = max_area_i;
    Cost[1][j] = min_area_j;
  }

  int maxs[2] = {0, 0};
  for (int i = N - 1; i >= 0; --i) {
    int p = i % 2;
    if (Cost[p][i] == -1) continue;

    if (Cost[p][i] > maxs[p]) {
      maxs[0] = Cost[0][i];
      maxs[1] = Cost[1][i];
    } else if (Cost[1 - p][i] < maxs[1 - p]) {
      maxs[1 - p] = Cost[1 - p][i];
    }
  }

  // cout << "Cost = \n";
  // for (int i = 0; i < N; ++i) {
  //   cout << i << ": ";
  //   for (int j = 0; j < 2; ++j) {
  //     cout << Cost[j][i] << ' ';
  //   }
  //   cout << '\n';
  // }

  cout << maxs[0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
