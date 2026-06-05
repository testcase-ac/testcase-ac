#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 6);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int N;
        if (mode <= 1) {
            N = rnd.next(3, 8);
        } else if (mode == 5) {
            N = rnd.next(20, 45);
        } else {
            N = rnd.next(6, 18);
        }

        vector<int> group(N);
        for (int i = 0; i < N; ++i) {
            group[i] = rnd.next(0, 1);
        }

        int fixedColor = rnd.next(0, 1);
        int biasVertex = rnd.next(0, N - 1);
        int biasColor = rnd.next(0, 1);
        int threshold = rnd.next(15, 85);

        println(N);
        for (int i = 0; i < N - 1; ++i) {
            vector<int> row;
            for (int j = i + 1; j < N; ++j) {
                int color;
                if (mode == 0) {
                    color = fixedColor;
                } else if (mode == 1) {
                    color = (i + j + fixedColor) % 2;
                } else if (mode == 2) {
                    color = (group[i] == group[j]) ? fixedColor : 1 - fixedColor;
                } else if (mode == 3) {
                    color = rnd.next(0, 99) < threshold ? 1 : 0;
                } else if (mode == 4) {
                    color = (i == biasVertex || j == biasVertex) ? biasColor : rnd.next(0, 1);
                } else {
                    color = (rnd.next(0, 99) < 10 || rnd.next(0, 99) >= 90) ? rnd.next(0, 1) : fixedColor;
                }
                row.push_back(color);
            }
            println(row);
        }
    }

    return 0;
}
