#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 12);
    int B = rnd.next(1, 30);
    int C = rnd.next(1, 30);
    int D = rnd.next(0, C - 1);
    int A = rnd.next(0, 3290);
    int E = rnd.next(0, 200);
    int F = rnd.next(0, 20);
    println(N, A, B, C, D, E, F);

    for (int i = 0; i < N; i++) {
        int L;
        int typeL = rnd.next(0, 2);
        if (typeL == 0) L = 0;
        else if (typeL == 1) L = rnd.next(1, 50);
        else L = rnd.next(51, 1000);

        int smallH = B < 5 ? B : 5;
        if (smallH < 1) smallH = 1;
        int mid_min = smallH + 1;
        int mid_max = B < 15 ? B : 15;
        if (mid_max < mid_min) mid_max = mid_min;
        int big_min = B + 1;
        int big_max = B + 10;
        if (big_max > 1000) big_max = 1000;
        if (big_max < big_min) big_max = big_min;
        int H;
        int typeH = rnd.next(0, 2);
        if (typeH == 0) H = rnd.next(1, smallH);
        else if (typeH == 1) H = rnd.next(mid_min, mid_max);
        else H = rnd.next(big_min, big_max);

        int smallM = C < 5 ? C : 5;
        if (smallM < 1) smallM = 1;
        int midm_min = smallM + 1;
        int midm_max = C < 15 ? C : 15;
        if (midm_max < midm_min) midm_max = midm_min;
        int bigm_min = C + 1;
        int bigm_max = C + 10;
        if (bigm_max > 1000) bigm_max = 1000;
        if (bigm_max < bigm_min) bigm_max = bigm_min;
        int M_;
        int typeM = rnd.next(0, 2);
        if (typeM == 0) M_ = rnd.next(1, smallM);
        else if (typeM == 1) M_ = rnd.next(midm_min, midm_max);
        else M_ = rnd.next(bigm_min, bigm_max);

        println(L, H, M_);
    }

    return 0;
}
