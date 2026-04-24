#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 8);
    println(T);
    vector<string> types = {"random", "same", "alt", "block", "full"};
    for (int tc = 0; tc < T; ++tc) {
        string t1 = rnd.any(types);
        string t2 = rnd.any(types);
        int n1 = rnd.next(1, 10);
        int n2 = rnd.next(1, 10);
        auto gen = [&](const string &t, int n) {
            if (t == "random") {
                int k = rnd.next(1, min(5, n));
                vector<char> pool;
                for (char c = 'A'; c <= 'Z'; ++c) pool.push_back(c);
                shuffle(pool.begin(), pool.end());
                pool.resize(k);
                string s;
                for (int i = 0; i < n; ++i)
                    s += rnd.any(pool);
                return s;
            } else if (t == "same") {
                char c = 'A' + rnd.next(0, 25);
                return string(n, c);
            } else if (t == "alt") {
                char c1 = 'A' + rnd.next(0, 25), c2;
                do { c2 = 'A' + rnd.next(0, 25); } while (c2 == c1);
                string s;
                for (int i = 0; i < n; ++i)
                    s += (i % 2 ? c1 : c2);
                return s;
            } else if (t == "block") {
                string s;
                int k = rnd.next(1, min(n, 4));
                for (int b = 0; b < k; ++b) {
                    char c = 'A' + rnd.next(0, 25);
                    int remBlocks = k - b - 1;
                    int remChars = n - (int)s.size();
                    int len = (b == k - 1 ? remChars : rnd.next(1, remChars - remBlocks));
                    s += string(len, c);
                }
                return s;
            } else { // full
                string s;
                for (int i = 0; i < n; ++i)
                    s += char('A' + (i % 26));
                return s;
            }
        };
        string s1 = gen(t1, n1);
        string s2 = gen(t2, n2);
        println(s1);
        println(s2);
    }
    return 0;
}
