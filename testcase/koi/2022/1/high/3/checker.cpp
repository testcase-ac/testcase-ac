#include "testlib.h"
#include <bits/stdc++.h>
#define eb emplace_back
#define sz(V) ((int)(V).size())
#define rb(x) ((x)&(-(x)))
using namespace std;

const string YES = "YES";
const string NO = "NO";

struct SEG {
	SEG(int MX) : V(MX+1, 0), MX(MX) {}

	vector<int> V;
	int MX;

	void upd(int x, int r) {
		while(x < MX) {
			if(V[x] < r) V[x] = r;
			x += rb(x);
		}
	}

	int get(int x) {
		int r = 0;
		while(0 < x) {
			if(r < V[x]) r = V[x];
			x -= rb(x);
		}
		return r;
	}
};

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);

	const int N = inf.readInt();

	vector<int> X(N+1), Y(N+1), A(N+1), B(N+1);
	for(int i = 1; i <= N; i++) {
		X[i] = inf.readInt();
		Y[i] = inf.readInt();
		A[i] = inf.readInt();
		B[i] = inf.readInt();
	}

	auto isValid = [&](vector<int> V) -> bool {
		if(sz(V) != N+1) return false;

		vector<bool> chk(N+1, false);
		for(int i = N; i; i--) {
			int v = V[i];
			if(v < 1 || N < v) return false;
			if(v < A[i] || B[i] < v) return false;
			if(chk[v]) return false;
			chk[v] = true;
		}

		for(int i = N; i; i--) {
			if(!chk[i]) return false;
		}

		vector<int> O(N+1);
		for(int i = N; i; i--)
			O[X[i]] = i;

		SEG seg(N+5);
		for(int x = 1; x <= N; x++) {
			int i = O[x];
			int c = seg.get(Y[i]);
			int v = V[i];
			if(v < c) return false;
			seg.upd(Y[i], v);
		}

		return true;
	};

	const string myans = ans.readToken();

	if(YES == myans) {
		vector<int> V(N+1);
		for(int i = 1; i <= N; i++) {
			V[i] = ans.readInt();
		}

		if(!isValid(V)) {
			quitf(_fail, "Invalid answer assignment");
		}
	} else if(NO == myans) {
		// Do nothing
	} else {
		quitf(_fail, "Invalid answer token : %s", myans.c_str());
	}

	const string yourans = ouf.readToken();

	if(YES == yourans) {
		vector<int> V(N+1);
		for(int i = 1; i <= N; i++) {
			V[i] = ouf.readInt();
		}

		if(!isValid(V)) {
			quitf(_wa, "Wrong assignment");
		}
	} else if(NO == yourans) {
		// Do nothing
	} else {
		quitf(_wa, "Invalid token : %s", yourans.c_str());
	}

	if(myans == yourans) {
		quitf(_ok, "Correct : %s", myans.c_str());
	}

	if(YES == yourans) {
		quitf(_fail, "Model did not find any assignment, but the participant did!");
	}

	quitf(_wa, "Wrong Answer : ans=[%s], out=[%s]", myans.c_str(), yourans.c_str());
}
