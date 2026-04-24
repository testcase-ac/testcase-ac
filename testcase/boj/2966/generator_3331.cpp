#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small test size
    int N = rnd.next(1, 15);

    // Choose generation scenario for diversity
    int scenario = rnd.next(0, 3);
    string ans;
    if (scenario == 0) {
        // Uniform random answers
        for (int i = 0; i < N; i++)
            ans += rnd.any(string("ABC"));
    } else if (scenario == 1) {
        // Biased towards one favorite answer
        char fav = rnd.any(string("ABC"));
        string other;
        for (char c : string("ABC"))
            if (c != fav) other += c;
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.6)
                ans += fav;
            else
                ans += rnd.any(other);
        }
    } else if (scenario == 2) {
        // Repeating pattern ABC
        string pattern = "ABC";
        for (int i = 0; i < N; i++)
            ans += pattern[i % 3];
    } else {
        // Block pattern AAA...BBB...CCC...
        if (N < 3) {
            for (int i = 0; i < N; i++)
                ans += rnd.any(string("ABC"));
        } else {
            int b1 = rnd.next(1, N - 2);
            int b2 = rnd.next(1, N - b1 - 1);
            int b3 = N - b1 - b2;
            ans += string(b1, 'A');
            ans += string(b2, 'B');
            ans += string(b3, 'C');
        }
    }

    // Output the generated test case
    println(N);
    println(ans);

    return 0;
}
