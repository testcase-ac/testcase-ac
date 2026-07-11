// https://github.com/MikeMirzayanov/testlib/blob/750b0308df70ca899c351e15246419f71fc6a9b5/testlib.h
#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

long long res[100004], ansSum, oufSum;

void makeLowercase(string &s) {
	for (char& c : s) {
		if ('A' <= c and c <= 'Z') c += 'a' - 'A';
	}
}

int main(int argc, char * argv[])
{
	registerTestlibCmd(argc, argv);

	string outP = ouf.readString();
	string ansP = ans.readString();

	makeLowercase(outP);
	makeLowercase(ansP);

	if (outP != ansP) {
		quitf(_wa, "You answered '%s', but it is actually '%s'.", outP.c_str(), ansP.c_str());
	}

	if (ansP == "no") {
		quitf(_ok, "Output is correct");
	}


	int N = inf.readInt();
	int M = inf.readInt();

	for (int i=1; i<=N; i++) {
		long long x = ans.readLong();
		ansSum += abs(x);
	}

	// 1. The output minimizes the sum of absolute values of weight
	for (int i=1; i<=N; i++) {
		res[i] = ouf.readLong(-ansSum, ansSum);
		oufSum += abs(res[i]);

		if (oufSum > ansSum)
			quitf(_wa, "Sum of weights of output is larger than the optimal sum");
	}

	// 2. The output satisfies all the conditions given by input
	for (int i=0; i<M; i++) {
		int x = inf.readInt();
		int y = inf.readInt();
		int w = inf.readInt();

		if (res[x] + res[y] != w) {
			quitf(_wa, "Output does not satisfies a input condition: Edge (res[%d] = %lld) x ---[%d]--- y (res[%d] = %lld) is wrong.", x, res[x], w, y, res[y]);
		}
	}

	if (oufSum < ansSum)
		quitf(_fail, "WE ARE DOOMED");

	quitf(_ok, "Output is correct");
}
