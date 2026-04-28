#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  string ans = "";

  // 1. 출전자의 영어 이름에서 알파벳이 중복되지 않도록 추출한다. 특정 알파벳이 여러 번 등장한다면 처음 등장한 경우를 제외하고 해당 알파벳을 버린다.
  set<char> U; int thr = 0;
  for (char c : S) {
    if (!U.count(c)) U.insert(c), ans += c;
    else ++thr;
  }

  // 2. 1번을 통해 만들어진 문자열 맨 뒤에 1번 과정에서 버려진 문자의 개수에 4를 더한 값을 붙인다.
  ans += to_string(thr + 4);

  // 3. 2번을 통해 만들어진 문자열 맨 앞에 출전 등록 번호에 1906을 더한 값을 붙인다.
  ans = to_string(N + 1906) + ans;

  // 4. 3번을 통해 만들어진 문자열을 뒤집는다.
  reverse(ans.begin(), ans.end());

  // 5. 4번을 통해 만들어진 문자열 맨 앞에 "smupc_"를 붙인다.
  ans = "smupc_" + ans;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
