#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 2000;
ll lp[MAX + 1];

vector<int> graph[50];
int ma[50], mb[50];
bool vis[50];
int sa, sb;

bool dfs(int a) {
  vis[a] = true;
  for (int b : graph[a]) {
    if (b == sa || b == sb) continue;

    // 반대편이 매칭되지 않았거나
    // 매칭되어 있었지만 원래 매칭되어 있던 정점을 다른 정점과 매칭시킬 수 있으면 성공
    if (mb[b] == -1 || !vis[mb[b]] && dfs(mb[b])) {
      ma[a] = b;
      mb[b] = a;
      return true;
    }
  }
  // 매칭 실패
  return false;
}

int main() {
  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int n;
  cin >> n;

  vector<int> a, oi, ei;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] & 1) oi.push_back(i);
    else ei.push_back(i);
  }
  if (oi.size() != ei.size()) {
    cout << "-1\n";
    return 0;
  }

  int s;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      s = a[i] + a[j];
      if (lp[s] == s) {
        graph[i].push_back(j);
        graph[j].push_back(i);
      }
    }
  }

  int match;
  vector<int> ans;
  for (int b : graph[0]) {
    memset(ma, -1, sizeof ma);
    memset(mb, -1, sizeof mb);

    sa = 0;
    sb = b;
    match = 1;

    if (oi[0] == 0) {
      for (int i = 1; i < oi.size(); i++) {
        memset(vis, false, sizeof vis);
        if (dfs(oi[i])) match++;
      }
    }
    else {
      for (int i = 1; i < ei.size(); i++) {
        memset(vis, false, sizeof vis);
        if (dfs(ei[i])) match++;
      }
    }

    if (match == n / 2) ans.push_back(a[b]);
  }

  if (ans.size()) {
    sort(ans.begin(), ans.end());
    for (auto el : ans) cout << el << ' ';
  }
  else cout << -1;
  cout << '\n';
}
