#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll gcd(ll x, ll y){ return y ? gcd(y, x%y) : x; }
ll pow(ll a, ll b) {
  ll ret = 1;
  for (; b; b >>= 1, a = (a * a))
    if (b & 1) ret = (ret * a);
  return ret;
}


int main(void) {
  ll res[24];
  res[0] = 1;

  ll c = 3;
  for (int s = 1; s < 24; s++) {
    ll tot = 0;

    for(int i = 1; i <= s; i++){
      tot += pow(c, gcd(i, s));
    }
    if(s % 2 == 0){
      tot += s*(pow(c,s/2)+pow(c,s/2+1))/2;
    }
    else{
      tot += s*(pow(c,s/2+1));
    }
    res[s] = tot / (2*s);
  }

  int n;
  while (true) {
    cin >> n;
    if (n == -1) break;

    cout << res[n] << '\n';
  }
}
