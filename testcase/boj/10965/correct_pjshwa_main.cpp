#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cout << "3\n";
  for (int i = 1; i <= 99'999; i += 3) cout << i << ' ';
  cout << '\n';

  for (int i = 2; i <= 99'999; i += 3) cout << i << ' ';
  cout << '\n';

  for (int i = 3; i <= 99'999; i += 3) cout << i << ' ';
  cout << '\n';

}
