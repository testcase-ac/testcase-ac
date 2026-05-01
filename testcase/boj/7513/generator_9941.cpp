#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 3);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int m, n;
        vector<string> words;

        if (tc == 0) {
            // Simple, deterministic first test case
            m = 3;
            println(m);
            words = {"a", "bc", "def"};
            for (const string &w : words) println(w);

            n = 3;
            println(n);

            // participant 1: k=1, only first word
            {
                vector<int> seq = {1, 0};
                println(seq);
            }
            // participant 2: uses all words in order
            {
                vector<int> seq = {3, 0, 1, 2};
                println(seq);
            }
            // participant 3: repeated and reversed use
            {
                vector<int> seq = {4, 2, 2, 1, 0};
                println(seq);
            }
        } else {
            // Random but compact test cases
            m = rnd.next(1, 5);
            println(m);

            // Generate short, easy-to-read words
            for (int i = 0; i < m; ++i) {
                int len = rnd.next(1, 5);
                string s;
                bool uniform = rnd.next(0, 1); // 0 or 1
                if (uniform == 0) {
                    char c = char('a' + i % 3);
                    s.assign(len, c);
                } else {
                    for (int j = 0; j < len; ++j) {
                        char c = char('a' + rnd.next(0, 2)); // 'a'..'c'
                        s.push_back(c);
                    }
                }
                words.push_back(s);
                println(s);
            }

            n = rnd.next(1, 7);
            println(n);

            for (int p = 0; p < n; ++p) {
                int style = rnd.next(0, 4);
                int k;
                if (style == 0) k = 1;
                else if (style == 1) k = rnd.next(2, 3);
                else k = rnd.next(3, 6); // <= 10 by problem constraints

                vector<int> seq;
                seq.reserve(k + 1);
                seq.push_back(k);

                for (int j = 0; j < k; ++j) {
                    int idx;
                    if (m == 1) {
                        idx = 0;
                    } else {
                        int choice = rnd.next(0, 4);
                        if (choice == 0) idx = 0;        // first word
                        else if (choice == 1) idx = m-1; // last word
                        else idx = rnd.next(0, m - 1);   // any
                    }
                    seq.push_back(idx);
                }
                println(seq);
            }
        }
    }

    return 0;
}
