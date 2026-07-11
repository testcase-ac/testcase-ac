#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);

	/* Read input */

	const int N = inf.readInt();

	const vector<ll> A = [&]() {
		auto V = inf.readLongs(N);
		V.insert(V.begin(), 0ll);
		return V;
	}();

	const vector<int> C = [&]() {
		auto V = inf.readInts(N - 1);
		V.insert(V.begin(), 0);
		return V;
	}();
	const vector<ll> L = [&]() {
		auto V = inf.readLongs(N - 1);
		V.insert(V.begin(), 0);
		return V;
	}();

	/* Precompute tree */

	const vector<int> depth = [&]() {
		vector<int> V(N + 1, 0);
		V[N] = 1;
		for (int i = N - 1; 1 <= i; i--) {
			V[i] = 1 + V[C[i]];
		}
		return V;
	}();

	/* Read outputs */

	const auto readAndCheck = [&](InStream &in) -> long long {
		int a = in.readInt(1, N, "a");
		int b = in.readInt(1, N, "b");

		in.ensuref(a != b, "Two vertices should be distinct: a=%d, b=%d", a, b);

		ll sum = 0, mx = max(A[a], A[b]);
		while (true) {
			mx = max({mx, A[a], A[b]});
			if (a == b) {
				break;
			}

			if (depth[a] > depth[b]) {
				swap(a, b);
			}
			// Now, depth[a] <= depth[b].

			sum += L[b];
			b = C[b];
		}

		return sum - mx;
	};

	const ll myAns = readAndCheck(ans);
	const ll yourAns = readAndCheck(ouf);

	/* Verdict */

	if (myAns > yourAns) {
		quitf(_wa, "Wrong Answer: Jury found %lld but yours is %lld", myAns, yourAns);
	} else if(myAns < yourAns) {
		quitf(_fail, "You found %lld better than jury's %lld", yourAns, myAns);
	} else {
		quitf(_ok, "Correct: %lld", myAns);
	}
}
