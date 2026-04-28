#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll a[21];
int main() {
  fast_io();

  a[0] = 1;
  for (int i = 1; i <= 20; i++) a[i] = (i * a[i - 1] + ((i & 1) ? -1 : 1));

  int t, n;
  cin >> t;
  
  while (t--) {
    cin >> n;
    cout << a[n] << '\n';
  }
}
