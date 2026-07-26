#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 10);
    int k = rnd.next(1, 8);
    int q = rnd.next(1, 4) == 1 ? 1000000000 : rnd.next(1, 20);
    vector<int> colors;
    for (int color = 1; color <= n; ++color)
        for (int j = 0; j < k; ++j)
            colors.push_back(color);

    int mode = rnd.next(0, 2);
    if (mode == 1)
        shuffle(colors.begin(), colors.end());
    else if (mode == 2)
        for (int& color : colors) color = color % n + 1;

    println(n, k, q);
    for (int i = 0; i < n; ++i)
        println(vector<int>(colors.begin() + i * k, colors.begin() + (i + 1) * k));
}
