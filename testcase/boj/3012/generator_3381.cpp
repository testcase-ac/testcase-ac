#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small length
    int N = rnd.next(2, 10);
    // Decide to build a valid base (only if even length), else random
    bool makeValid = (N % 2 == 0 && rnd.next(0, 1) == 0);
    string s(N, ' ');
    if (makeValid) {
        // Generate a random valid bracket sequence of length N
        int K = N / 2, openUsed = 0;
        vector<char> stk;
        for (int i = 0; i < N; i++) {
            if (openUsed < K && (stk.empty() || rnd.next() < 0.5)) {
                // push a random opening bracket
                char o = rnd.any(string("([{"));
                s[i] = o;
                stk.push_back(o);
                openUsed++;
            } else {
                // pop and close
                char o = stk.back(); stk.pop_back();
                char c = (o == '(' ? ')' : (o == '[' ? ']' : '}'));
                s[i] = c;
            }
        }
    } else {
        // Completely random bracket characters
        string all = "()[]{}";
        for (int i = 0; i < N; i++) {
            s[i] = rnd.any(all);
        }
    }
    // Introduce '?' with random probability
    double p = rnd.next();
    for (int i = 0; i < N; i++) {
        if (rnd.next() < p) s[i] = '?';
    }
    // Output
    println(N);
    println(s);
    return 0;
}
