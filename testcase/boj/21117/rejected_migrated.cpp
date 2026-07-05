//제 코드는 아니고 가장 빠르게 도는 제출 번호 27351982의 코드입니다
#include <bits/stdc++.h>

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	using bs = bitset<301>;

	int N; cin >> N;
	vector<bs> A(N); for (auto& a : A) cin >> a;
	vector<bs> B(N); for (auto& b : B) cin >> b;

	auto solve = [&]() -> bs {
		int num_extra = 0;
		vector<array<bs, 2>> basis(N);

		for (int i = 0; i < N; i++) {
			while (true) {
				if (!A[i].any()) {
					if (!B[i].any()) {
						return bs();
					}
					A[i] = B[i];
					B[i].reset();
					num_extra++;
				}
				int j = int(A[i]._Find_first());
				if (basis[j][0][j]) {
					A[i] ^= basis[j][0];
					B[i] ^= basis[j][1];
					continue;
				} else {
					basis[j][0] = A[i];
					basis[j][1] = B[i];
					break;
				}
			}
		}

		for (int i = N-1; i >= 0; i--) {
			bs cur = basis[i][0];
			bs val = basis[i][1];
			for (int j = i+1; j < N; j++) {
				if (cur[j]) val ^= B[j];
			}
			B[i] = val;
		}

		// Find the char poly of B[i]
		bs ans; ans[0] = 1;
		int deg = 0;
		for (int i = 0; i < N; i++) {
			{
				int j = int(B[i]._Find_next(i));
				if (j >= N) {
					bs nans;
					for (; deg <= i; ans <<= 1, deg++) {
						if (B[i][deg]) nans ^= ans;
					}
					ans ^= nans;
					continue;
				}
				if (j != i+1) {
					swap(B[j], B[i+1]);
					for (auto& b : B) {
						bool tmp = b[j];
						b[j] = b[i+1];
						b[i+1] = tmp;
					}
				}
			}
			assert(B[i][i+1]);
			bs msk = B[i]; msk.flip(i+1);
			for (int k = 0; k < N; k++) {
				if (msk[k]) B[i+1] ^= B[k];
			}
			for (auto& b : B) {
				if (b[i+1]) b ^= msk;
			}
		}

		return ans >> num_extra;
	};

	bs ans = solve();
	for (int i = 0; i <= N; i++) {
		cout << ans[i] << '\n';
	}

	return 0;
}
