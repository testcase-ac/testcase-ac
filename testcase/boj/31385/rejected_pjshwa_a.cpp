#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 300;
vector<int> V;

int sigma(int n) {
  int ret = 0;
  for (int f = 1; f * f <= n; ++f) {
    if (n % f) continue;
    ++ret;
    if (f * f < n) ++ret;
  }
  return ret;
}

int N;
vector<int> cur;

void dfs(int i, int pre) {
  if (i == N) {
    for (int v : cur) cout << v << ' '; cout << '\n';

    int sum = 0;
    for (int v : cur) {
      sum += v;
      // cout << sum << ' ';
    }
    // cout << endl;
    exit(0);
  }

  for (int v : V) {
    int nxt = pre + v;
    if (sigma(nxt) == v) {
      cur.push_back(v);
      dfs(i + 1, nxt);
      cur.pop_back();
    }
  }
}

void solve() {
  cin >> N;
  for (int v : V) {
    cur.push_back(v);
    dfs(1, v);
    cur.pop_back();
  }
  cout << "Impossible\n";
}

#include <sys/resource.h>

void enlarge_stack() {
  struct rlimit lim;
  getrlimit(RLIMIT_STACK, &lim);
  lim.rlim_cur = lim.rlim_max;
  setrlimit(RLIMIT_STACK, &lim);
}

int main() {
  fast_io();
  enlarge_stack();

  V = {2, 3, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 24, 28, 30, 32, 33, 34, 36, 40, 42, 44, 48, 50, 54, 56, 60, 64, 72, 80, 84, 90, 96, 100, 108, 112, 120, 128, 144, 150, 160, 168, 180, 192, 200};

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
