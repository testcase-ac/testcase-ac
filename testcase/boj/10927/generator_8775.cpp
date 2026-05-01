#include "testlib.h"
using namespace std;

char randomAlphaNum() {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    return alphabet[rnd.next(0, (int)alphabet.size() - 1)];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s;
    int pattern = rnd.next(0, 9);

    switch (pattern) {
        case 0: {
            // Single character
            s.push_back(randomAlphaNum());
            break;
        }
        case 1: {
            // Maximum length random
            int len = 50;
            s.reserve(len);
            for (int i = 0; i < len; ++i) s.push_back(randomAlphaNum());
            break;
        }
        case 2: {
            // Short random string
            int len = rnd.next(2, 10);
            s.reserve(len);
            for (int i = 0; i < len; ++i) s.push_back(randomAlphaNum());
            break;
        }
        case 3: {
            // Medium random string
            int len = rnd.next(11, 30);
            s.reserve(len);
            for (int i = 0; i < len; ++i) s.push_back(randomAlphaNum());
            break;
        }
        case 4: {
            // Longer random string
            int len = rnd.next(31, 50);
            s.reserve(len);
            for (int i = 0; i < len; ++i) s.push_back(randomAlphaNum());
            break;
        }
        case 5: {
            // Repeated single character
            int len = rnd.next(3, 50);
            char c = randomAlphaNum();
            s.assign(len, c);
            break;
        }
        case 6: {
            // Alternating two distinct characters
            int len = rnd.next(2, 50);
            char a = randomAlphaNum();
            char b;
            do {
                b = randomAlphaNum();
            } while (b == a);
            s.reserve(len);
            for (int i = 0; i < len; ++i)
                s.push_back((i % 2 == 0) ? a : b);
            break;
        }
        case 7: {
            // Digits only
            int len = rnd.next(1, 50);
            s.reserve(len);
            for (int i = 0; i < len; ++i)
                s.push_back(char('0' + rnd.next(0, 9)));
            break;
        }
        case 8: {
            // Mixed case bias: mostly lowercase with some uppercase and digits
            int len = rnd.next(5, 50);
            s.reserve(len);
            for (int i = 0; i < len; ++i) {
                int t = rnd.next(0, 9);
                if (t <= 5)       s.push_back(char('a' + rnd.next(0, 25)));
                else if (t <= 7)  s.push_back(char('A' + rnd.next(0, 25)));
                else              s.push_back(char('0' + rnd.next(0, 9)));
            }
            break;
        }
        case 9: {
            // Hand-crafted interesting strings
            vector<string> samples = {
                "Baekjoon",        // example from statement
                "a",
                "0",
                "ABC",
                "abc",
                "ABCabc123",
                "zzzzzz",
                "Z9",
                "AaAaAa",
                "Md5TestString",
                "EdgeCASE12345"
            };
            s = rnd.any(samples);
            break;
        }
    }

    println(s);
    return 0;
}
