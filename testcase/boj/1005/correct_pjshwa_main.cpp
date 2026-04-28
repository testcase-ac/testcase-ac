#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int times[100001];
int dp[100001];
vector<int> r_graph[100001];

int min_time(int node) {
  if (dp[node] == -1) {
    int mt_children = 0;
    for (int &child : r_graph[node]) mt_children = max(mt_children, min_time(child));
    dp[node] = mt_children + times[node];
  }
  return dp[node];
}

int main() {
  fast_io();

  int t, n, k, x, y, w;
  cin >> t;

  while (t--) {
    cin >> n >> k;

    // Initialization
    for (int i = 1; i <= n; i++) r_graph[i].clear();
    memset(dp, -1, sizeof(dp));

    for (int i = 1; i <= n; i++) cin >> times[i];
    for (int i = 0; i < k; i++) {
      cin >> x >> y;
      r_graph[y].push_back(x);
    }
    cin >> w;
    cout << min_time(w) << '\n';
  }
}
