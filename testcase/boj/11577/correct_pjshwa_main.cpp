#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k, s, tcnt = 0;
  cin >> n >> k;

  queue<int> lchg;
  for (int i = 0; i < n; i++) {
    cin >> s;

    // If s + lchg.size() mod 2 == 0, no inversion required
    // Else inversion is required
    // If we should invert the bulbs at point i
    if ((s + lchg.size()) & 1) {
      // Mark the end point of this inversion
      lchg.push(i + k - 1);
      tcnt++;
    }

    // The "effect" of inversion ends
    if (!lchg.empty() && lchg.front() == i) lchg.pop();
  }

  // Inversion succeeds
  if (lchg.empty()) cout << tcnt << '\n';

  // There are always some remaining bulbs
  else cout << "Insomnia\n";
}
