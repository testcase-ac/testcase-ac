#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

priority_queue<int> icc[100000];
unordered_map<string, int> friend_to_index;
int friends_count;

int f_index(string f) {
  auto found = friend_to_index.find(f);
  if (friend_to_index.end() == found) {
    friend_to_index.insert({f, friends_count});
    return friends_count++;
  }
  else return found->second;
}

int main() {
  fast_io();

  int q, qi, k, ki;
  string s;
  cin >> q;

  long long isum = 0;

  while (q--) {
    cin >> qi >> s >> k;
    int si = f_index(s);

    if (qi == 1) {
      while (k--) {
        cin >> ki;
        icc[si].push(ki);
      }

    }
    else {
      while (!icc[si].empty() && k--) {
        isum += icc[si].top();
        icc[si].pop();
      }
    }
  }

  cout << isum;
}
