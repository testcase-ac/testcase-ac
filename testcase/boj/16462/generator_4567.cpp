#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students
    int N = rnd.next(1, 10);
    println(N);

    // Hyper-parameter to bias low/medium/high scores
    // t = 0 -> uniform, t > 0 -> skew high, t < 0 -> skew low
    int t = rnd.next(-3, 3);

    // Generate each (possibly skewed) score in [1,100]
    for (int i = 0; i < N; i++) {
        int q = rnd.wnext(100, t) + 1;  // rnd.wnext(100,t) in [0,99]
        println(q);
    }

    return 0;
}
