#include <algorithm>
#include <assert.h>
#include <bitset>
#include <complex>
#include <ctype.h>
#include <functional>
#include <iostream>
#include <limits.h>
#include <locale.h>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <cmath>
#include <vector>
#include <deque>
//#include <unordered_set>
#include <unordered_map>

#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;

#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef pair <ll, int> pli;
typedef pair <ldb, ldb> pdd;

int IT_MAX = 1 << 20;
const ll MOD = 98765431;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 1234567890123456789ll;
const db PI = 3.141592653589793238;
const db ERR = 1E-6;

ll in[3050];
ll sum[3050];

set <ll> Sx;
int main() {
	int N, i, j, k;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		scanf("%lld", &in[i]);
		sum[i] = sum[i - 1] + in[i];
	}

	ll a1 = LL_INF, a2 = -1;
	for (i = N / 2; i >= 1; i--) {
		for (j = i + 1; j + i - 1 <= N; j++) {
			Sx.insert(sum[j - 1] - sum[j - i - 1]);
			
			ll v = sum[j + i - 1] - sum[j - 1];
			auto it = Sx.lower_bound(v);
			if (it != Sx.end()) {
				if (a1 > abs(*it - v)) {
					a1 = abs(*it - v);
					a2 = i;
				}
			}
			if (it != Sx.begin()) {
				it--;
				if (a1 > abs(*it - v)) {
					a1 = abs(*it - v);
					a2 = i;
				}
			}
		}
		Sx.clear();
	}
	return !printf("%lld\n%lld\n", a2, a1);
}

// https://www.acmicpc.net/source/5287045
