#include <smmintrin.h>
#include <immintrin.h>
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")

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
#include <unordered_map>  
#include <unordered_set>  
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

typedef unsigned int uint;
typedef tuple<int, int, int> t3;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef pair <ll, int> pli;
typedef pair <db, db> pdd;

int IT_MAX = 1 << 19;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1);
const db ERR = 1e-10;

//template <int32_t P_, int32_t R_>
namespace FFT2{
	const int P = 998244353, R = 3;
	const int SZ = 17, N = 1 << SZ;

	uint Pow(int x, int y) {
		int r = 1;
		while (y) {
			if (y & 1) r = (ll) r * x % P;
			x = (ll) x * x % P;
			y >>= 1;
		}
		return r;
	}

	const uint RP = Pow((1ll<<32)%P, P-2), MP = P-2; // MP = P^-1 mod 2^32
	uint A[N] __attribute__ ((aligned (0x100)));
	uint B[N] __attribute__ ((aligned (0x100)));
	__m256i Pa;

	void init(){ Pa = _mm256_set1_epi32(P); }

	inline uint fit(uint a){ return a >= P? a-P : a; }

	__m256i avx_add(__m256i a, __m256i b){
		__m256i c = _mm256_add_epi32(a, b);
		__m256i d = _mm256_sub_epi32(c, Pa);
		return _mm256_min_epu32(c, d);
	}

	__m256i avx_sub(__m256i a, __m256i b){
		__m256i c = _mm256_sub_epi32(a, b);
		__m256i d = _mm256_add_epi32(c, Pa);
		return _mm256_min_epu32(c, d);
	}

	__m256i avx_fit(__m256i a){
		__m256i b = _mm256_sub_epi32(a, Pa);
		return _mm256_min_epu32(a, b);
	}

	uint my_mul(uint a, uint b){
		return fit(((ull)a*b + (ull)P*(a*b*MP)) >> 32);
	}

	__m256i avx_mul(__m256i a, __m256i b){
		__m256i res[2];
		__m256i p = _mm256_mullo_epi32(_mm256_mullo_epi32(a, b), _mm256_set1_epi32(MP));

		__m256i ax = _mm256_shuffle_epi32(a, 0x50);
		__m256i bx = _mm256_shuffle_epi32(b, 0x50);
		__m256i px = _mm256_shuffle_epi32(p, 0x50);
		__m256i c = _mm256_mul_epu32(ax, bx);
		__m256i f = _mm256_mul_epu32(px, Pa);

		res[0] = _mm256_add_epi64(c, f);

		ax = _mm256_shuffle_epi32(a, 0xfa);
		bx = _mm256_shuffle_epi32(b, 0xfa);
		px = _mm256_shuffle_epi32(p, 0xfa);
		c = _mm256_mul_epu32(ax, bx);
		f = _mm256_mul_epu32(px, Pa);

		res[1] = _mm256_add_epi64(c, f);

		return avx_fit(_mm256_hadd_epi32(res[0], res[1]));
	}

	inline void run(uint* A, bool rv) {
		int j = 0, k = 0;
		for (int i = 1; i < N; i++) {
			for (k = N >> 1; j >= k; k >>= 1) j -= k;
			j += k;
			if (i < j) swap(A[i], A[j]);
		}
		for (int i = 1; i < 8; i <<= 1) {
			uint x = ((ull)Pow(rv ? Pow(R, P - 2) : R, P / i >> 1) << 32) % P;
			for (int j = 0; j < N; j += i << 1) {
				uint y = (1ll<<32) % P;
				for (int k = 0; k < i; k++) {
					uint z = my_mul(A[i+j+k], y);
					A[i+j+k] = fit(A[j+k] - z + P);
					A[j+k] = fit(A[j+k] + z);
					y = my_mul(y, x);
				}
			}
		}
		for (int i = 8; i < N; i <<= 1) {
			uint t = ((ull)Pow(rv ? Pow(R, P - 2) : R, P / i >> 1) << 32) % P, u = (1ll << 32) % P;
			__m256i yi, x;
			for(int j = 0; j < 8; j++, u = my_mul(u, t)) yi = _mm256_insert_epi32(yi, u, j);
			x = _mm256_set1_epi32(u);

			for (int j = 0; j < N; j += i << 1) {
				__m256i y = yi;
				for(int l = 0; l < i; l += 8){
					__m256i v[2];
					auto f = [](__m256i &v1, __m256i &v2, __m256i a, __m256i b){
						v1 = avx_add(a, b);
						v2 = avx_sub(a, b);
					};

					for(int t = 0; t < 2; t++)
						v[t] = _mm256_stream_load_si256((__m256i *)(A+j+i*t+l));

					f(v[0], v[1], v[0], avx_mul(v[1], y));

					for(int t = 0; t < 2; t++)
						_mm256_store_si256((__m256i *)(A+j+i*t+l), v[t]);

					y = avx_mul(y, x);
				}
			}
		} // */
	}

