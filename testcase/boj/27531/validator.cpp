#include "testlib.h"
using namespace std;
typedef long long ll;
 
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
 
	int N = inf.readInt(1, 200'000, "N"); inf.readEoln();

	set<int> au, bu;
	for (int i = 1; i <= N; i++) {
		int ai = inf.readInt(1, N, "a_i"); inf.readSpace();
		int bi = inf.readInt(1, N, "b_i"); inf.readSpace();
		int pi = inf.readInt(1, 1'000, "p_i"); inf.readEoln();

		au.insert(ai);
		bu.insert(bi);
	}

	ensuref(au.size() == N, "a_i must be distinct");
	ensuref(bu.size() == N, "b_i must be distinct");

	for (int i = 1; i <= N; i++) {
		ensuref(au.count(i) == 1, "a_i must be 1..N");
		ensuref(bu.count(i) == 1, "b_i must be 1..N");
	}

	inf.readEof();
	return 0;
}
