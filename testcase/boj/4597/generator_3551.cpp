#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 10);
    double zeroBias = rnd.next(0.0, 1.0);
    for (int tc = 0; tc < T; ++tc) {
        int t_param = rnd.next(-1, 1);
        int m = rnd.wnext(30, t_param) + 1;  // missing bits length in [1,30]
        string s;
        s.reserve(m + 1);
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            char c = (rnd.next() < zeroBias ? '0' : '1');
            s.push_back(c);
            if (c == '1') sum++;
        }
        int last = rnd.next(0, 1);
        sum += last;
        char label = (sum % 2 ? 'o' : 'e');
        println(s + label);
    }
    println("#");
    return 0;
}
