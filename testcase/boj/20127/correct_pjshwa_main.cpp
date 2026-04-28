#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[100000];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int invs = 0, invidx;
  for (int i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1]) {
      invidx = i;
      invs++;
    }
  }

  int k = 2e5;

  // Already IS
  if (invs == 0) k = 0;

  // Can be IS
  else if (invs == 1 && a[0] >= a[n - 1]) k = invidx + 1;
    
  invs = 0;
  for (int i = 0; i < n - 1; i++) {
    if (a[i] < a[i + 1]) {
      invidx = i;
      invs++;
    }
  }

  // Already DS
  if (invs == 0) k = 0;

  // Can be DS
  else if (invs == 1 && a[0] <= a[n - 1]) k = min(k, invidx + 1);
  
  cout << (k == 2e5 ? -1 : k) << '\n';
}
