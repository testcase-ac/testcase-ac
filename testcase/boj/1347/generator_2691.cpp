#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate length between 1 and 49
    int N = rnd.next(1, 49);
    string s;
    s.reserve(N);
    bool hasF = false;
    // Build a random sequence with more forwards but some turns
    for (int i = 0; i < N; i++) {
        double r = rnd.next();
        if (r < 0.6) {
            s.push_back('F');
            hasF = true;
        } else {
            if (rnd.next() < 0.5)
                s.push_back('L');
            else
                s.push_back('R');
        }
    }
    // Ensure at least one 'F'
    if (!hasF) {
        int pos = rnd.next(0, N - 1);
        s[pos] = 'F';
    }
    // Output
    println(N);
    println(s);
    return 0;
}
