#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

bool isPossible(const string &S, string T) {
    while (T.size() > S.size()) {
        if (T.back() == 'A') {
            T.pop_back();
        } else {
            T.pop_back();
            reverse(T.begin(), T.end());
        }
    }
    return T == S;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    bool wantSolvable = rnd.next() < 0.5;
    string S, T;
    
    if (wantSolvable) {
        // Generate a solvable case by forward operations
        int lenS = rnd.next(1, 5);
        for (int i = 0; i < lenS; i++)
            S += rnd.any(string("AB"));
        
        int ops = rnd.next(1, 8);
        T = S;
        for (int i = 0; i < ops; i++) {
            if (rnd.next() < 0.5) {
                T.push_back('A');
            } else {
                reverse(T.begin(), T.end());
                T.push_back('B');
            }
        }
    } else {
        // Generate an unsolvable case by rejection sampling
        while (true) {
            int lenS = rnd.next(1, 5);
            S.clear();
            for (int i = 0; i < lenS; i++)
                S += rnd.any(string("AB"));
            
            int maxOps = rnd.next(1, 8);
            int lenT = rnd.next(lenS + 1, lenS + maxOps);
            T.clear();
            for (int i = 0; i < lenT; i++)
                T += rnd.any(string("AB"));
            
            if (!isPossible(S, T))
                break;
        }
    }
    
    println(S);
    println(T);
    return 0;
}
