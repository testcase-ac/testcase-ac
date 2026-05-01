#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with varied bias: low, uniform, or high
    int t = rnd.next(-1, 1);
    int N = rnd.wnext(30, t) + 1;
    println(N);
    for (int i = 0; i < N; i++) {
        // Number of words in option: 1 to 5, with bias
        int t2 = rnd.next(-1, 1);
        int W = rnd.wnext(5, t2) + 1;
        vector<string> words;
        words.reserve(W);
        for (int j = 0; j < W; j++) {
            // Word length: 1 to 10, with bias
            int t3 = rnd.next(-1, 1);
            int len = rnd.wnext(10, t3) + 1;
            string s;
            s.reserve(len);
            for (int k = 0; k < len; k++) {
                char c = char('a' + rnd.next(0, 25));
                // Randomly uppercase some letters
                if (rnd.next(0, 3) == 0) c = char(toupper(c));
                s.push_back(c);
            }
            words.push_back(s);
        }
        // Print the option line
        for (int j = 0; j < (int)words.size(); j++) {
            if (j) printf(" ");
            printf("%s", words[j].c_str());
        }
        printf("\n");
    }
    return 0;
}
