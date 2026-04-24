#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 10);

    // Prepare empty board
    vector<string> board(N, string(M, '.'));

    // Choose style: 0=random noise, 1=clusters, 2=stripes
    int style = rnd.next(0, 2);

    if (style == 0) {
        // Uniform random noise
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                board[i][j] = (rnd.next() < p ? '*' : '.');
    }
    else if (style == 1) {
        // Clustered stars
        int maxClusters = min(5, N * M);
        int clusters = rnd.next(1, maxClusters);
        for (int c = 0; c < clusters; c++) {
            int cx = rnd.next(0, N-1);
            int cy = rnd.next(0, M-1);
            int r = rnd.next(0, max(N, M) / 3);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    int d = abs(i - cx) + abs(j - cy);
                    if (d <= r && rnd.next() < 0.8)
                        board[i][j] = '*';
                }
            }
        }
        // Some stray noise
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (board[i][j] == '.' && rnd.next() < 0.05)
                    board[i][j] = '*';
    }
    else {
        // Stripes pattern
        bool horizontal = rnd.next(0,1) == 0;
        int width = rnd.next(1, 2);
        int period = rnd.next(1, 3);
        if (horizontal) {
            for (int i = 0; i < N; i++) {
                bool fill = ((i / period) % 2) == 0;
                for (int j = 0; j < M; j++)
                    board[i][j] = fill ? '*' : '.';
                // possibly narrow gaps
                if (fill && width > 1 && i+1 < N && rnd.next() < 0.5) {
                    for (int j = 0; j < M; j++)
                        board[i+1][j] = '*';
                }
            }
        } else {
            for (int j = 0; j < M; j++) {
                bool fill = ((j / period) % 2) == 0;
                for (int i = 0; i < N; i++)
                    board[i][j] = fill ? '*' : '.';
                if (fill && width > 1 && j+1 < M && rnd.next() < 0.5) {
                    for (int i = 0; i < N; i++)
                        board[i][j+1] = '*';
                }
            }
        }
    }

    // Ensure at least one hole
    bool any = false;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (board[i][j] == '*')
                any = true;
    if (!any) {
        int i = rnd.next(0, N-1);
        int j = rnd.next(0, M-1);
        board[i][j] = '*';
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++)
        println(board[i]);

    return 0;
}
