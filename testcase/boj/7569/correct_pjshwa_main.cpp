#include <bits/stdc++.h>
#define v1 vector<int>
#define v2 vector<vector<int>>
#define v3 vector<vector<vector<int>>>
#define t3 tuple<int, int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int m, n, o, mv = 0, utomato = 0;
queue<pair<t3, int>> q;
v3 farm;

void bfs() {
  while (!q.empty()) {
    auto[p, it] = q.front();
    auto[oi, ni, mi] = p;
    mv = max(mv, it);
    q.pop();

    if (mi > 0 && farm[oi][ni][mi - 1] == 0) {
      utomato--;
      farm[oi][ni][mi - 1] = 1;
      q.push({{oi, ni, mi - 1}, it + 1});
    }
    if (ni > 0 && farm[oi][ni - 1][mi] == 0) {
      utomato--;
      farm[oi][ni - 1][mi] = 1;
      q.push({{oi, ni - 1, mi}, it + 1});
    }
    if (oi > 0 && farm[oi - 1][ni][mi] == 0) {
      utomato--;
      farm[oi - 1][ni][mi] = 1;
      q.push({{oi - 1, ni, mi}, it + 1});
    }

    if (mi < m - 1 && farm[oi][ni][mi + 1] == 0) {
      utomato--;
      farm[oi][ni][mi + 1] = 1;
      q.push({{oi, ni, mi + 1}, it + 1});
    }
    if (ni < n - 1 && farm[oi][ni + 1][mi] == 0) {
      utomato--;
      farm[oi][ni + 1][mi] = 1;
      q.push({{oi, ni + 1, mi}, it + 1});
    }
    if (oi < o - 1 && farm[oi + 1][ni][mi] == 0) {
      utomato--;
      farm[oi + 1][ni][mi] = 1;
      q.push({{oi + 1, ni, mi}, it + 1});
    }
  }
}


int main() {
  fast_io();

  cin >> m >> n >> o;

  int e;
  for (int oi = 0; oi < o; oi++) {
    v2 he;
    for (int ni = 0; ni < n; ni++) {
      v1 ne;
      for (int mi = 0; mi < m; mi++) {
        cin >> e, ne.push_back(e);
        if (!e) utomato++;
      }
      he.push_back(ne);
    }
    farm.push_back(he);
  }

  for (int mi = 0; mi < m; mi++) for (int ni = 0; ni < n; ni++) for (int oi = 0; oi < o; oi++) {
    if (farm[oi][ni][mi] == 1) q.push({{oi, ni, mi}, 0});
  }
  bfs();

  if (utomato) cout << -1;
  else cout << mv;
}
