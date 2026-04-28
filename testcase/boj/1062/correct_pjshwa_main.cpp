#include <bits/stdc++.h>
using namespace std;

bool vis[26];
char str[17];
string candidates = "bdefghjklmopqrsuvwxyz";
string words[50];

int trav(int r, int k, int n) {
  int ans = 0, t_ans;
  int stack[21];
  int stack_pointer = -1;
  bool finished = false;

  int sz;
  bool know;

  stack[0] = 0;
  while (!finished) {
    for (stack_pointer++; stack_pointer < k - 1; stack_pointer++) {
      stack[stack_pointer + 1] = stack[stack_pointer] + 1;
    }

    // do work here
    for (int i = 0; i < k; i++) {
      char cand = candidates[stack[i]];
      vis[cand - 'a'] = true;
    }

    t_ans = 0;
    for (int s = 0; s < n; s++) {
      string word = words[s];
      sz = word.size();
      know = true;
      for (int i = 4; i < sz - 4; i++) {
        if (!vis[word[i] - 'a']) {
          know = false;
          break;
        }
      }
      if (know) t_ans++;
    }

    ans = max(t_ans, ans);

    for (int i = 0; i < k; i++) {
      char cand = candidates[stack[i]];
      vis[cand - 'a'] = false;
    }
    // do work here

    do {
      if (stack_pointer == -1) {
        finished = true;
        break;
      }
      stack[stack_pointer--]++;
    } while (stack[stack_pointer + 1] + k == stack_pointer + (26 - 5) + 2);
  }

  return ans;
}

int main() {
  int n, k;
  cin >> n >> k;
  if (k <= 4) {
    cout << "0\n";
    return 0;
  }
  if (k == 26) {
    cout << n << '\n';
    return 0;
  }

  k -= 5;
  vis['a' - 'a'] = true;
  vis['c' - 'a'] = true;
  vis['i' - 'a'] = true;
  vis['n' - 'a'] = true;
  vis['t' - 'a'] = true;

  for (int i = 0; i < n; i++) cin >> words[i];
  cout << trav(0, k, n) << '\n';
}
