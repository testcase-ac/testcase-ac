#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;

int main(){
  ull n;
  cin >> n;

  int cnt = 64;
  while ((n & 1) == 0) {
    n >>= 1;
    cnt--;
  }
  cout << cnt << '\n';
}
