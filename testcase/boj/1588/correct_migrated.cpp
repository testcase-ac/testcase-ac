#include<cstdio>
typedef long long ll;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
ll t[4][4] = {{},
	{1,3,2},
	{2,1,1},
	{2,3,2}},
	A, Lv, Le, Ri,
	ans[4], d[4][21][4];

ll GetNumber(ll lv, ll pos) {
	return lv ? t[GetNumber(lv-1, pos/3)][pos%3] : A;
}

inline void Add(ll* a, ll* b) {
	for (ll i = 1; i <= 3; i++) a[i] += b[i];
}

void GetRange(ll lv, ll le, ll ri)
{
	if (ri < le) return;
	if (ri - le <= 2) {
		for (ll i = le; i <= ri; i++)
			Add(ans, d[GetNumber(lv, i)][Lv-lv]);
	}
	else {
		ll Lt = le, Rt = ri;
		while (Lt % 3) ++Lt;
		if (le < Lt) GetRange(lv, le, Lt-1);
		while (Rt % 3 != 2) --Rt;
		if (ri > Rt) GetRange(lv, Rt+1, ri);
		GetRange(lv-1, Lt/3, Rt/3);
	}
}

int main()
{
	scanf("%lld%lld%lld%lld", &A, &Le, &Ri, &Lv);

	d[1][0][1] = 1;
	d[2][0][2] = 1;
	d[3][0][3] = 1;
	for (ll i = 1; i <= 20; i++) {
		for (ll j = 1; j <= 3; j++) {
			d[j][i][1] = d[j][i-1][1] + 2 * d[j][i-1][2];
			d[j][i][2] = d[j][i-1][1] + d[j][i-1][2] + 2 * d[j][i-1][3];
			d[j][i][3] = d[j][i-1][1] + d[j][i-1][3];
		}
	}

	GetRange(Lv, Le, Ri);

	for (ll i = 1; i <= 3; i++) {
		printf("%lld ", ans[i]);
	}

	return 0;
}
