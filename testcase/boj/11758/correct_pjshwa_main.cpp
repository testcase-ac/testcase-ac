#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
using namespace std;

ll ccw(pll a, pll b, pll c){
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

int main(){
  int x1, y1, x2, y2, x3, y3;
  cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

  ll res = ccw({ x1, y1 }, { x2, y2 }, { x3, y3 });
  cout << (res > 0 ? 1 : res < 0 ? -1 : 0) << '\n';
}
