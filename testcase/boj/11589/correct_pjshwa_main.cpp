#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> graph[5001];
pair<pii, pii> coords[5001];
int indegree[5001];
int main() {
  fast_io();

  int n;
  double x1, y1, x2, y2, x3, y3, x4, y4;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> \
    coords[i].first.first >> \
    coords[i].first.second >> \
    coords[i].second.first >> \
    coords[i].second.second;
  }

  for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
    tie(x1, y1) = coords[i].first;
    tie(x2, y2) = coords[i].second;
    tie(x3, y3) = coords[j].first;
    tie(x4, y4) = coords[j].second;

    if (
      (min(x3, x4) >= min(x1, x2) && min(x3, x4) <= max(x1, x2)) ||
      (min(x1, x2) >= min(x3, x4) && min(x1, x2) <= max(x3, x4))
     ) {
      bool iOverj;

      if (x3 == x4) {
        if (x1 == x2) iOverj = min(y1, y2) >= max(y3, y4);
        else {
          double ai = (y2 - y1) / (x2 - x1);
          double yi = ai * (x3 - x1) + y1;
          iOverj = yi >= max(y3, y4);
        }
      }
      else if (x1 == x2) {
        double aj = (y4 - y3) / (x4 - x3);
        double yj = aj * (x1 - x3) + y3;
        iOverj = min(y1, y2) >= yj;
      }
      else {
        double ai = (y2 - y1) / (x2 - x1);
        double aj = (y4 - y3) / (x4 - x3);
        double xp;
        if (x1 >= min(x3, x4) && x1 <= max(x3, x4)) xp = x1;
        if (x2 >= min(x3, x4) && x2 <= max(x3, x4)) xp = x2;
        if (x3 >= min(x1, x2) && x3 <= max(x1, x2)) xp = x3;
        if (x4 >= min(x1, x2) && x4 <= max(x1, x2)) xp = x4;

        double yi = ai * (xp - x1) + y1;
        double yj = aj * (xp - x3) + y3;
        iOverj = yi >= yj;
      }

      if (iOverj) {
        graph[j].push_back(i);
        indegree[i]++;
      }
      else {
        graph[i].push_back(j);
        indegree[j]++;
      }
    }
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }

  vector<int> ans;
  int a;
  for (int i = 1; i <= n; i++) {
    a = q.front();
    ans.push_back(a);
    q.pop();

    for (int y : graph[a]) {
      if (!--indegree[y]) q.push(y);
    }
  }

  for (int el : ans) cout << el << ' ';
}
