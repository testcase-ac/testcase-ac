#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX][MAX], rmin[MAX], rmax[MAX], cmin[MAX], cmax[MAX];
vector<int> rd[MAX], cd[MAX], ru[MAX], cu[MAX];

void solve() {
  int N, M, S;
  cin >> N >> M >> S;

  memset(rmin, -1, sizeof(rmin));
  memset(rmax, -1, sizeof(rmax));
  memset(cmin, -1, sizeof(cmin));
  memset(cmax, -1, sizeof(cmax));

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    cin >> A[i][j];
    rmin[A[i][j]] = rmin[A[i][j]] == -1 ? i : min(rmin[A[i][j]], i);
    rmax[A[i][j]] = rmax[A[i][j]] == -1 ? i : max(rmax[A[i][j]], i);
    cmin[A[i][j]] = cmin[A[i][j]] == -1 ? j : min(cmin[A[i][j]], j);
    cmax[A[i][j]] = cmax[A[i][j]] == -1 ? j : max(cmax[A[i][j]], j);
  }

  vector<int> rs, cs;
  int ccnt = 0;
  for (int i = 1; i <= 256; i++) {
    if (rmin[i] == -1) continue;
    ccnt++;

    rs.push_back(rmin[i]); rs.push_back(rmax[i]);
    cs.push_back(cmin[i]); cs.push_back(cmax[i]);

    rd[rmin[i]].push_back(i); ru[rmax[i]].push_back(i);
    cd[cmin[i]].push_back(i); cu[cmax[i]].push_back(i);
  }
  compress(rs); compress(cs);

  for (int e : rs) cout << e << ' '; cout << '\n';
  for (int e : cs) cout << e << ' '; cout << '\n';

  int cz = cs.size(), rz = rs.size(), ans = 0;
  for (int i = 0; i < cz; i++) {
    set<int> in, out;
    for (int j = 0; j < i; j++) {
      for (int e : cd[cs[j]]) out.insert(e);
    }

    for (int j = i; j < cz; j++) {
      for (int e : cu[cs[j]]) {
        if (!out.count(e)) in.insert(e);
      }

      int h = cs[j] - cs[i] + 1, r = 0;
      if (h > S) break;

      set<int> rin, rout;
      for (int l = 0; l < rz; l++) {
        assert(l <= r);
        while (r < rz && h * (rs[r] - rs[l] + 1) <= S) {
          for (int e : ru[rs[r]]) {
            if (in.count(e) && !rout.count(e)) rin.insert(e);
          }
          r++;
        }

        ans = max(ans, (int)rin.size());
        for (int e : rd[rs[l]]) rin.erase(e), rout.insert(e);
      }
    }
  }

  cout << ccnt - ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
