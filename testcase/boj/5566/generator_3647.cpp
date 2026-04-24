#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small board size
    int N = rnd.next(2, 10);
    // Hyper-parameters for instruction generation
    double pZero = rnd.next() * 0.7;           // Probability an instruction is zero
    double pPos = rnd.next();                  // Given non-zero, probability it's positive
    int maxInstr = rnd.next(1, N);             // Max magnitude of an instruction

    // Generate board instructions (1-based)
    vector<int> instr(N+1);
    instr[1] = 0;
    instr[N] = 0;
    for (int i = 2; i < N; i++) {
        if (rnd.next() < pZero) {
            instr[i] = 0;
        } else {
            bool positive = rnd.next() < pPos;
            if (positive) {
                instr[i] = rnd.next(1, maxInstr);
            } else {
                int maxBack = i - 1;
                int mag = rnd.next(1, min(maxInstr, maxBack));
                instr[i] = -mag;
            }
        }
    }

    // Simulate dice rolls to guarantee reaching N
    vector<int> dice;
    int pos = 1;
    while (pos < N) {
        int roll = rnd.next(1, 6);
        dice.push_back(roll);
        pos += roll;
        if (pos < N) {
            pos += instr[pos];
        }
    }
    int baseRolls = (int)dice.size();

    // Pad extra rolls (unused) for diversity
    int extra = rnd.next(0, 3);
    for (int i = 0; i < extra; i++)
        dice.push_back(rnd.next(1, 6));

    int M = baseRolls + extra;

    // Output in required format
    println(N, M);
    for (int i = 1; i <= N; i++)
        println(instr[i]);
    for (int d : dice)
        println(d);

    return 0;
}
