#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int F = rnd.next(1, 4); // number of fields
    for (int f = 0; f < F; f++) {
        int N = rnd.next(1, 8);
        int E = rnd.next(1, 8);
        vector<string> g(N, string(E, '.'));
        int pid = rnd.next(0, 4);
        if (pid == 0) {
            // Sparse random obstacles
            int d = rnd.next(0, 3);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < E; j++)
                    if (rnd.next(9) < d) g[i][j] = 'X';
        } else if (pid == 1) {
            // Dense random obstacles
            int d = rnd.next(5, 8);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < E; j++)
                    if (rnd.next(9) < d) g[i][j] = 'X';
        } else if (pid == 2) {
            // Border obstacles + few inside
            int d = rnd.next(0, 2);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < E; j++) {
                    if (i == 0 || i == N-1 || j == 0 || j == E-1) g[i][j] = 'X';
                    else if (rnd.next(9) < d) g[i][j] = 'X';
                }
        } else if (pid == 3) {
            // Stripes
            bool horiz = rnd.next(0,1);
            int offset = rnd.next(0,1);
            if (horiz) {
                for (int i = 0; i < N; i++)
                    if ((i + offset) % 2 == 0)
                        for (int j = 0; j < E; j++)
                            g[i][j] = 'X';
            } else {
                for (int j = 0; j < E; j++)
                    if ((j + offset) % 2 == 0)
                        for (int i = 0; i < N; i++)
                            g[i][j] = 'X';
            }
        } else {
            // Checkerboard
            int offset = rnd.next(0,1);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < E; j++)
                    if ((i + j) % 2 == offset) g[i][j] = 'X';
        }
        printf("%d %d\n", N, E);
        for (int i = 0; i < N; i++)
            printf("%s\n", g[i].c_str());
    }
    printf("0 0\n");
    return 0;
}