	void runA(bool rv){ return run(A, rv); }
	void runB(bool rv){ return run(B, rv); }

	void multiplication(){
		for(int i = 0; i < N/2; i++) A[i] = ((ll)A[i]<<32) % P;
		for(int i = 0; i < N/2; i++) B[i] = ((ll)B[i]<<32) % P;
		runA(false);
		runB(false);
		for(int i = 0; i < N; i += 8){
			__m256i a = _mm256_stream_load_si256((__m256i *)(A+i));
			__m256i b = _mm256_stream_load_si256((__m256i *)(B+i));
			_mm256_store_si256((__m256i*)(A+i), avx_mul(a, b));
		}
		runA(true);
		uint r = Pow(N, P-2);
		for(int i = 0; i < N; i++) A[i] = (ull)A[i] * RP % P * r % P; // Decode
	}
}
namespace FFT1{
	const int P = 924844033, R = 5;
	const int SZ = 17, N = 1 << SZ;

	uint Pow(int x, int y) {
		int r = 1;
		while (y) {
			if (y & 1) r = (ll) r * x % P;
			x = (ll) x * x % P;
			y >>= 1;
		}
		return r;
	}

	const uint RP = Pow((1ll<<32)%P, P-2), MP = P-2; // MP = P^-1 mod 2^32
	uint A[N] __attribute__ ((aligned (0x100)));
	uint B[N] __attribute__ ((aligned (0x100)));
	__m256i Pa;

	void init(){ Pa = _mm256_set1_epi32(P); }

	inline uint fit(uint a){ return a >= P? a-P : a; }

	__m256i avx_add(__m256i a, __m256i b){
		__m256i c = _mm256_add_epi32(a, b);
		__m256i d = _mm256_sub_epi32(c, Pa);
		return _mm256_min_epu32(c, d);
	}

	__m256i avx_sub(__m256i a, __m256i b){
		__m256i c = _mm256_sub_epi32(a, b);
		__m256i d = _mm256_add_epi32(c, Pa);
		return _mm256_min_epu32(c, d);
	}

	__m256i avx_fit(__m256i a){
		__m256i b = _mm256_sub_epi32(a, Pa);
		return _mm256_min_epu32(a, b);
	}

	uint my_mul(uint a, uint b){
		return fit(((ull)a*b + (ull)P*(a*b*MP)) >> 32);
	}

	__m256i avx_mul(__m256i a, __m256i b){
		__m256i res[2];
		__m256i p = _mm256_mullo_epi32(_mm256_mullo_epi32(a, b), _mm256_set1_epi32(MP));

		__m256i ax = _mm256_shuffle_epi32(a, 0x50);
		__m256i bx = _mm256_shuffle_epi32(b, 0x50);
		__m256i px = _mm256_shuffle_epi32(p, 0x50);
		__m256i c = _mm256_mul_epu32(ax, bx);
		__m256i f = _mm256_mul_epu32(px, Pa);

		res[0] = _mm256_add_epi64(c, f);

		ax = _mm256_shuffle_epi32(a, 0xfa);
		bx = _mm256_shuffle_epi32(b, 0xfa);
		px = _mm256_shuffle_epi32(p, 0xfa);
		c = _mm256_mul_epu32(ax, bx);
		f = _mm256_mul_epu32(px, Pa);

		res[1] = _mm256_add_epi64(c, f);

		return avx_fit(_mm256_hadd_epi32(res[0], res[1]));
	}

