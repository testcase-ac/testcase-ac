#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, a[20];
vector<int> current, vs;

void dfs(int i) {
  if (i == n) {
    vs.push_back(accumulate(current.begin(), current.end(), 0));
    return;
  }

  dfs(i + 1);
  current.push_back(a[i]);
  dfs(i + 1);
  current.pop_back();
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  dfs(0);

  compress(vs);
  cout << vs[vs.size() - 1] - (vs.size() - 1) << '\n';
}
