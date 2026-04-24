#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int t = 0; t < T; t++) {
        int N = rnd.next(1, 10);
        println(N);
        int type = rnd.next(0, 4);
        vector<int> idx = {0, 1, 2};
        shuffle(idx.begin(), idx.end());
        vector<int> base(3), step(3);
        if (type == 4) {
            for (int c = 0; c < 3; c++) {
                base[c] = rnd.next(-10, 10);
                step[c] = rnd.next(-5, 5);
            }
        }

        for (int i = 0; i < N; i++) {
            int raw[3];
            for (int c = 0; c < 3; c++) {
                int v;
                switch (type) {
                    case 0:
                        v = rnd.next(-20, 20);
                        break;
                    case 1:
                        v = (rnd.next() < 0.7 ? rnd.next(0, 20) : rnd.next(-20, -1));
                        break;
                    case 2:
                        v = (rnd.next() < 0.7 ? rnd.next(-20, 0) : rnd.next(1, 20));
                        break;
                    case 3:
                        v = (rnd.next() < 0.5 ? 0 : rnd.next(-5, 5));
                        break;
                    case 4:
                        v = base[c] + step[c] * i + rnd.next(-3, 3);
                        break;
                    default:
                        v = 0;
                }
                raw[c] = v;
            }
            // occasional tie to add variety
            if (rnd.next() < 0.1) {
                int a = rnd.next(0, 2), b = rnd.next(0, 2);
                if (a != b) {
                    int m = max(raw[a], raw[b]);
                    raw[a] = raw[b] = m;
                }
            }
            println(raw[idx[0]], raw[idx[1]], raw[idx[2]]);
        }
    }

    return 0;
}
