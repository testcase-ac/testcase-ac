#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);
    // Choose a non-black color for the starting codel
    char startColor;
    do {
        startColor = char(rnd.next('A', 'Z'));
    } while (startColor == 'X');

    // Output dimensions
    println(N, M);
    // Build the grid: only (1,1) is the startColor, all others are black ('X').
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char cell = (i == 1 && j == 1 ? startColor : 'X');
            printf("%c", cell);
        }
        printf("\n");
    }
    return 0;
}
