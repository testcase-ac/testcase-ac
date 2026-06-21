#include "testlib.h"

#include <cstdio>
#include <vector>

using namespace std;

void emit(const vector<int>& program) {
    for (int word : program) {
        printf("%03d\n", word);
    }
}

int inst(int op, int d, int n) {
    return op * 100 + d * 10 + n;
}

vector<int> straightLineProgram() {
    int ops = rnd.next(3, 18);
    vector<int> program;
    for (int i = 0; i < ops; ++i) {
        int kind = rnd.next(0, 5);
        int d = rnd.next(0, 9);
        int s = rnd.next(0, 9);
        if (kind == 0) {
            program.push_back(inst(2, d, rnd.next(0, 9)));
        } else if (kind == 1) {
            program.push_back(inst(3, d, rnd.next(0, 9)));
        } else if (kind == 2) {
            program.push_back(inst(4, d, rnd.next(0, 9)));
        } else if (kind == 3) {
            program.push_back(inst(5, d, s));
        } else if (kind == 4) {
            program.push_back(inst(6, d, s));
        } else {
            program.push_back(inst(7, d, s));
        }
    }
    program.push_back(100);
    return program;
}

vector<int> memoryProgram() {
    int address = rnd.next(0, 1);
    int value = rnd.next(0, 9);
    int source = rnd.next(0, 9);
    int addrReg = (source + rnd.next(1, 9)) % 10;
    int target = (addrReg + rnd.next(1, 9)) % 10;

    vector<int> program;
    program.push_back(inst(2, source, value));
    program.push_back(inst(2, addrReg, address));
    program.push_back(inst(9, source, addrReg));
    program.push_back(inst(8, target, addrReg));

    int extraOps = rnd.next(1, 10);
    for (int i = 0; i < extraOps; ++i) {
        program.push_back(inst(rnd.next(3, 7), rnd.next(0, 9), rnd.next(0, 9)));
    }

    program.push_back(100);
    return program;
}

vector<int> branchProgram() {
    vector<int> program;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        int addrReg = rnd.next(0, 8);
        int condReg = (addrReg + rnd.next(1, 8)) % 9;
        program.push_back(inst(2, condReg, 0));
        program.push_back(inst(2, addrReg, 5));
        program.push_back(inst(0, addrReg, condReg));
        program.push_back(inst(3, condReg, rnd.next(1, 9)));
        program.push_back(100);
    } else if (mode == 1) {
        int addrReg = rnd.next(0, 8);
        int condReg = (addrReg + rnd.next(1, 8)) % 9;
        program.push_back(inst(2, condReg, rnd.next(1, 9)));
        program.push_back(inst(2, addrReg, 4));
        program.push_back(inst(0, addrReg, condReg));
        program.push_back(inst(3, condReg, rnd.next(1, 9)));
        program.push_back(100);
    } else {
        int addrReg = rnd.next(0, 8);
        program.push_back(inst(2, addrReg, 3));
        program.push_back(inst(2, 9, rnd.next(1, 9)));
        program.push_back(inst(0, addrReg, 9));
        program.push_back(100);
    }
    return program;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    if (mode == 0) {
        emit(straightLineProgram());
    } else if (mode == 1) {
        emit(memoryProgram());
    } else {
        emit(branchProgram());
    }

    return 0;
}
