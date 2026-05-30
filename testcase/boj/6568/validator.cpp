#include "testlib.h"
#include <array>
#include <vector>
#include <string>
using namespace std;

static inline int parseByte(const string& s) {
    int v = 0;
    for (char c : s) {
        v = (v << 1) + (c - '0');
    }
    return v;
}

struct MachineState {
    array<int, 32> mem{};
    int pc = 0;
    int acc = 0;
    bool halted = false;
};

static inline void step(MachineState& state) {
    if (state.halted) {
        return;
    }

    int instr = state.mem[state.pc] & 255;
    int opcode = (instr >> 5) & 7;
    int operand = instr & 31;

    state.pc = (state.pc + 1) & 31;

    switch (opcode) {
        case 0:
            state.mem[operand] = state.acc & 255;
            break;
        case 1:
            state.acc = state.mem[operand] & 255;
            break;
        case 2:
            if ((state.acc & 255) == 0) {
                state.pc = operand;
            }
            break;
        case 3:
            break;
        case 4:
            state.acc = (state.acc + 255) & 255;
            break;
        case 5:
            state.acc = (state.acc + 1) & 255;
            break;
        case 6:
            state.pc = operand;
            break;
        case 7:
            state.halted = true;
            break;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    ensuref(!inf.eof(), "Input must contain at least one test case");

    while (!inf.eof()) {
        ++tc;
        setTestCase(tc);
        ensuref(tc <= 100000, "Too many test cases: %d (max 100000)", tc);

        MachineState initial;
        for (int i = 0; i < 32; ++i) {
            string s = inf.readLine("[01]{8}", "mem_byte");
            initial.mem[i] = parseByte(s);
        }

        MachineState slow = initial;
        MachineState fast = initial;
        while (true) {
            step(slow);
            step(fast);
            step(fast);

            if (slow.halted || fast.halted) {
                break;
            }
            ensuref(!(slow.pc == fast.pc && slow.acc == fast.acc && slow.mem == fast.mem),
                    "Test case %d: program does not terminate", tc);
        }
    }

    inf.readEof();
}
