#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<char> cons = {'q','w','e','r','t','a','s','d','f','g','z','x','c','v'};
    vector<char> vows = {'y','u','i','o','p','h','j','k','l','n','m','b'};
    char sL = rnd.any(cons);
    char sR = rnd.any(vows);
    double p = rnd.next(0.0, 1.0);
    int L;
    if (p < 0.2) L = rnd.next(1, 3);
    else if (p < 0.6) L = rnd.next(4, 10);
    else if (p < 0.9) L = rnd.next(11, 20);
    else L = rnd.next(21, 30);
    string s;
    int pat = rnd.next(0, 4);
    if (pat == 0) {
        vector<char> all = cons;
        all.insert(all.end(), vows.begin(), vows.end());
        for (int i = 0; i < L; i++) s.push_back(rnd.any(all));
    } else if (pat == 1) {
        for (int i = 0; i < L; i++) s.push_back(rnd.any(cons));
    } else if (pat == 2) {
        for (int i = 0; i < L; i++) s.push_back(rnd.any(vows));
    } else if (pat == 3) {
        for (int i = 0; i < L; i++) {
            if (i % 2 == 0) s.push_back(rnd.any(cons));
            else s.push_back(rnd.any(vows));
        }
    } else {
        int k = rnd.next(1, min(3, L));
        string sub;
        vector<char> all = cons;
        all.insert(all.end(), vows.begin(), vows.end());
        for (int i = 0; i < k; i++) sub.push_back(rnd.any(all));
        while ((int)s.size() < L) s += sub;
        s.resize(L);
    }
    printf("%c %c\n", sL, sR);
    printf("%s\n", s.c_str());
    return 0;
}
