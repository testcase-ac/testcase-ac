#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

int N;
void solve() {
  for (int i = 0; i < N; ++i) adj[i].clear();
  for (int i = 0; i < N; ++i) {
    string Js, Ks; cin >> Js >> Ks;
    int J = stoi(Js.substr(0, Js.size() - 1));
    int K = stoi(Ks.substr(1, Ks.size() - 2));
    while (K--) {
      int x; cin >> x;
      adj[J].push_back(x - N);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  while (cin >> N) solve();
}
