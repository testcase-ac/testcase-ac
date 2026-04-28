#include <bits/stdc++.h>
#define ll long long
#define MOD int(1e9 + 7)
using namespace std;

int POW(int a, int b) {
  int ret = 1;
  for (; b; b >>= 1, a = (a * a))
    if (b & 1) ret = (ret * a);
  return ret;
}

int main(void) {
  while(true){
    int c,s;
    cin >> c >> s;
    if(c==0) break;
    int tot = 0;
    // 1. 뒤집지 않고 회전만 하는 경우
    for(int i = 1; i <= s; i++){
      tot += POW(c,__gcd(i,s));
    }
    // 2. 뒤집은 후 회전하는 경우
    if(s % 2 == 0){
      tot += s*(POW(c,s/2)+POW(c,s/2+1))/2;
    }
    else{
      tot += s*(POW(c,s/2+1));
    }
    cout << tot / (2*s) << '\n';
  }
}
