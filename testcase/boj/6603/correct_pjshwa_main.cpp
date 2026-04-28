#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n; 
  ll m, nums[13], stack[13];

  while (1) {
    cin >> n;
    if (n == 0) break;

    for (int i = 0; i < n; i++) cin >> nums[i];

    int stack_pointer;
    bool finished;

    // combinations
    for (int i = 6; i <= 6; i++) {
      stack_pointer = -1;
      stack[0] = 0;

      finished = false;
      while (!finished) {

        for (stack_pointer++; stack_pointer < i - 1; stack_pointer++) {
          stack[stack_pointer + 1] = stack[stack_pointer] + 1;
        }

        // stack[0]..stack[i - 1] contains the indexes
        // do work here
        for(int j = 0; j < 6; j++) {
          cout << nums[stack[j]] << ' ';
        }
        cout << '\n';
        // do work here

        do {
          if (stack_pointer == -1) {
            finished = true;
            break;
          }
          stack[stack_pointer--]++;
        } while (stack[stack_pointer + 1] + i == n + stack_pointer + 2);
      }
    }

    cout << '\n';
  }
}
