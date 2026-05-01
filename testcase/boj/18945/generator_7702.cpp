#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of boards
    int N = rnd.next(1, 10);
    println(N);

    // Generate each board with exactly one A or B bomb
    for (int i = 0; i < N; i++) {
        int R = rnd.next(1, 10);
        int maxC = 40 / R;
        int C = rnd.next(1, min(maxC, 10));
        println(R, C);
        // Position and type of the single non-C bomb
        int br = rnd.next(1, R);
        int bc = rnd.next(1, C);
        char typ = rnd.any(string("AB"));
        // Fill the board
        for (int r = 1; r <= R; r++) {
            string row;
            row.reserve(C);
            for (int c = 1; c <= C; c++) {
                if (r == br && c == bc) row += typ;
                else row += 'C';
            }
            println(row);
        }
    }

    // Number of games/queries
    int T = rnd.next(1, 10);
    println(T);
    // Each query: K swaps, range [U, V]
    for (int i = 0; i < T; i++) {
        int U = rnd.next(1, N);
        int V = rnd.next(U, N);
        int K = rnd.next(1, N);
        println(K, U, V);
    }

    return 0;
}
