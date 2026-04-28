#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e5;
long long r[MAX], w[MAX];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 1; i < n; i++) cin >> r[i];
  for (int i = 0; i < n; i++) cin >> w[i];

  long long s = 0;
  long long cl = w[0];
  for (int i = 1; i < n; i++) {
    s += cl * r[i];
    cl = min(cl, w[i]);
  }

  cout << s << '\n';
}
