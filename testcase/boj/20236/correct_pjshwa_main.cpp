#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;
using pii = pair<int, int>;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<int> ans;
vector<int> zfe;
vector<pii> graph[MAX];
stack<int> traj;
int in[MAX], out[MAX], nxt[MAX];
int c;
bool first = true;

void dfs(int s, int ei) {
  while (nxt[s] < graph[s].size()) {
    auto [d, x] = graph[s][nxt[s]];
    nxt[s]++;
    dfs(d, x);
  }

  if (ei != -1) traj.push(ei);
}

int main() {
  fast_io();

  int n;
  cin >> n >> c;
  vector<tuple<int, int, int>> wait;
  vector<int> points;
  for (int i = 1; i <= n; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    if (w == 0) {
      if (a == c) zfe.push_back(i);
      else ans.push_back(i);
    }
    else {
      if (a == b && a == c) ans.push_back(i);
      else {
        points.push_back(a);
        points.push_back(b);
        wait.emplace_back(a, b, i);
      }
    }
  }

  points.push_back(c);
  compress(points);
  for (auto [a, b, i] : wait) {
    int na = getidx(points, a);
    int nb = getidx(points, b);
    in[nb]++;
    out[na]++;
    graph[na].push_back({nb, i});
  }
  c = getidx(points, c);

  bool able = true;
  int pc = 0;
  for (int i = 0; i < MAX; i++) {
    if (i == c) continue;

    if (in[i] - out[i] == 1) pc++;
    else if (in[i] - out[i] != 0) able = false;
  }

  able &= ((pc == 1 && in[c] + 1 == out[c]) || (pc == 0 && in[c] == out[c]));

  if (able) {
    dfs(c, -1);
    bool first = true;
    while (!traj.empty()) {
      ans.push_back(traj.top());
      if (first) {
        first = false;
        for (int e : zfe) ans.push_back(e);
      }
      traj.pop();
    }

    if (ans.size() == n) {
      cout << "Yes\n";
      for (int e : ans) cout << e << ' ';
    }
    else cout << "No\n";
  }
  else cout << "No\n";
}
