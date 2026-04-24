#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: board size
    int N = rnd.next(1, 10);

    // Choose a pattern style for diversity
    // 0 = random blocks, 1 = main diagonal, 2 = anti-diagonal
    // 3 = full random row, 4 = full random column
    int style = rnd.next(0, 4);

    // Some block probabilities for random noise
    vector<double> probs = {0.1, 0.2, 0.3, 0.5};
    double blockProb = rnd.any(probs);

    // Initialize empty board
    vector<string> board(N, string(N, '.'));

    if (style == 0) {
        // Pure random blocking
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (rnd.next() < blockProb) board[i][j] = 'X';
            }
        }
    } else if (style == 1) {
        // Main diagonal blocks
        for (int i = 0; i < N; i++) board[i][i] = 'X';
        // Add a bit of noise
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j]=='.' && rnd.next() < 0.1) board[i][j] = 'X';
    } else if (style == 2) {
        // Anti-diagonal blocks
        for (int i = 0; i < N; i++) board[i][N-1-i] = 'X';
        // Add a bit of noise
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j]=='.' && rnd.next() < 0.1) board[i][j] = 'X';
    } else if (style == 3) {
        // One full random row
        int r = rnd.next(0, N-1);
        for (int j = 0; j < N; j++) board[r][j] = 'X';
        // Random noise elsewhere
        for (int i = 0; i < N; i++)
            if (i != r)
                for (int j = 0; j < N; j++)
                    if (rnd.next() < blockProb / 2) board[i][j] = 'X';
    } else {
        // One full random column
        int c = rnd.next(0, N-1);
        for (int i = 0; i < N; i++) board[i][c] = 'X';
        // Random noise elsewhere
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (j != c && rnd.next() < blockProb / 2) board[i][j] = 'X';
    }

    // Ensure at least one empty cell
    bool hasEmpty = false;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == '.') hasEmpty = true;
    if (!hasEmpty) {
        int i = rnd.next(0, N-1), j = rnd.next(0, N-1);
        board[i][j] = '.';
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        printf("%s\n", board[i].c_str());
    }
    return 0;
}
