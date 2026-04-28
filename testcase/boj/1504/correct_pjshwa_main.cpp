#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 6e8;
int cdist[801];
vector<pii> graph[801];

int main() {
  fast_io();

  int v, e, ui, vi, wi, di, v1, v2, k;
  cin >> v >> e;

  while (e--) {
    cin >> ui >> vi >> wi;
    graph[ui].push_back({wi, vi});
    graph[vi].push_back({wi, ui});
  }

  cin >> v1 >> v2;

  int ans1 = 0, ans2 = 0;
  for (int dt = 0; dt < 6; dt++) {
    if (dt == 0) k = 1;
    else if (dt == 1) k = v1;
    else if (dt == 2) k = v2;
    else if (dt == 3) k = 1;
    else if (dt == 4) k = v2;
    else if (dt == 5) k = v1;

    for (int i = 1; i <= v; i++) cdist[i] = MAX;
    cdist[k] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
      tie(wi, ui) = pq.top();
      pq.pop();

      for (auto &p : graph[ui]) {
        tie(di, vi) = p;
        if (cdist[vi] > di + wi) {
          cdist[vi] = di + wi;
          pq.push({cdist[vi], vi});
        }
      }
    }
    
    if (dt == 0) ans1 += cdist[v1];
    else if (dt == 1) ans1 += cdist[v2];
    else if (dt == 2) ans1 += cdist[v];
    else if (dt == 3) ans2 += cdist[v2];
    else if (dt == 4) ans2 += cdist[v1];
    else if (dt == 5) ans2 += cdist[v];
  }

  int ans = min(ans1, ans2);
  if (ans >= MAX) cout << "-1\n";
  else cout << ans << '\n';
}
