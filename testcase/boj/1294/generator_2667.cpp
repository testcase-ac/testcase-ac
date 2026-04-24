#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of words
    int N = rnd.next(2, 8);
    println(N);

    // Create a small common prefix to introduce tricky ordering
    int cp_len = rnd.next(0, 3);
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string common;
    for (int i = 0; i < cp_len; i++) {
        common += rnd.any(letters);
    }

    // Generate each word
    for (int i = 0; i < N; i++) {
        int L = rnd.next(1, 8);
        string s;
        // Half of the time, include a random prefix of the common string
        if (!common.empty() && rnd.next(0, 1) == 1) {
            int p = rnd.next(1, (int)common.size());
            s = common.substr(0, p);
        }
        // Fill the rest with random letters
        for (int j = (int)s.size(); j < L; j++) {
            s += rnd.any(letters);
        }
        println(s);
    }

    return 0;
}
