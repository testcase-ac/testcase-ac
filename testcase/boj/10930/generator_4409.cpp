#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter to skew length distribution:
    // tLen > 0 favors larger lengths, tLen < 0 favors smaller lengths
    int tLen = rnd.next(-1, 1);
    // rnd.wnext(50, tLen) gives [0,49], so +1 -> [1,50]
    int n = rnd.wnext(50, tLen) + 1;

    // Hyper-parameters: relative weight for digits, lowercase, uppercase
    int wD = rnd.next(1, 5);
    int wL = rnd.next(1, 5);
    int wU = rnd.next(1, 5);

    vector<char> categories;
    for (int i = 0; i < wD; ++i) categories.push_back('d');
    for (int i = 0; i < wL; ++i) categories.push_back('l');
    for (int i = 0; i < wU; ++i) categories.push_back('u');

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        char type = rnd.any(categories);
        if (type == 'd') {
            s.push_back(char('0' + rnd.next(0, 9)));
        } else if (type == 'l') {
            s.push_back(char('a' + rnd.next(0, 25)));
        } else {
            s.push_back(char('A' + rnd.next(0, 25)));
        }
    }

    // Output the single test case: the string S
    println(s);
    return 0;
}
