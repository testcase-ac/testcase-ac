#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[1000];
bool cnts[1 << 17];
int main() {
  fast_io();

  int n;
  cin >> n;
  if (n > 1000) return cout << "Yes", 0;

  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) if (cnts[a[i] ^ a[j]]) return cout << "Yes", 0;
    for (int j = 0; j < i; j++) cnts[a[i] ^ a[j]] = true;
  }

  cout << "No";
}
