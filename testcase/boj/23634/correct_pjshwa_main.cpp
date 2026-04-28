#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;


void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
char board[MAX + 1][MAX + 1], oboard[MAX + 1][MAX + 1];
bool vis[MAX * MAX];
int parent[MAX * MAX];
int n, m;

void bcopy() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      board[i][j] = oboard[i][j];
    }
  }
}

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> oboard[i];
  for (int i = 0; i < n * m; i++) parent[i] = i;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (oboard[i][j] != '0') continue;
    if (i > 0 && oboard[i - 1][j] == '0') Union(i * m + j, (i - 1) * m + j);
    if (j > 0 && oboard[i][j - 1] == '0') Union(i * m + j, i * m + j - 1);
  }

  queue<pii> q;
  set<int> groups;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (oboard[i][j] == '0') {
      q.push({i * m + j, 0});
      vis[i * m + j] = true;
      groups.insert(Find(i * m + j));
    }
  }

  map<int, int> t2s;
  int mgs = 1e9;
  bcopy();

  while (!q.empty()) {
    auto [pos, t] = q.front();
    int ci = pos / m, cj = pos % m;
    q.pop();

    board[ci][cj] = '0';
    if (ci > 0) {
      if (board[ci - 1][cj] == '0') {
        int xg = Find(pos), yg = Find((ci - 1) * m + cj);
        if (xg != yg) {
          Union(pos, (ci - 1) * m + cj);
          groups.erase(yg);
        }
      }
      else if (board[ci - 1][cj] == '1' && !vis[(ci - 1) * m + cj]) {
        Union(pos, (ci - 1) * m + cj);
        vis[(ci - 1) * m + cj] = true;
        q.push({(ci - 1) * m + cj, t + 1});
      }
    }
    if (ci < n - 1) {
      if (board[ci + 1][cj] == '0') {
        int xg = Find(pos), yg = Find((ci + 1) * m + cj);
        if (xg != yg) {
          Union(pos, (ci + 1) * m + cj);
          groups.erase(yg);
        }
      }
      else if (board[ci + 1][cj] == '1' && !vis[(ci + 1) * m + cj]) {
        Union(pos, (ci + 1) * m + cj);
        vis[(ci + 1) * m + cj] = true;
        q.push({(ci + 1) * m + cj, t + 1});
      }
    }
    if (cj > 0) {
      if (board[ci][cj - 1] == '0') {
        int xg = Find(pos), yg = Find(ci * m + cj - 1);
        if (xg != yg) {
          Union(pos, ci * m + cj - 1);
          groups.erase(yg);
        }
      }
      else if (board[ci][cj - 1] == '1' && !vis[ci * m + cj - 1]) {
        Union(pos, ci * m + cj - 1);
        vis[ci * m + cj - 1] = true;
        q.push({ci * m + cj - 1, t + 1});
      }
    }
    if (cj < m - 1) {
      if (board[ci][cj + 1] == '0') {
        int xg = Find(pos), yg = Find(ci * m + cj + 1);
        if (xg != yg) {
          Union(pos, ci * m + cj + 1);
          groups.erase(yg);
        }
      }
      else if (board[ci][cj + 1] == '1' && !vis[ci * m + cj + 1]) {
        Union(pos, ci * m + cj + 1);
        vis[ci * m + cj + 1] = true;
        q.push({ci * m + cj + 1, t + 1});
      }
    }

    t2s[t] = groups.size();
    mgs = min(mgs, t2s[t]);
  }

  int ts;
  for (int ti = 0; ti <= MAX * MAX; ti++) {
    if (!t2s.count(ti + 1) || (t2s[ti] == t2s[ti + 1] && t2s[ti] == mgs)) {
      ts = ti;
      break;
    }
  }

  memset(vis, 0, sizeof vis);
  bcopy();
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (oboard[i][j] == '0') {
      q.push({i * m + j, 0});
      vis[i * m + j] = true;
    }
  }

  while (!q.empty()) {
    auto [pos, t] = q.front();
    int ci = pos / m, cj = pos % m;
    q.pop();

    if (t > ts) continue;
    board[ci][cj] = '0';

    if (ci > 0 && board[ci - 1][cj] == '1' && !vis[(ci - 1) * m + cj]) {
      vis[(ci - 1) * m + cj] = true;
      q.push({(ci - 1) * m + cj, t + 1});
    }
    if (ci < n - 1 && board[ci + 1][cj] == '1' && !vis[(ci + 1) * m + cj]) {
      vis[(ci + 1) * m + cj] = true;
      q.push({(ci + 1) * m + cj, t + 1});
    }
    if (cj > 0 && board[ci][cj - 1] == '1' && !vis[ci * m + cj - 1]) {
      vis[ci * m + cj - 1] = true;
      q.push({ci * m + cj - 1, t + 1});
    }
    if (cj < m - 1 && board[ci][cj + 1] == '1' && !vis[ci * m + cj + 1]) {
      vis[ci * m + cj + 1] = true;
      q.push({ci * m + cj + 1, t + 1});
    }
  }

  int fcnt = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    if (board[i][j] == '0') fcnt++;
  }

  cout << ts << ' ' << fcnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
