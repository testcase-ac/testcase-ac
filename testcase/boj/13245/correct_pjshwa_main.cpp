#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll pow(ll a, ll b) {
  ll ret = 1;
  for (; b; b >>= 1, a = (a * a))
    if (b & 1) ret = (ret * a);
  return ret;
}

ll digits_sum(string num_str) {
  int sz = num_str.size();
  if (sz == 0) return 0;

  int f = num_str[0] - 48;
  if (sz == 1) return f * (f + 1) / 2;

  string new_num_str = num_str.substr(1);

  ll ans = (45 * (sz - 1)) * pow(10, sz - 2) * f;
  ans += (pow(10, sz - 1) * f * (f - 1) / 2);
  ans += (stoll(new_num_str) + 1) * f;

  return ans + digits_sum(new_num_str);
}

int main(void) {
  string num_str;
  cin >> num_str;
  cout << digits_sum(num_str) << '\n';
}
