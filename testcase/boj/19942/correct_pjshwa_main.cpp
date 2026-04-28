#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 15, INF = 1e9 + 7;
int p[MAX], s[MAX], f[MAX], v[MAX], c[MAX];
int lp, ls, lf, lv;
int ap, as, af, av;
int mprice = INF, cprice;
vector<int> ans, current;
int n;

void dfs(int i) {
  if (i == n) {
    if (ap >= lp && as >= ls && af >= lf && av >= lv) {
      if (cprice < mprice) {
        mprice = cprice;
        ans = current;
      }
      else if (cprice == mprice) {
        int x = min(current.size(), ans.size());
        for (int i = 0; i < x; i++) {
          if (current[i] < ans[i]) {
            ans = current;
            break;
          }
        }
      }
    }
    return;
  }

  dfs(i + 1);
  ap += p[i], as += s[i], af += f[i], av += v[i], cprice += c[i];
  current.push_back(i);
  dfs(i + 1);
  ap -= p[i], as -= s[i], af -= f[i], av -= v[i], cprice -= c[i];
  current.pop_back();
}

void solve() {
  cin >> n >> lp >> ls >> lf >> lv;
  for (int i = 0; i < n; i++) cin >> p[i] >> s[i] >> f[i] >> v[i] >> c[i];
  dfs(0);

  if (mprice == INF) cout << "-1\n";
  else {
    cout << mprice << '\n';
    for (int e : ans) cout << e + 1 << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
