#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int grass[MAX + 1];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    int g, x;
    cin >> g >> x;
    grass[x] = g;
  }

  int cgrass = 0;
  for (int i = 0; i <= min(MAX, 2 * k); i++) cgrass += grass[i];

  int mgrass = cgrass;
  for (int pos = k + 1; pos <= MAX - k; pos++) {
    cgrass -= grass[pos - k - 1];
    cgrass += grass[pos + k];
    mgrass = max(mgrass, cgrass);
  }

  cout << mgrass << '\n';
}
