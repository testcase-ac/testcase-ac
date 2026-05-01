#include "testlib.h"

using namespace std;
using i64 = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 30;
    vector<i64> A = rnd.distinct(N, i64(1e16)+1);
    int digit = rnd.next(0, 18);
    i64 p10 = 1;
    for (int i = 1; i < digit; i++) { p10 *= 10; }
    i64 D = digit == 0 ? 0 : rnd.next(p10, p10*10 - 1);

    println(N);
    println(A);
    println(D);

    return 0;
}
