#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/*
Problem summary (for validator logic):
- Input: single line with four positive integers s1, s2, s3, s4.
- Constraints:
    * 1 ≤ s_i ≤ 1000
    * For all i: 2*s_i < sum_j s_j
      (i.e., no single side is at least half of the perimeter; strictly less)
- Exactly one line, exactly four integers, then EOF.
- Numbers are normal decimal integers -> enforce canonical form via readInt.
- We must also validate the global property: the inequality 2*s_i < sum s_j
  for all i, which is explicitly guaranteed by the statement.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_S = 1;
    const int MAX_S = 1000;

    // Read exactly four integers on a single line
    long long s[4];
    for (int i = 0; i < 4; ++i) {
        s[i] = inf.readInt(MIN_S, MAX_S, ("s_" + to_string(i + 1)).c_str());
        if (i + 1 < 4)
            inf.readSpace();
    }
    inf.readEoln();

    long long sum = 0;
    for (int i = 0; i < 4; ++i) sum += s[i];

    // Check global constraint: 2*s_i < sum for all i
    for (int i = 0; i < 4; ++i) {
        ensuref(2LL * s[i] < sum,
                "Constraint violated: 2*s_%d (= %lld) must be strictly less than "
                "sum of all sides (= %lld)",
                i + 1, 2LL * s[i], sum);
    }

    inf.readEof();
}
