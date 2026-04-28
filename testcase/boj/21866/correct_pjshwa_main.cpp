#include <bits/stdc++.h>
using namespace std;

bool hacker = false;
int main() {
  cin.tie(NULL); cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  int s = 0, si;
  for (int i = 0; i < 9; i++) {
    cin >> si;
    if (i <= 1 && si > 100) hacker = true;
    if (i <= 3 && si > 200) hacker = true;
    if (i <= 5 && si > 300) hacker = true;
    if (i <= 7 && si > 400) hacker = true;
    if (i == 8 && si > 500) hacker = true;
    s += si;
  }

  if (hacker) {
    cout << "hacker";
    return 0;
  }
  cout << (s >= 100 ? "draw" : "none");
}
