#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the string
    int N = rnd.next(1, 10);
    // Alphabet size for diversity
    int alph = rnd.next(1, min(5, N));

    // Choose a generation scenario
    int scenario = rnd.next(0, 2);
    string s;
    s.reserve(N);

    if (scenario == 0) {
        // Completely random string
        for (int i = 0; i < N; i++) {
            char c = char('a' + rnd.next(0, alph - 1));
            s.push_back(c);
        }
    }
    else if (scenario == 1) {
        // Periodic string with small pattern
        int p = rnd.next(1, min(3, N));
        vector<char> pat(p);
        for (int i = 0; i < p; i++)
            pat[i] = char('a' + rnd.next(0, alph - 1));
        for (int i = 0; i < N; i++)
            s.push_back(pat[i % p]);
    }
    else {
        // Runs of the same character
        while ((int)s.size() < N) {
            int rem = N - s.size();
            int run = rnd.next(1, rem);
            char c = char('a' + rnd.next(0, alph - 1));
            for (int i = 0; i < run; i++)
                s.push_back(c);
        }
    }

    // Output the generated string
    println(s);
    return 0;
}
