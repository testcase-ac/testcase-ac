#include "testlib.h"

#include <vector>
using namespace std;

struct CaseData {
    int m;
    int target;
    vector<int> gates;
    vector<int> changeable;
    vector<int> leaves;
};

int randomOddM(int mode) {
    if (mode == 0) return 3;
    if (mode == 1) return rnd.any(vector<int>{5, 7, 9});
    if (mode == 2) return rnd.any(vector<int>{15, 21, 29});
    return rnd.next(1, 14) * 2 + 1;
}

CaseData makeCase(int mode) {
    CaseData tc;
    tc.m = randomOddM(mode);
    tc.target = rnd.next(0, 1);

    int interior_count = (tc.m - 1) / 2;
    int leaf_count = (tc.m + 1) / 2;
    tc.gates.resize(interior_count);
    tc.changeable.resize(interior_count);
    tc.leaves.resize(leaf_count);

    for (int i = 0; i < interior_count; ++i) {
        if (mode == 3) {
            tc.gates[i] = i % 2;
            tc.changeable[i] = (i % 3 != 0);
        } else if (mode == 4) {
            tc.gates[i] = rnd.next(0, 1);
            tc.changeable[i] = 0;
        } else if (mode == 5) {
            tc.gates[i] = rnd.next(0, 1);
            tc.changeable[i] = 1;
        } else {
            tc.gates[i] = rnd.next(0, 1);
            tc.changeable[i] = rnd.next(0, 1);
        }
    }

    for (int i = 0; i < leaf_count; ++i) {
        if (mode == 1) {
            tc.leaves[i] = (i == rnd.next(0, leaf_count - 1));
        } else if (mode == 2) {
            tc.leaves[i] = i % 2;
        } else if (mode == 4) {
            tc.leaves[i] = rnd.next(0, 4) == 0;
        } else {
            tc.leaves[i] = rnd.next(0, 1);
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int case_count = rnd.next(2, 20);
    println(case_count);

    for (int case_id = 0; case_id < case_count; ++case_id) {
        int mode = case_id < 6 ? case_id : rnd.next(0, 5);
        CaseData tc = makeCase(mode);

        println(tc.m, tc.target);
        for (int i = 0; i < (int)tc.gates.size(); ++i) {
            println(tc.gates[i], tc.changeable[i]);
        }
        for (int value : tc.leaves) {
            println(value);
        }
    }

    return 0;
}
