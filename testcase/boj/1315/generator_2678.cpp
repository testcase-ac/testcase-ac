#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of quests
    int N = rnd.next(2, 10);
    println(N);

    // Ensure at least one trivial quest
    int p0 = rnd.next(1, 5);
    println(1, 1, p0);

    // Generate other quests with varied requirements
    for (int i = 2; i <= N; ++i) {
        // Type: S = strength-focused, I = intelligence-focused, B = both high
        char t = rnd.any(string("SIB"));
        int req_str, req_int;
        if (t == 'S') {
            req_str = rnd.wnext(20, 2) + 1;     // bias toward higher strength
            req_int = rnd.next(1, 20);
        } else if (t == 'I') {
            req_int = rnd.wnext(20, 2) + 1;     // bias toward higher intelligence
            req_str = rnd.next(1, 20);
        } else {
            req_str = rnd.next(10, 20);         // both moderately high
            req_int = rnd.next(10, 20);
        }
        int p = rnd.next(1, 5);                 // small reward
        println(req_str, req_int, p);
    }

    return 0;
}
