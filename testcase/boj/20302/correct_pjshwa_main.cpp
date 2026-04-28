#include <iostream>
#include <vector>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e5;
int lp[MAX+1];
int ty[MAX+1];

int main() {
  fast_io();
  
  int t, n, lpc;
  vector<int> pr;

  for (int i = 2; i <= MAX; i++) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++) lp[i * pr[j]] = pr[j];
  }

  cin >> n;
  int num;
  char op;

  for (int i = 0; i < n; i++) {
    if (i == 0) {
      op = '*';
      cin >> num;
    }
    else cin >> op >> num;
    num = abs(num);

    if (num == 0) {
      cout << "mint chocolate\n";
      return 0;
    }

    while (num != 1) {
      lpc = lp[num];
      num /= lpc;
      op == '*' ? ty[lpc]++ : ty[lpc]--;
    }
  }

  bool able = true;
  for (int prime : pr) {
    if (ty[prime] < 0) able = false;
  }
  cout << (able ? "mint chocolate" : "toothpaste") << '\n';
  
}
