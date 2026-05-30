#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);

	int N = inf.readInt(1, 100'000, "N");
	inf.readEoln();
	string a = inf.readToken("[TGFP]{1,100000}", "a");
	ensuref((int)a.size() == N, "road length must be N: expected %d, got %d", N, (int)a.size());
	inf.readEoln();
	inf.readEof();
	return 0;
}
