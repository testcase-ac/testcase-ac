#include <bits/stdc++.h>
using namespace std;

int listen() {
  int ret;
  cin >> ret;
  return ret;
}

void respond(char o) {
  cout << o << endl;
}

int main() {
  int it = 100;

  int lb = 1, ub = 1e9;
  while (it--) {
    int q = listen();
    if (lb == ub && lb == q) {
      respond('=');
      break;
    }
    if (lb <= q) {
      if (q <= ub) {
        if (ub - q > q - lb) {
          lb = q + 1;
          respond('>');
        }
        else {
          ub = q - 1;
          respond('<');
        }
      }
      else respond('<');
    }
    else respond('>');
  }
}
