#include <bits/stdc++.h>
using namespace std;

int a[1000000], dl[1000000], dr[1000000];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int cmin, md;
  cmin = 1e9;
  md = -1e9;
  for (int i = 1; i < n; i++) {
    cmin = min(cmin, a[i - 1]);
    md = max(md, a[i] - cmin);
    dl[i] = md;
  }

  cmin = 1e9;
  md = -1e9;
  for (int i = n - 2; i >= 0; i--) {
    cmin = min(cmin, -a[i + 1]);
    md = max(md, -a[i] - cmin);
    dr[i] = md;
  }

  md = -1e9;
  for (int i = 1; i < n - 2; i++) md = max(md, dl[i] + dr[i + 1]);
  cout << md << '\n';
}
