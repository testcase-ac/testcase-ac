#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[5000];
bool weights[800001];
int main() {
  fast_io();

  int w, n;
  cin >> w >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] + a[j] > w) continue;
      if (weights[w - a[i] - a[j]]) {
        cout << "YES\n";
        return 0;
      }
    }
    for (int j = 0; j < i; j++) {
      if (a[i] + a[j] < w) weights[a[i] + a[j]] = true;
    }
  }

  cout << "NO\n";
}
