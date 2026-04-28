#include <bits/stdc++.h>
#define ll long long
#define pdi pair<double, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  priority_queue<pdi, vector<pdi>, greater<pdi> > pq;
  int n;
  ll x, y, v;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y >> v;
    double xy = x * x + y * y;
    xy /= (v * v);
    pq.push({xy, i});
  }

  while (n--) {
    cout << pq.top().second << '\n';
    pq.pop();
  }
}
