#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool vis[MAX];
tii ans[MAX + 1];
int a, b;

int tick = 0;
void dfs(int a, int b, int par, int pidx) {
  if (a == 0 && b == 0) return;

  int idx = ++tick;
  if (par != -1) {
    if (pidx == 1) get<1>(ans[par]) = idx;
    else get<2>(ans[par]) = idx;
  }

  if (a == 1 && b == 0) {
    ans[idx] = {1, 0, 0};
    return;
  }
  if (a == 0 && b == 1) {
    ans[idx] = {2, 0, 0};
    return;
  }

  int sum = a + 2 * b;
  if (sum & 1) {
    if (b == 0) {
      get<0>(ans[idx]) = 1;
      a--;
      dfs(a / 2, 0, idx, 1);
      dfs(a / 2, 0, idx, 2);
    }
    else {
      get<0>(ans[idx]) = 2;
      b--;
      int half2 = b / 2, diva = (sum - 2) / 2 - 2 * half2;
      dfs(diva, half2, idx, 1);
      dfs(a - diva, b - half2, idx, 2);
    }
  }
  else {
    if (a == 0 && b % 2 == 0) {
      cout << "-1\n";
      exit(0);
    }
    else if (b) {
      get<0>(ans[idx]) = 2;
      b--;
      int half2 = b / 2, diva = (sum - 2) / 2 - 2 * half2;
      dfs(diva, half2, idx, 1);
      dfs(a - diva, b - half2, idx, 2);
    }
    else {
      get<0>(ans[idx]) = 1;
      a--;
      dfs(a / 2, 0, idx, 1);
      dfs((sum - 1) - a / 2, 0, idx, 2);
    }
  }
}

int main() {
  fast_io();

  cin >> a >> b;
  dfs(a, b, -1, 0);

  for (int i = 1; i <= tick; i++) {
    cout << get<0>(ans[i]) << ' ' << get<1>(ans[i]) << ' ' << get<2>(ans[i]) << '\n';
  }


}
