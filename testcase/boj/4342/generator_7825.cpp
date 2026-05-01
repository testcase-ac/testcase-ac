#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX32 = 2147483647;
    const int LIM_SMALL = 10;
    const int LIM_MED = 1000000;
    const int LIM_B = 1000;

    int T = rnd.next(3, 8);
    vector<int> types = {0,1,2,3,4,5};
    for (int i = 0; i < T; i++) {
        int tp = rnd.any(types);
        long long a = 0, b = 0;
        switch (tp) {
            case 0:
                a = rnd.next(1, LIM_MED);
                b = rnd.next(1, LIM_MED);
                break;
            case 1:
                a = rnd.next(1, LIM_SMALL);
                b = rnd.next(1, LIM_SMALL);
                break;
            case 2:
                a = rnd.next(1, LIM_MED);
                b = a;
                break;
            case 3: {
                b = rnd.next(1, LIM_B);
                int kmax = LIM_MED / b;
                if (kmax < 2) kmax = 2;
                int k = rnd.next(2, kmax);
                a = b * 1LL * k;
                break;
            }
            case 4:
                a = rnd.next(1, LIM_MED - 1);
                b = rnd.next((int)a + 1, LIM_MED);
                break;
            case 5:
                a = rnd.next(MAX32 - 1000, MAX32);
                b = rnd.next(MAX32 - 1000, MAX32);
                break;
        }
        println(a, b);
    }
    println(0, 0);

    return 0;
}
