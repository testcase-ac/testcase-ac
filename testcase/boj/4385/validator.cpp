#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> ram(1000, 0);
    int words = 0;
    while (!inf.eof()) {
        ensuref(words < 1000, "more than 1000 RAM words");
        string token = inf.readToken("[0-9]{3}", "word");
        inf.readEoln();
        ram[words++] = stoi(token);
    }
    ensuref(words > 0, "input must contain at least one RAM word");

    vector<int> reg(10, 0);
    int pc = 0;
    int executed = 0;
    bool halted = false;
    while (executed < 100000) {
        int inst = ram[pc];
        pc = (pc + 1) % 1000;
        ++executed;

        int op = inst / 100;
        int d = (inst / 10) % 10;
        int n = inst % 10;

        if (op == 1) {
            ensuref(d == 0 && n == 0, "invalid halt instruction %03d", inst);
            halted = true;
            break;
        }
        if (op == 2) {
            reg[d] = n;
        } else if (op == 3) {
            reg[d] = (reg[d] + n) % 1000;
        } else if (op == 4) {
            reg[d] = (reg[d] * n) % 1000;
        } else if (op == 5) {
            reg[d] = reg[n];
        } else if (op == 6) {
            reg[d] = (reg[d] + reg[n]) % 1000;
        } else if (op == 7) {
            reg[d] = (reg[d] * reg[n]) % 1000;
        } else if (op == 8) {
            reg[d] = ram[reg[n]];
        } else if (op == 9) {
            ram[reg[n]] = reg[d];
        } else {
            if (reg[n] != 0) {
                pc = reg[d];
            }
        }
    }

    ensuref(halted, "program does not halt within 100000 instructions");
    inf.readEof();
}
