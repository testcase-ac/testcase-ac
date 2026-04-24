#include "testlib.h"
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small size
    int N = rnd.next(1, 10);
    // Choose alphabet size from 'a'
    int alph = rnd.next(1, 5);
    string letters;
    for (int i = 0; i < alph; i++) letters.push_back(char('a' + i));
    string s(N, 'a');
    // Hyper-parameters for diversity
    double p = rnd.next();
    if (p < 0.2) {
        // Full palindrome
        for (int j = 0; j < N; j++) {
            char c = rnd.any(letters);
            s[j] = s[N - 1 - j] = c;
        }
    } else if (p < 0.4) {
        // All same letter
        char c = rnd.any(letters);
        for (int i = 0; i < N; i++) s[i] = c;
    } else if (p < 0.7) {
        // Palindromic suffix of random length
        int len = rnd.next(1, N);
        // Fill prefix
        for (int i = 0; i < N - len; i++) {
            s[i] = rnd.any(letters);
        }
        // Fill suffix as palindrome
        for (int j = 0; j < len; j++) {
            char c = rnd.any(letters);
            s[N - len + j] = s[N - 1 - j] = c;
        }
    } else {
        // Completely random string
        for (int i = 0; i < N; i++) s[i] = rnd.any(letters);
    }
    // Output
    println(N);
    printf("%s\n", s.c_str());
    return 0;
}
