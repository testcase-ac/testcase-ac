#include <cstdio>
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main() {
	int N, n, k, mx = 0, ans = 0;

	scanf("%d", &N);
	while (N--) {
		scanf("%d", &n);
		for (k = 0; n; n >>= 1) {
			++k;
			if (n & 1) ++ans;
		}
		if (--k > mx) mx = k;
	}
	ans += mx;

	printf("%d\n", ans);

	return 0;
}
