#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: total commands
    int N = rnd.next(1, 20);

    // Hyper-parameters: weights for choosing each command
    int w_open  = rnd.next(1, 5);
    int w_close = rnd.next(1, 5);
    int w_del   = rnd.next(1, 5);

    string current;
    vector<char> cmds;
    cmds.reserve(N);

    for (int i = 0; i < N; i++) {
        // disable delete if empty
        int w_del_eff = current.empty() ? 0 : w_del;
        int total_w = w_open + w_close + w_del_eff;
        int x = rnd.next(1, total_w);

        char c;
        if (x <= w_open) {
            c = '(';
            current.push_back(c);
        } else if (x <= w_open + w_close) {
            c = ')';
            current.push_back(c);
        } else {
            c = '-';
            current.pop_back();
        }
        cmds.push_back(c);
    }

    // Output the command sequence
    string out(cmds.begin(), cmds.end());
    printf("%s\n", out.c_str());

    return 0;
}
