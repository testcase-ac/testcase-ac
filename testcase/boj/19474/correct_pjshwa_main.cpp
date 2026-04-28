#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using uii = unordered_map<int, int>;

const int MAX = 3000, MOD = 998244353;
vector<int> graph[MAX + 1];
bool vis[MAX + 1];
int n;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

uii dfs(int v) {
  vis[v] = true;

  uii ret, addend;

  for (int d : graph[v]) {
    if (!vis[d]) {
      ret[1]++;
      uii res = dfs(d);
      for (auto [k1, v1] : addend) for (auto [k2, v2] : res) {
        ret[k1 + k2 + 2] += 8 * (v1 + v2);
      }
      for (auto [k2, v2] : res) {
        ret[k2] += v2;
        ret[k2 + 1] += 2 * v2;
        addend[k2] += v2;
      }
    }
  }

  return ret;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  uii a = dfs(1);
  for (auto [k, v] : a) {
    cout << "k: " << k << ", v: " << v << endl;
  }
}
