//code by sebinkim
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using lll = __int128;
using ld = double;
using base = complex <ld>;

const int k = 1 << 17;
const ld pi = acos(-1);

ll F[303030], I[303030], FI[303030], X[303030];
base P[303030], Q[303030];
ll n, p, x;

void fft(base *V, ll k, bool f) {
	ll i, j, l; ld th;
	base w, x, y;

	for (i = 1, j = 0; i < k; i++) {
		for (l = k >> 1; j >= l; l >>= 1) j -= l;
		j += l; if (i < j) swap(V[i], V[j]);
	}

	for (i = 1; i < k; i <<= 1) {
		th = (f ? pi : -pi) / i;
		w = base(cos(th), sin(th));
		for (j = 0; j < k; j += i << 1) {
			auto u = V + j, v = u + i;
			for (l = 0, x = 1; l < i; l++, u++, v++) {
				if (l & 511) x *= w;
				else x = l? base(cos(th * l), sin(th * l)) : 1;
				y = *v * x; *v = *u - y; *u += y;
			}
		}
	}

	if (f) for (i = 0; i < k; i++) {
		V[i] /= k;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll i, j, l, s, t;

	cin >> n >> p;

	F[0] = FI[0] = 1;
	for (i = 1; i <= k + k + 2; i++) {
		I[i] = i == 1? 1 : lll(-p / i) * I[p % i] % p;
		F[i] = F[i - 1] * i % p;
		FI[i] = (lll)FI[i - 1] * I[i] % p;
	}

	X[0] = 1; X[1] = 2;
	for (i = 1, s = 4; i < k; i <<= 1, s <<= 1) {
		for (j = 0; j < s; j++) {
			if (j <= i) {
				t = (lll)FI[j] * FI[i - j] *
					(i - j & 1 ? -1 : 1) % p * X[j] % p;
				P[j] = base(t >> 17, t & k - 1);
				X[s + 1] = (X[s + 1] + (lll)t * I[s + 1 - j]) % p;
			}
			else P[j] = 0;
			t = I[j + 1];
			Q[j] = base(t >> 17, t & k - 1);
		}

		fft(P, s, 0); fft(Q, s, 0);
		for (j = 0; j <= s >> 1; j++) {
			l = j ? s - j : 0;
			base v1 = P[j] + conj(P[l]), v2 = conj(P[j]) - P[l];
			tie(P[j], Q[j], P[l], Q[l]) = make_tuple(
				v1 * Q[j], conj(v2) * conj(Q[l]),
				conj(v1) * Q[l], -v2 * conj(Q[j]));
		}
		fft(P, s, 1); fft(Q, s, 1);

		for (j = i; j < s; j++) {
			X[j + 1] = (((lll)round(P[j].real()) << 33) + ((ll)round(Q[j].real()) >> 1)
			+ ((lll)round(P[j].imag() + Q[j].imag()) << 16)) % p;
		}
		for (j = i; j <= s; j++) {
			X[j + 1] = (lll)F[j + 1] * FI[j - i] % p * X[j + 1] % p;
		}
		for (j = 0; j <= i << 1; j++) {
			X[j] = (lll)X[j << 1] * X[j << 1 | 1] % p;
		}
	}

	s = n / k;
	for (i = 0, x = 1; i < s; i++) x = (lll)x * X[i] % p;
	for (i = s * k + 1; i <= n; i++) x = (lll)x * i % p;

	cout << (x + p) % p << "\n";
	
	return 0;
}
