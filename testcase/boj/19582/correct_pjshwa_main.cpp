#include <iostream>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int n; cin >> n;
  int xi[n], pi[n];

  for (int i = 0; i < n; i++) {
    cin >> xi[i] >> pi[i];
  }

  bool possible = true;
  int fail_idx = -1;
  int s = 0;
  for (int i = 0; i < n; i++) {
    if (s <= xi[i]) s += pi[i];
    else {
      possible = false;
      fail_idx = i;
      break;
    }
  }

  if (!possible) {
    possible = true;
    s = 0;

    for (int i = 0; i < n; i++) {
      if (i == fail_idx) continue;

      if (s <= xi[i]) s += pi[i];
      else {
        possible = false;
        break;
      }
    }
  }

  if (!possible) {
    int max_idx = -1;
    int max_val = -1;
    possible = true;
    s = 0;

    for (int i = 0; i < fail_idx; i++) {
      if (pi[i] > max_val) {
        max_idx = i;
        max_val = pi[i];
      }
    }

    for (int i = 0; i < n; i++) {
      if (i == max_idx) continue;

      if (s <= xi[i]) s += pi[i];
      else {
        possible = false;
        break;
      }
    }
  }

  cout << (possible ? "Kkeo-eok" : "Zzz") << '\n';
}
