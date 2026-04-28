#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<int> graph[(int)3e5];
int degree[(int)3e5];

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, u, v;
  ll d = 0, g = 0;
  cin >> n;

  memset(degree, 0, sizeof(degree));
  for (int i = 0; i < n - 1; i++) {
    cin >> u >> v;
    degree[u - 1]++;
    degree[v - 1]++;
    graph[u - 1].push_back(v - 1);
  }

  for (int i = 0; i < n; i++) {
    for (auto &v : graph[i]) d += (degree[i] - 1) * (degree[v] - 1);
    if (degree[i] >= 3) g += degree[i] * (degree[i] - 1) * (degree[i] - 2) / 6;
  }

  if (d > 3 * g) cout << "D\n";
  else if (d < 3 * g) cout << "G\n";
  else cout << "DUDUDUNGA\n";
}
