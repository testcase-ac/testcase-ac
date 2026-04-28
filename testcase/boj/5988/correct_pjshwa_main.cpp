#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char num[62];
int main() {
  fast_io();

  int n, l;
  cin >> n;
  while (n--) {
    cin >> num;
    cout << (num[strlen(num) - 1] & 1 ? "odd\n" : "even\n");
  }
}
