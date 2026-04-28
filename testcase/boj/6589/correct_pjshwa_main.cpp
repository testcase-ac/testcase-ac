#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

const int MAXN = 200;
int parent[MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

int N, R, tc;

void init() {
  fi.clear();
  fcount = 0;
  iota(parent, parent + N, 0);
}

void solve() {
  cout << "Scenario #" << ++tc << '\n';
  init();

  vector<tuple<int, int, int>> E;
  for (int i = 0; i < R; ++i) {
    string c1, c2; int w; cin >> c1 >> c2 >> w;
    E.emplace_back(w, fidx(c1), fidx(c2));
  }
  sort(E.begin(), E.end(), greater<>());

  string Ss, Ds; cin >> Ss >> Ds;
  int S = fidx(Ss), D = fidx(Ds);
  for (auto& [w, u, v] : E) {
    Union(u, v);
    if (Find(S) == Find(D)) {
      cout << w << " tons\n";
      break;
    }
  }
}

int main() {
  fast_io();

  int f = 1;
  while (cin >> N >> R) {
    if (N == 0 && R == 0) break;
    if (f) f = 0;
    else cout << '\n';
    solve();
  }
}
