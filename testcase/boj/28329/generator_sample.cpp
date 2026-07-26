#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int alphabet = rnd.any(vector<int>{2, 3, 5, 26});
    string s(n, 'a');
    for (char& c : s)
        c += rnd.next(alphabet);

    println(s);
    int q = rnd.next(0, 20);
    println(q);
    for (int query = 0; query < q; ++query) {
        int i = rnd.next(0, n - 1);
        char c;
        do {
            c = static_cast<char>('a' + rnd.next(alphabet));
        } while (c == s[i]);
        s[i] = c;
        println(i + 1, c);
    }
}
