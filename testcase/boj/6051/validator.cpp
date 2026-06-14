#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 80000, "N");
    inf.readEoln();

    vector<int> previous(n + 1, -1);
    vector<int> last(n + 1, -1);
    vector<int> size(n + 1, 0);

    previous[0] = -1;
    last[0] = -1;
    size[0] = 0;

    for (int i = 1; i <= n; ++i) {
        char c = inf.readChar();
        ensuref(c == 'a' || c == 's' || c == 't',
                "query %d has invalid command '%c'", i, c);

        if (c == 'a') {
            inf.readSpace();
            int k = inf.readInt(1, 1000000, "K");
            inf.readEoln();

            previous[i] = i - 1;
            last[i] = k;
            size[i] = size[i - 1] + 1;
        } else if (c == 's') {
            inf.readEoln();
            ensuref(size[i - 1] > 0, "query %d sells from an empty herd", i);

            int restored = previous[i - 1];
            previous[i] = previous[restored];
            last[i] = last[restored];
            size[i] = size[restored];
        } else {
            inf.readSpace();
            int k = inf.readInt(1, i, "K");
            inf.readEoln();

            int restored = k - 1;
            previous[i] = previous[restored];
            last[i] = last[restored];
            size[i] = size[restored];
        }
    }

    inf.readEof();
}
