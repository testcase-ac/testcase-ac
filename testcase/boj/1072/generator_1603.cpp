#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> buk = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    int MX = rnd.any(buk);
    int X = rnd.next(1, MX);

    int mn = 0;
    if(rnd.next() < 0.2) {
        mn = (int)(X * 0.98);
    }
    int Y = rnd.next(mn, X);
    println(X, Y);
}
