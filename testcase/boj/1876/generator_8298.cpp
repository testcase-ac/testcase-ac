#include "testlib.h"
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 6);
    println(N);
    for (int i = 0; i < N; i++) {
        // Hyper-parameter for T: bias towards 16.0 or 18.0 or uniform
        int tT = rnd.next(-2, 2);
        int valT = rnd.wnext(201, tT); // 0..200
        double T = 16.0 + valT * (2.0 / 200.0);
        // Hyper-parameter for X: bias towards 10 or 80 or uniform
        int tX = rnd.next(-2, 2);
        int valX = rnd.wnext(71, tX); // 0..70
        int X = 10 + valX;
        printf("%.2f %d\n", T, X);
    }
    return 0;
}
