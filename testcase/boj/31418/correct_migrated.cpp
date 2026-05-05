#include <iostream>
#include <algorithm>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
#define P 998244353
#define N 1000000
typedef long long int ll;
char r[N];
int p;
inline int f() {
	int answer = 0, x;
	while (1) {
		if (p == N) fread(r, 1, N, stdin), p = 0;
		x = r[p++];
		if (x == ' ' || x == '\n') break;
		answer = answer * 10 + (x & 0x0F);
	}
	return answer;
}
int main(void) {
	ll m, n, num, t, answer = 1;
	int x, y;
	m = f();
	n = f();
	num = f();
	t = f();

	while (num--) {
		x = f();
		y = f();

		ll minX = max(1LL, x - t);
		ll maxX = min(m, x + t);
		ll minY = max(1LL, y - t);
		ll maxY = min(n, y + t);
		ll s = (maxX - minX + 1) * (maxY - minY + 1);
		s %= P;
		answer = (answer * s) % P;
	}
	cout << answer;
	return 0;
}
