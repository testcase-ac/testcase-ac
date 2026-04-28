#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(void) {
  int stack[50], multiplier[50];

  string txt;
  cin >> txt;

  int sz = txt.size();
  int lev = 0;

  stack[0] = 0;

  for (int i = 0; i < sz; i++) {
    if (i < sz - 1 && txt[i + 1] == '(') {
      lev++;
      multiplier[lev] = txt[i] - 48;
      stack[lev] = 0;
      i++;
    }
    else if (txt[i] == ')') {
      stack[lev - 1] += (multiplier[lev] * stack[lev]);
      lev--;
    }
    else stack[lev]++;
  }

  cout << stack[0] << '\n';
}
