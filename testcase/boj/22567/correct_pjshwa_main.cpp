#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MAXV = 1e6;
int rno_u[MAXV + 1], cno_u[MAXV + 1];
int rno_v[MAXV + 1], cno_v[MAXV + 1];
int rcnt_u[MAX], rcnt_v[MAX];
int ccnt_u[MAX], ccnt_v[MAX];
int diag_u_l = 0, diag_u_r = 0, diag_v_l = 0, diag_v_r = 0;

void solve() {
  int n, u, v, m;
  cin >> n >> u >> v >> m;

  memset(rno_u, -1, sizeof(rno_u));
  memset(cno_u, -1, sizeof(cno_u));
  memset(rno_v, -1, sizeof(rno_v));
  memset(cno_v, -1, sizeof(cno_v));

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int x;
    cin >> x;
    rno_u[x] = i;
    cno_u[x] = j;
  }
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int x;
    cin >> x;
    rno_v[x] = i;
    cno_v[x] = j;
  }

  // assert(n > 1);

  int ucnt = 0, vcnt = 0;
  while (m--) {
    int k;
    cin >> k;

    if (rno_u[k] != -1) {
      int i = rno_u[k], j = cno_u[k];

      rcnt_u[i]++;
      ccnt_u[j]++;
      if (i == j) diag_u_l++;
      if (i + j == n - 1) diag_u_r++;

      if (rcnt_u[i] == n) ucnt++, rcnt_u[i] = 0;
      if (ccnt_u[j] == n) ucnt++, ccnt_u[j] = 0;
      if (diag_u_l == n) ucnt++, diag_u_l = 0;
      if (diag_u_r == n) ucnt++, diag_u_r = 0;
    }
    if (rno_v[k] != -1) {
      int i = rno_v[k], j = cno_v[k];

      rcnt_v[i]++;
      ccnt_v[j]++;
      if (i == j) diag_v_l++;
      if (i + j == n - 1) diag_v_r++;

      if (rcnt_v[i] == n) vcnt++, rcnt_v[i] = 0;
      if (ccnt_v[j] == n) vcnt++, ccnt_v[j] = 0;
      if (diag_v_l == n) vcnt++, diag_v_l = 0;
      if (diag_v_r == n) vcnt++, diag_v_r = 0;
    }

    if (n == 1) {
      ucnt = min(ucnt, 1);
      vcnt = min(vcnt, 1);
    }

    if (ucnt >= u && vcnt < v) return cout << "USAGI\n", void();
    if (vcnt >= v && ucnt < u) return cout << "NEKO\n", void();
    if (ucnt >= u && vcnt >= v) break;
  }

  cout << "DRAW\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
