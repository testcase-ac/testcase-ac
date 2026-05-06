//제 코드가 너무 느려서 qoj에서 가장 빠르게 도는 코드인 huangkx님 코드 올려요

#include <bits/stdc++.h>
using namespace std;

const int N = 200, M = 200, K = 100;

namespace Math {
	const int P = 998244353;
	inline int add(int x, int y) { return x + y >= P ? x + y - P : x + y; }
	inline int sub(int x, int y) { return x < y ? x + P - y : x - y; }
	inline int mul(int x, int y) { return 1ll * x * y % P; }
	int Qpow(int x, int y, int Mod) {
		int res = 1;
		while(y) { if(y & 1) res = 1ll * res * x % Mod; x = 1ll * x * x % Mod; y >>= 1; }
		return res;
	}
	inline int Inv(int x) { return Qpow(x, P - 2, P); }
	const int T = (N + K - 2) + (M + K - 2);
	int C[T + 1][T + 1];
	void Init_C() {
		for(int i = 0; i <= T; ++ i) {
			C[i][0] = 1;
			for(int j = 1; j <= i; ++ j) C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
		}
	}
	int Calc(int x, int y, int xx, int yy) {
		if(x - xx < 0 || yy - y < 0) return 0;
		return C[x - xx + yy - y][x - xx];
	}
}
using namespace Math;

namespace Matrix {
	vector < vector < int > > p(K);
	struct Mat {
		int a[K][K], n;
		void Init(int siz) { n = siz; for(int i = 1; i <= n; ++ i) for(int j = 1; j <= n; ++ j) a[i][j] = 0; }
		void Madoka() {
			for(int i = 1; i < n; ++ i) {
				int k = 0; for(int j = i + 1; j <= n; ++ j) if(a[j][i]) { k = j; break; }
				if(! k) continue;
				if(k ^ (i + 1)) {
					swap(a[k], a[i + 1]);
					for(int j = 1; j <= n; ++ j) swap(a[j][k], a[j][i + 1]);
				}
				int inv = Inv(a[i + 1][i]);
				for(int j = i + 2; j <= n; ++ j) {
					int t = mul(a[j][i], inv);
					for(k = 1; k <= n; ++ k) a[j][k] = sub(a[j][k], mul(t, a[i + 1][k]));
					for(k = 1; k <= n; ++ k) a[k][i + 1] = add(a[k][i + 1], mul(t, a[k][j])); // add, not sub
				}
			}
		}
		vector < int > Hessenberg() {
			Madoka();
			p[0].resize(1); p[0][0] = 1;
			for(int i = 1; i <= n; ++ i) {
				p[i].resize(i + 1); for(int j = 0; j <= i; ++ j) p[i][j] = 0;
				for(int j = 0; j < i; ++ j) p[i][j] = sub(p[i][j], mul(p[i - 1][j], a[i][i]));
				for(int j = 0; j < i; ++ j) p[i][j + 1] = add(p[i][j + 1], p[i - 1][j]);
				for(int j = 1, prd = 1; j <= i - 1; ++ j) {
					prd = mul(prd, a[i - j + 1][i - j]);
					for(int k = 0; k <= i - j - 1; ++ k) p[i][k] = sub(p[i][k], mul(p[i - j - 1][k], mul(prd, a[i - j][i])));
				}
			}
			return p[n];
		}
	};
	vector < int > det_AB(Mat A, Mat B) { // det(Ax+B)
		int prd = 1, cnt = 0, n = A.n;
		for(int i = 1; i <= n; ++ i) {
			int k;
			while(true) {
				k = 0; for(int j = i; j <= n; ++ j) if(A.a[j][i]) { k = j; break; } // a[j][i], not a[i][j]
				if(k) break;
				for(int j = 1; j < i; ++ j) {
					int t = mul(A.a[j][i], Inv(A.a[j][j]));
					for(k = 1; k <= n; ++ k) {
						A.a[k][i] = sub(A.a[k][i], mul(t, A.a[k][j]));
						B.a[k][i] = sub(B.a[k][i], mul(t, B.a[k][j]));
					}
				}
				++ cnt;
				if(cnt > n + 1) {
					vector < int > res; res.push_back(0);
					return res;
				}
				for(k = 1; k <= n; ++ k) {
					swap(A.a[k][i], B.a[k][i]);
					B.a[k][i] = 0; ///
				}
			}
			if(k ^ i) {
				swap(A.a[i], A.a[k]);
				swap(B.a[i], B.a[k]);
				prd = sub(0, prd);
			}
			int inv = Inv(A.a[i][i]); prd = mul(prd, A.a[i][i]);
			for(int j = 1; j <= n; ++ j) {
				A.a[i][j] = mul(A.a[i][j], inv);
				B.a[i][j] = mul(B.a[i][j], inv);
			}
			for(int j = 1; j <= n; ++ j) {
				if(j == i) continue;
				int t = A.a[j][i];
				for(k = 1; k <= n; ++ k) {
					A.a[j][k] = sub(A.a[j][k], mul(t, A.a[i][k]));
					B.a[j][k] = sub(B.a[j][k], mul(t, B.a[i][k]));
				}
			}
		}
		for(int i = 1; i <= n; ++ i) for(int j = 1; j <= n; ++ j) B.a[i][j] = sub(0, B.a[i][j]);
		vector < int > tmp = B.Hessenberg(); vector < int > res;
		for(int i = cnt; i < ((int)tmp.size()); ++ i) res.emplace_back(mul(tmp[i], prd));
		return res;
	}
}
using namespace Matrix;

int n, m, k, r, c, v; Mat A, B;
vector < int > ply;

int main() {
	Init_C();
	cin >> n >> m >> k >> r >> c >> v;
	A.Init(k - 1); B.Init(k - 1);
	int x = r + v - 1, y = c + v - 1;
	for(int i = 1; i <= k - 1; ++ i) { // (n+i,i)
		for(int j = 1; j <= k - 1; ++ j) { // (j,m+j)
			B.a[i][j] = Calc(n + i, i, j, m + j); // A,B 不要弄反了。
			for(int t = 0; t < min(x, y); ++ t) { // min(x, y), not min(r, c)
				int val = mul(Calc(n + i, i, x - t, y - t), Calc(x - t, y - t, j, m + j));
				B.a[i][j] = sub(B.a[i][j], val); // ? 没懂
				if(t) A.a[i][j] = add(A.a[i][j], val);
			}
		}
	}
	ply = det_AB(A, B); ply.resize(v); printf("%d\n", ply[v - 1]);
	return 0;
}
// 女孩对我说 我看不清她的脸
// 参考多篇博客，主要参考：https://www.cnblogs.com/TheLastCandy/p/17929769.html
// https://www.cnblogs.com/rainybunny/p/16375383.html#-gym-102978aascending-matrix-
// https://www.cnblogs.com/Farmer-djx/p/18156135
// https://www.cnblogs.com/apjifengc/p/17417387.html
// 没懂：https://www.cnblogs.com/Tantantann/p/17543515.html