	inline void run(uint* A, bool rv) {
		int j = 0, k = 0;
		for (int i = 1; i < N; i++) {
			for (k = N >> 1; j >= k; k >>= 1) j -= k;
			j += k;
			if (i < j) swap(A[i], A[j]);
		}
		for (int i = 1; i < 8; i <<= 1) {
			uint x = ((ull)Pow(rv ? Pow(R, P - 2) : R, P / i >> 1) << 32) % P;
			for (int j = 0; j < N; j += i << 1) {
				uint y = (1ll<<32) % P;
				for (int k = 0; k < i; k++) {
					uint z = my_mul(A[i+j+k], y);
					A[i+j+k] = fit(A[j+k] - z + P);
					A[j+k] = fit(A[j+k] + z);
					y = my_mul(y, x);
				}
			}
		}
		for (int i = 8; i < N; i <<= 1) {
			uint t = ((ull)Pow(rv ? Pow(R, P - 2) : R, P / i >> 1) << 32) % P, u = (1ll << 32) % P;
			__m256i yi, x;
			for(int j = 0; j < 8; j++, u = my_mul(u, t)) yi = _mm256_insert_epi32(yi, u, j);
			x = _mm256_set1_epi32(u);

			for (int j = 0; j < N; j += i << 1) {
				__m256i y = yi;
				for(int l = 0; l < i; l += 8){
					__m256i v[2];
					auto f = [](__m256i &v1, __m256i &v2, __m256i a, __m256i b){
						v1 = avx_add(a, b);
						v2 = avx_sub(a, b);
					};

					for(int t = 0; t < 2; t++)
						v[t] = _mm256_stream_load_si256((__m256i *)(A+j+i*t+l));

					f(v[0], v[1], v[0], avx_mul(v[1], y));

					for(int t = 0; t < 2; t++)
						_mm256_store_si256((__m256i *)(A+j+i*t+l), v[t]);

					y = avx_mul(y, x);
				}
			}
		} // */
	}

	void runA(bool rv){ return run(A, rv); }
	void runB(bool rv){ return run(B, rv); }

	void multiplication(){
		for(int i = 0; i < N; i++) A[i] = ((ll)A[i]<<32) % P;
		for(int i = 0; i < N; i++) B[i] = ((ll)B[i]<<32) % P;
		runA(false);
		runB(false);
		for(int i = 0; i < N; i += 8){
			__m256i a = _mm256_stream_load_si256((__m256i *)(A+i));
			__m256i b = _mm256_stream_load_si256((__m256i *)(B+i));
			_mm256_store_si256((__m256i*)(A+i), avx_mul(a, b));
		}
		runA(true);
		uint r = Pow(N, P-2);
		for(int i = 0; i < N; i++) A[i] = (ull)A[i] * RP % P * r % P; // Decode
	}
}

constexpr int SIZE = 300016;
char s1[SIZE], s2[SIZE], ans[SIZE*2+1];

ll crt(int a, int b){
	ll c = (b * 798595496ll) % 998244353 * 924844033 + (a * 184968794ll) % 924844033 * 998244353;
	if(c >= 998244353ll * 924844033) c -= 998244353ll * 924844033;
	return c;
}

int main() {
	int U = 5;
	
	for(int i = 0; i < U; i++) s1[i] = s2[i] = '0';
	scanf("%s%s", s1+U, s2+U);
	int l1 = strlen(s1), l2 = strlen(s2);
	
	for(int i = 0, idx = 0; i+U < l1; i += U, idx++){
		FFT1::A[idx] = 0;
		for(int j = U-1; j >= 0; j--) FFT1::A[idx] = FFT1::A[idx] * 10 + s1[l1-1-i-j] - '0';
		FFT2::A[idx] = FFT1::A[idx];
	}
	for(int i = 0, idx = 0; i+U < l2; i += U, idx++){
		FFT1::B[idx] = 0;
		for(int j = U-1; j >= 0; j--) FFT1::B[idx] = FFT1::B[idx] * 10 + s2[l2-1-i-j] - '0';
		FFT2::B[idx] = FFT1::B[idx];
	}
	FFT1::init();
	FFT2::init();
	
	FFT1::multiplication();
	FFT2::multiplication();
	
	ll cur = 0;
	for(int i = 0, idx = 0; i < SIZE*2; i += U, idx++){
		cur += crt(FFT1::A[idx], FFT2::A[idx]);
		for(int j = 0; j < U; j++){
			ans[2*SIZE-1-i-j] = cur%10 + '0'; cur /= 10;
		}
	}
	for(int i = 0; i < SIZE*2; i++){
		if(ans[i] != '0'){
			fwrite(ans+i, 1, SIZE*2-i, stdout);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}

// https://www.acmicpc.net/source/11609951
