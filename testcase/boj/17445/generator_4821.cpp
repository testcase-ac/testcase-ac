#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for magnitude of numbers
    vector<int> bounds = {5, 10, 50, 100};
    int bound = rnd.any(bounds);

    // Choose 1, 2, or 3 arguments
    int type = rnd.next(1, 3);

    if (type == 1) {
        // range(a)
        long long a = rnd.next(-bound, bound);
        printf("range(%lld)\n", a);
    }
    else if (type == 2) {
        // range(a,b)
        long long a = rnd.next(-bound, bound);
        long long b = rnd.next(-bound, bound);
        printf("range(%lld,%lld)\n", a, b);
    }
    else {
        // range(a,b,c), ensure c != 0
        long long a = rnd.next(-bound, bound);
        long long c = (rnd.next(0, 1) ? rnd.next(1, bound) : -rnd.next(1, bound));
        long long b = rnd.next(-bound, bound);
        printf("range(%lld,%lld,%lld)\n", a, b, c);
    }

    return 0;
}
