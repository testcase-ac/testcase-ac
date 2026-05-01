#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mode = rnd.next(0, 5);
    string s;
    switch (mode) {
        case 0: {
            int N = rnd.next(1, 5);
            for (int i = 0; i < N; i++)
                s.push_back(char('A' + rnd.next(0, 25)));
            break;
        }
        case 1: {
            int N = rnd.next(6, 15);
            for (int i = 0; i < N; i++)
                s.push_back(char('A' + rnd.next(0, 25)));
            break;
        }
        case 2: {
            int N = rnd.next(6, 15);
            int k = rnd.next(2, 4);
            string alph;
            for (int i = 0; i < k; i++)
                alph.push_back('A' + i);
            for (int i = 0; i < N; i++)
                s.push_back(rnd.any(alph));
            break;
        }
        case 3: {
            int N = rnd.next(5, 20);
            int start = rnd.next(0, 26 - N);
            vector<char> letters;
            for (int i = 0; i < N; i++)
                letters.push_back('A' + start + i);
            for (int i = N - 1; i >= 0; i--)
                s.push_back(letters[i]);
            break;
        }
        case 4: {
            int N = rnd.next(5, 20);
            int start = rnd.next(0, 26 - N);
            for (int i = 0; i < N; i++)
                s.push_back('A' + start + i);
            break;
        }
        case 5: {
            int N = rnd.next(1, 10);
            char c = 'A' + rnd.next(0, 25);
            s = string(N, c);
            break;
        }
    }
    println(s);
    return 0;
}
