#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 26 * 26, MAXN = MAXL * 2;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], K;
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

int E(char a, char b) {
  if (isupper(b)) return (a - 'a') * 26 + (b - 'A') + 26 * 26;
  else return (a - 'A') * 26 + (b - 'a');
}

void solve() {
  string S; cin >> S;
  int N = S.size();
  
  int Ps = E(S[0], S[1]), Pe = E(S[N - 2], S[N - 1]);
  for (int i = 1; i < N - 1; ++i) {
    int P0 = E(S[i - 1], S[i]), P1 = E(S[i], S[i + 1]);
    if (P0 == Ps || P1 == Ps || P0 == Pe || P1 == Pe) continue;
    adj[P0].push_back(P1);
    adj[P1].push_back(P0);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < MAXL; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + MAXL, false);
    if (dfs(i)) ++match;
  }

  if (Ps == Pe) ++match;
  else match += 2;

  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
