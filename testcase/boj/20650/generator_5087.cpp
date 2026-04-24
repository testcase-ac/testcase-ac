#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Base value A
    int A = rnd.next(1, 10);
    // Choose relationship type for diversity:
    // 0: all distinct, 1: A=B<C, 2: A<B=C, 3: A=B=C
    int type = rnd.next(0, 3);
    int delta1, delta2;
    if (type == 0) {
        delta1 = rnd.next(1, 5);
        delta2 = rnd.next(1, 5);
    } else if (type == 1) {
        delta1 = 0;
        delta2 = rnd.next(1, 5);
    } else if (type == 2) {
        delta1 = rnd.next(1, 5);
        delta2 = 0;
    } else {
        delta1 = delta2 = 0;
    }

    int B = A + delta1;
    int C = B + delta2;

    vector<long long> v = {A, B, C, A + B, B + C, C + A, A + B + C};
    shuffle(v.begin(), v.end());
    println(v);

    return 0;
}
