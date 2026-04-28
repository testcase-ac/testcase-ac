#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll, ll>
using namespace std;

// https://wogud6792.tistory.com/12
ll ccw(pll a, pll b, pll c){
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

pll points[10000];
int main(){
  int n, x, y;
  ll result = 0;
  cin >> n;
    
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    points[i] = make_pair(x, y);
  }

  for (int i = 1; i < n - 1; i++){
    result += ccw(points[0], points[i], points[i + 1]);
  }

  if (result < 0) result = -result;
  cout << fixed << setprecision(1) << (double)result / 2 << '\n';
}
