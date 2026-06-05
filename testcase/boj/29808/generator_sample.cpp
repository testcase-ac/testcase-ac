#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxS = 2000000000;
    const int zip = 4763;
    const vector<int> koreanEnglishCoef = {508, 108};
    const vector<int> mathScienceCoef = {212, 305};

    int mode = rnd.next(0, 5);
    int s = 0;

    if (mode == 0) {
        vector<int> boundary = {0, 1, zip - 1, zip, maxS - 1, maxS};
        s = rnd.any(boundary);
    } else if (mode == 1) {
        s = rnd.next(0, maxS);
        if (s % zip == 0 && s < maxS) {
            ++s;
        } else if (s % zip == 0) {
            --s;
        }
    } else {
        int d1 = rnd.next(0, 200);
        int d2 = rnd.next(0, 200);

        if (mode == 3) {
            d1 = rnd.any(vector<int>{0, 1, 199, 200});
        } else if (mode == 4) {
            d2 = rnd.any(vector<int>{0, 1, 199, 200});
        } else if (mode == 5) {
            d1 = rnd.next(150, 200);
            d2 = rnd.next(150, 200);
        }

        int a = rnd.any(koreanEnglishCoef);
        int b = rnd.any(mathScienceCoef);
        s = (a * d1 + b * d2) * zip;
    }

    println(s);
    return 0;
}
