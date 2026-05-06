#include "testlib.h"
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

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_STEPS = 10000000LL; // large safety bound
    int tc = 0;

    while (!inf.eof()) {
        ++tc;
        setTestCase(tc);
        ensuref(tc <= 100000, "Too many test cases: %d (max 100000)", tc);

        vector<int> mem(32);
        for (int i = 0; i < 32; ++i) {
            // Each line must be exactly 8 chars of 0/1, no extra spaces
            string s = inf.readLine("[01]{8}", "mem_byte");
            mem[i] = parseByte(s);
        }

        // Validate the global property: "The program always halts."
        // Simulate the described machine and ensure it reaches HLT.
        int pc = 0;   // 5-bit PC
        int acc = 0;  // 8-bit accumulator
        bool halted = false;

        for (long long steps = 0; steps < MAX_STEPS; ++steps) {
            int instr = mem[pc] & 255;
            int opcode = (instr >> 5) & 7; // top 3 bits
            int operand = instr & 31;      // low 5 bits

            // Increment PC before executing instruction (wrap within 5 bits)
            pc = (pc + 1) & 31;

            switch (opcode) {
                case 0: // STA x
                    mem[operand] = acc & 255;
                    break;
                case 1: // LDA x
                    acc = mem[operand] & 255;
                    break;
                case 2: // BEQ x
                    if ((acc & 255) == 0) pc = operand & 31;
                    break;
                case 3: // NOP
                    break;
                case 4: // DEC
                    acc = (acc + 255) & 255; // decrement with 8-bit wrap
                    break;
                case 5: // INC
                    acc = (acc + 1) & 255;   // increment with 8-bit wrap
                    break;
                case 6: // JMP x
                    pc = operand & 31;
                    break;
                case 7: // HLT
                    halted = true;
                    break;
                default:
                    // unreachable
                    break;
            }

            if (halted) break;
        }

        ensuref(halted, "Test case %d: program did not halt within %lld steps", tc, MAX_STEPS);
    }

    // EOF must be immediate after the last newline read
    inf.readEof();
}
