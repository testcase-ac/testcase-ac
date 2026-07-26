#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> critical = {4, 5, 6, 34, 35, 36, 54, 55, 56, 59};
    int T = rnd.next(8, 20);
    println(T);

    for (int i = 0; i < T; ++i) {
        int N;
        switch (i % 4) {
            case 0:
                N = rnd.next(1, 100);
                break;
            case 1:
                N = 60 * rnd.next(0, 1000) + rnd.any(critical);
                break;
            case 2:
                N = rnd.next(1, 10000000);
                break;
            default:
                N = rnd.next(9999900, 10000000);
        }
        println(N);
    }
}
