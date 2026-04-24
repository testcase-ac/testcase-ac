#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // length of the string
    int N = rnd.next(3, 10);
    // choose pattern type
    int type = rnd.next(0, 4);
    string s;

    if (type == 0) {
        // fully random
        for (int i = 0; i < N; i++)
            s += char(rnd.next('a', 'z'));
    } else if (type == 1 || type == 2) {
        // sorted unique letters, ascending or descending
        vector<char> pool;
        for (char c = 'a'; c <= 'z'; c++)
            pool.push_back(c);
        shuffle(pool.begin(), pool.end());
        vector<char> pick(pool.begin(), pool.begin() + N);
        sort(pick.begin(), pick.end());
        if (type == 1)
            reverse(pick.begin(), pick.end());
        for (char c : pick)
            s += c;
    } else if (type == 3) {
        // small alphabet with repeats
        int k = rnd.next(1, min(5, N));
        set<char> st;
        while ((int)st.size() < k)
            st.insert(char(rnd.next('a', 'z')));
        vector<char> chars(st.begin(), st.end());
        for (int i = 0; i < N; i++)
            s += rnd.any(chars);
    } else {
        // build from three reversed segments
        int p1 = rnd.next(1, N - 2);
        int p2 = rnd.next(p1 + 1, N - 1);
        vector<string> segs(3);
        for (int seg = 0; seg < 3; seg++) {
            int len = (seg == 0 ? p1 : (seg == 1 ? p2 - p1 : N - p2));
            string t;
            for (int i = 0; i < len; i++)
                t += char(rnd.next('a', 'z'));
            reverse(t.begin(), t.end());
            segs[seg] = t;
        }
        s = segs[0] + segs[1] + segs[2];
    }

    printf("%s\n", s.c_str());
    return 0;
}
