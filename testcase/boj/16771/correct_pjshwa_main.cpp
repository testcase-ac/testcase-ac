#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int> &v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

const int MAX = 10;
int A[MAX], B[MAX];
vector<int> ans;

void dfs(int t, int acc) {
  if (t == 2) {
    ans.push_back(acc);
    return;
  }

  dfs(t + 1, acc);
  for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) {
    int dif = B[j] - A[i];
    swap(A[i], B[j]);
    dfs(t + 1, acc + dif);
    swap(A[i], B[j]);
  }

}

void solve() {
  for (int i = 0; i < 10; i++) cin >> A[i];
  for (int i = 0; i < 10; i++) cin >> B[i];

  dfs(0, 1000);

  compress(ans);
  cout << ans.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
