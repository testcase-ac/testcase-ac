#include <stdio.h>  
#include <algorithm>  
#include <assert.h>
#include <bitset>
#include <cmath>  
#include <complex>  
#include <deque>  
#include <functional>  
#include <iostream>  
#include <limits.h>  
#include <map>  
#include <math.h>  
#include <queue>  
#include <set>  
#include <stdlib.h>  
#include <string.h>  
#include <string>  
#include <time.h>  
//#include <unordered_map>  
//#include <unordered_set>  
#include <vector>
#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
#define mp make_pair
#define Fi first
#define Se second
#define pb(x) push_back(x)
#define szz(x) ((int)(x).size())
#define rep(i, n) for(int i=0;i<n;i++)
#define all(x) (x).begin(), (x).end()
#define ldb ldouble  
typedef tuple<int, int, int> t3;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef pair <ll, int> pli;
typedef pair <db, db> pdd;
int IT_MAX = 1 << 20;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1);
const db ERR = 1e-10;

pii in[3];
pii u[3];
int main() {
	for (int i = 0; i < 3; i++) scanf("%d %d", &in[i].first, &in[i].second);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			u[j] = in[j];
			if (i & (1 << j)) swap(u[j].first, u[j].second);
		}
		sort(u, u + 3);

		do {
			if (u[0].first != u[1].first) continue;

			pii u1 = pii(u[0].first, u[0].second + u[1].second), u2 = u[2];
			if (u1.first == u2.first && u1.first == u1.second + u2.second) return !printf("1\n");
			if (u1.first == u2.second && u1.first == u1.second + u2.first) return !printf("1\n");
			if (u1.second == u2.first && u1.second == u1.first + u2.second) return !printf("1\n");
			if (u1.second == u2.second && u1.second == u1.first + u2.first) return !printf("1\n");
		} while (next_permutation(u, u + 3));
	}
	return !printf("0\n");
}
