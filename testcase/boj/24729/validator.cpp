#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
 We must validate:
 - Format:
   * One integer N on first line, 1 <= N <= 50000.
   * Second line: N integers a_i, each 1 <= a_i <= 100000.
   * Strict spaces/newlines, then EOF.
 - Canonical integer format is automatically enforced by readInt/readInts.

 There is no additional guaranteed property (like "answer always exists"),
 and the problem is about rearranging the given multiset into a special
 "stair" sequence, which is the task of the solution, not the validator.
 So we do NOT simulate or check that property here.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(N, 1, 100000, "a_i");
    inf.readEoln();

    inf.readEof();
}
