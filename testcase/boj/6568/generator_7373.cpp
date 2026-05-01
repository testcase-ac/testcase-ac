#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

string to_bin8(int x) {
    string s(8, '0');
    for (int i = 7; i >= 0; --i) {
        s[i] = char('0' + (x & 1));
        x >>= 1;
    }
    return s;
}

string encode(int opcode, int operand = 0) {
    int code = ((opcode & 7) << 5) | (operand & 31);
    return to_bin8(code);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    for (int tc = 0; tc < T; ++tc) {
        // default fill with NOP (011----- => operand zero)
        vector<string> mem(32, encode(3, 0));
        int tpl = rnd.next(1, 4);
        if (tpl == 1) {
            // Simple INC K times then HLT
            int K = rnd.next(1, 15);
            for (int i = 0; i < K; ++i)
                mem[i] = encode(5, 0); // INC
            mem[K] = encode(7, 0); // HLT
            // rest already NOP
        } else if (tpl == 2) {
            // DEC loop: load V from D, loop DEC until zero, then HLT
            int V = rnd.next(1, 10);
            int D = rnd.next(16, 30);
            // code positions 0..4
            mem[0] = encode(1, D);   // LDA D
            mem[1] = encode(4, 0);   // DEC
            mem[2] = encode(2, 4);   // BEQ to addr 4
            mem[3] = encode(6, 1);   // JMP to addr 1
            mem[4] = encode(7, 0);   // HLT
            mem[D] = to_bin8(V);     // data
        } else if (tpl == 3) {
            // Store and reload: LDA D, STA E, LDA E, HLT
            int D = rnd.next(10, 20);
            int E = rnd.next(21, 30);
            while (E == D) E = rnd.next(21, 30);
            int V = rnd.next(0, 255);
            mem[0] = encode(1, D);   // LDA D
            mem[1] = encode(0, E);   // STA E
            mem[2] = encode(1, E);   // LDA E
            mem[3] = encode(7, 0);   // HLT
            mem[D] = to_bin8(V);
        } else {
            // Linear sequence of INC/DEC/NOP, then HLT
            int L = rnd.next(3, 10);
            for (int i = 0; i < L - 1; ++i) {
                int choice = rnd.next(0, 2);
                if (choice == 0) mem[i] = encode(5, 0);
                else if (choice == 1) mem[i] = encode(4, 0);
                else mem[i] = encode(3, 0);
            }
            mem[L - 1] = encode(7, 0);
        }
        // Output this test case: 32 lines
        for (int i = 0; i < 32; ++i) {
            println(mem[i]);
        }
    }
    return 0;
}
