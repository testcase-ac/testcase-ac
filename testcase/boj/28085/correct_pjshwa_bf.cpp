#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int A[MAX], d[1 << 15][2][31];
int N;

int r(int s, int o, int t) {
  if (d[s][o][t] != -1) return d[s][o][t];
  if (t == 30) return d[s][o][t] = INF;
  if (o == 1 && s == (1 << N) - 1) return d[s][o][t] = 0;

  int ret = INF;
  for (int i = 0; i < N; i++) {
    int ci = (s >> i) & 1;
    if (o != ci) continue;
    ret = min(ret, r(s ^ (1 << i), o ^ 1, t + 1) + A[i]);

    for (int j = i + 1; j < N; j++) {
      int cj = (s >> j) & 1;
      if (o != cj || A[i] == A[j]) continue;
      int ns = s ^ (1 << i) ^ (1 << j);
      ret = min(ret, r(ns, o ^ 1, t + 1) + max(A[i], A[j]));
    }
  }
  return d[s][o][t] = ret;
}

vector<pii> T;

bool trace(int s, int o, int t) {
  if (t == 30) return false;
  if (o == 1 && s == (1 << N) - 1) return true;

  int res = d[s][o][t];
  for (int i = 0; i < N; i++) {
    int ci = (s >> i) & 1;
    if (o != ci) continue;

    if (res == d[s ^ (1 << i)][o ^ 1][t + 1] + A[i] && trace(s ^ (1 << i), o ^ 1, t + 1)) {
      T.push_back({s ^ (1 << i), o ^ 1});
      return true;
    }
    
    for (int j = i + 1; j < N; j++) {
      int cj = (s >> j) & 1;
      if (o != cj || A[i] == A[j]) continue;
      int ns = s ^ (1 << i) ^ (1 << j);

      if (res == d[ns][o ^ 1][t + 1] + max(A[i], A[j]) && trace(ns, o ^ 1, t + 1)) {
        T.push_back({ns, o ^ 1});
        return true;
      }
    }
  }
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N); memset(d, -1, sizeof(d));

  int ans = r(0, 0, 0);
  if (ans == INF) ans = -1;
  cout << ans << '\n';

  // return;

  // Backtracking
  trace(0, 0, 0);
  T.push_back({0, 0});
  reverse(T.begin(), T.end());
  for (auto [s, o] : T) {
    if (!o) cout << "o ";

    for (int i = 0; i < N; i++) {
      if (!((s >> i) & 1)) cout << A[i] << ' ';
    }
    cout << "\t\t\t||\t\t\t";
    for (int i = 0; i < N; i++) {
      if ((s >> i) & 1) cout << A[i] << ' ';
    }

    if (o) cout << " o";
    cout << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
