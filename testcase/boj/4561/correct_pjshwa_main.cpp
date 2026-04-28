#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

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

void reset() {
  fi.clear();
  fcount = 0;
}

const int MAX = 100, INF = 0x3f3f3f3f;
int cost[MAX][MAX];
string inv[MAX];

void solve() {
  reset();

  int x, y;
  cin >> x >> y;
  for (int i = 0; i < x; i++) {
    string C, NS, EW;
    int LA, LO;
    cin >> C >> LA >> NS >> LO >> EW;
  
    inv[fidx(C)] = C;

  }

  for (int i = 0; i < x; i++) for (int j = 0; j < x; j++) {
    if (i == j) cost[i][j] = 0;
    else cost[i][j] = INF;
  }
  while (y--) {
    string S, T;
    cin >> S >> T;

    int c;


    cost[fidx(S)][fidx(T)] = cost[fidx(T)][fidx(S)] = c;
  }

  // Floyd-warshall
  for (int k = 0; k < x; k++) {
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < x; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int mdist = 0;
  for (int i = 0; i < x; i++) for (int j = 0; j < x; j++) {
    if (cost[i][j] != INF) mdist = max(mdist, cost[i][j]);
  }

  for (int i = 0; i < x; i++) for (int j = 0; j < x; j++) {
    if (cost[i][j] == mdist) {
      vector<string> ans = {inv[i], inv[j]};
      sort(ans.begin(), ans.end());
      cout << ans[0] << ' ' << ans[1] << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
