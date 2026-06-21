#include "testlib.h"

#include <vector>

using namespace std;

struct CaseData {
    int m;
    int target;
    vector<int> gate;
    vector<int> changeable;
    vector<int> leaf;
};

CaseData makeCase(int mode) {
    CaseData tc;

    int height = 1;
    if (mode == 0) {
        height = 1;
    } else if (mode == 1) {
        height = rnd.next(1, 3);
    } else if (mode == 2) {
        height = rnd.next(2, 4);
    } else {
        height = rnd.next(1, 5);
    }

    tc.m = (1 << (height + 1)) - 1;
    int internalNodes = (tc.m - 1) / 2;
    int leafNodes = (tc.m + 1) / 2;

    tc.target = rnd.next(0, 1);
    tc.gate.resize(internalNodes);
    tc.changeable.resize(internalNodes);
    tc.leaf.resize(leafNodes);

    for (int i = 0; i < internalNodes; ++i) {
        if (mode == 2) {
            tc.gate[i] = i % 2;
        } else if (mode == 3) {
            tc.gate[i] = (i + height) % 2;
        } else {
            tc.gate[i] = rnd.next(0, 1);
        }

        if (mode == 0) {
            tc.changeable[i] = rnd.next(0, 1);
        } else if (mode == 2) {
            tc.changeable[i] = i % 3 == 0 ? 1 : 0;
        } else if (mode == 3) {
            tc.changeable[i] = 0;
        } else {
            tc.changeable[i] = rnd.next(0, 1);
        }
    }

    int leafPattern = rnd.next(0, 4);
    for (int i = 0; i < leafNodes; ++i) {
        if (mode == 3) {
            tc.leaf[i] = rnd.next(0, 1);
        } else if (leafPattern == 0) {
            tc.leaf[i] = 0;
        } else if (leafPattern == 1) {
            tc.leaf[i] = 1;
        } else if (leafPattern == 2) {
            tc.leaf[i] = i % 2;
        } else if (leafPattern == 3) {
            tc.leaf[i] = (i / 2) % 2;
        } else {
            tc.leaf[i] = rnd.next(0, 1);
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(2, 20);
    println(t);

    for (int caseNo = 0; caseNo < t; ++caseNo) {
        CaseData tc = makeCase(caseNo % 5);
        println(tc.m, tc.target);

        int internalNodes = (tc.m - 1) / 2;
        for (int i = 0; i < internalNodes; ++i) {
            println(tc.gate[i], tc.changeable[i]);
        }

        for (int value : tc.leaf) {
            println(value);
        }
    }

    return 0;
}
