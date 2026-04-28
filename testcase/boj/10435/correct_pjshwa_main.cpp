#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<int> Q[6000];
vector<int> cur;
void dfs(int i, int p, int s) {
  if (i == 0) {
    Q[s] = cur;
    return;
  }

  if (p % i) {
    int val = i - p % i;
    cur.push_back(val);
    dfs(i - 1, p + (p + val) / i, s + val);
    cur.pop_back();
  }
  else {
    for (int val : {0, i}) {
      cur.push_back(val);
      dfs(i - 1, p + (p + val) / i, s + val);
      cur.pop_back();
    }
  }
}

void solve() {
  int tc, N;
  cin >> tc >> N;

  int z = Q[N].size(), it = 0;
  cout << tc << ' ' << z << '\n';

  for (int i = z - 1; i >= 0; --i) {
    cout << Q[N][i] << ' ';

    it++;
    if (i > 0 && it % 10 == 0) cout << '\n';
  }
  cout << '\n';
}

int main() {
  fast_io();

  for (int B = 80; B >= 1; B--) {
    cur.push_back(B);
    dfs(B - 1, 1, B);
    cur.pop_back();
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
