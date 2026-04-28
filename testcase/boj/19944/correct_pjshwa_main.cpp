#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main(){
  ll n, m;
  cin >> n >> m;

  if (m <= 2) cout << "NEWBIE!";
  else if (m <= n) cout << "OLDBIE!";
  else cout << "TLE!";
  cout << '\n';
}
