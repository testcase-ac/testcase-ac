#include <bits/stdc++.h>
using namespace std;

int a[300000];
vector<int> vi[10001];
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, C, M, A, B;
  cin >> N >> C;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    vi[a[i]].push_back(i);
  }

  cin >> M;
  while (M--) {
    cin >> A >> B;

    int found = -1;
    for (int i = 1; i <= 20; i++) {
      int ridx = rand() % (B - A + 1) + A - 1;
      auto& tv = vi[a[ridx]];
      int tally = upper_bound(tv.begin(), tv.end(), B - 1) - lower_bound(tv.begin(), tv.end(), A - 1);
      if (2 * tally > B - A + 1) {
        found = a[ridx];
        break;
      }
    }

    if (found == -1) cout << "no\n";
    else cout << "yes " << found << '\n';
  }
}
