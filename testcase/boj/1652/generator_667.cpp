#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    println(N);
    double prob = rnd.next();
    for (int i = 0; i < N; i++) {
        string s;
        for (int j = 0; j < N; j++) {
            if (prob < rnd.next()) {
                s += '.';
            } else {
                s += 'X';
            }
        }
        println(s);
    }
}
