#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Result {
  ll numbers = 0;
  array<ll, 10> digits{};
};

string limit_value;
Result memo[20][2];
bool seen[20][2];

Result count_odd_pages(int pos, bool tight, bool started) {
  if (pos == (int)limit_value.size()) {
    return {started ? 1 : 0, {}};
  }

  if (!tight && seen[pos][started]) return memo[pos][started];

  Result ret;
  int limit = tight ? limit_value[pos] - '0' : 9;
  for (int digit = 0; digit <= limit; ++digit) {
    bool next_started = started || digit != 0;
    if (pos + 1 == (int)limit_value.size() &&
        (!next_started || digit % 2 == 0)) {
      continue;
    }

    Result child = count_odd_pages(pos + 1, tight && digit == limit, next_started);
    ret.numbers += child.numbers;
    for (int d = 0; d < 10; ++d) ret.digits[d] += child.digits[d];
    if (next_started) ret.digits[digit] += child.numbers;
  }

  if (!tight) {
    seen[pos][started] = true;
    memo[pos][started] = ret;
  }
  return ret;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  ll N;
  cin >> N;
  limit_value = to_string(N);

  Result answer = count_odd_pages(0, true, false);
  for (int i = 0; i < 10; ++i) {
    cout << answer.digits[i] << " \n"[i == 9];
  }
}
