#include <bits/stdc++.h>
using namespace std;

int heights[100001];
int main() {
  int n, m, a, b, k;
  cin >> n >> m;
  map<int, int> dts;
  for (int i = 0; i < n; i++) cin >> heights[i];
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> k;
    auto af = dts.find(a - 1);
    auto bf = dts.find(b);
    if (af != dts.end()) af->second += k;
    else dts.insert({a - 1, k});
    if (bf != dts.end()) bf->second -= k;
    else dts.insert({b, -k});
  }
    
  int dt = 0;
  for (int i = 0; i < n; i++) {
    auto df = dts.find(i);
    if (df != dts.end()) dt += df->second;
    cout << heights[i] + dt << ' ';
  }
}
