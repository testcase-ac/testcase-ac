#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  unordered_map<int, int> t;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (t[x]) ans++, t[x]--;
  }

  cout << n - ans << '\n';
}
