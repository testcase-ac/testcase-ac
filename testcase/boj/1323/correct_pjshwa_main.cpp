#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool vis[100000];
int main(){
  fast_io();

  ll n, k;
  cin >> n >> k;
  ll steps = to_string(n).size(), mod = n % k, iter = 1;

  bool able = true;
  while (mod != 0) {
    if (vis[mod]) {
      able = false;
      break;
    }
    vis[mod] = true;

    for (int i = 0; i < steps; i++) mod *= 10;
    mod = (mod + n) % k;
    iter++;
  }

  if (able) cout << iter;
  else cout << -1;
}
