#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // We produce some trivial solvable cases for N=2 (all R),
    // and various unsolvable cases by parity or single mismatch.
    bool makeSolvable = rnd.next(0, 1) == 1;
    if (makeSolvable) {
        // Trivial solvable: N=2, single upward triangle, all R
        println(2);
        println("R");
        println("RR");
    } else {
        // Unsolvable: either parity fail on larger N, or single mismatch on N=2
        if (rnd.next(0, 1) == 0) {
            // Parity-based unsolvable: total cells not divisible by 3
            vector<int> parityNs = {1, 4, 7, 10};
            int N = rnd.any(parityNs);
            int S = N * (N + 1) / 2;
            println(N);
            int idx = 0;
            for (int i = 1; i <= N; i++) {
                string line;
                for (int j = 0; j < i; j++) {
                    line += (rnd.next(0,1) ? 'R' : 'B');
                    idx++;
                }
                println(line);
            }
        } else {
            // Single-mismatch unsolvable: start from solvable N=2 then flip one
            int N = 2;
            vector<char> c = {'R','R','R'}; // idx 0:(1,1), 1:(2,1), 2:(2,2)
            int p = rnd.next(0, 2);
            c[p] = (c[p] == 'R' ? 'B' : 'R');
            println(N);
            // print row 1
            println(string(1, c[0]));
            // print row 2
            string row2;
            row2 += c[1];
            row2 += c[2];
            println(row2);
        }
    }
    return 0;
}
