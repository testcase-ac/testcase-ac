#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(3);
    vector<int> values;

    if (mode == 0) {
        int x = rnd.next(2, 499);
        int y = rnd.next(2, 1000 - x);
        while (y == x) y = rnd.next(2, 1000 - x);
        values = {x, y, x + y};
    } else if (mode == 1) {
        int x = rnd.next(2, 31);
        int y = rnd.next(2, 1000 / x);
        while (y == x) y = rnd.next(2, 1000 / x);
        values = {x, y, x * y};
    } else {
        while (true) {
            values = {rnd.next(2, 1000), rnd.next(2, 1000), rnd.next(2, 1000)};
            sort(values.begin(), values.end());
            if (values[0] == values[1] || values[1] == values[2]) continue;
            if (values[0] + values[1] == values[2]) continue;
            if (values[0] * values[1] == values[2]) continue;
            break;
        }
    }

    shuffle(values.begin(), values.end());
    println(values);

    return 0;
}
