#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for variability
    int C = rnd.next(1, 15);        // number of stocks
    int D = rnd.next(2, 5);         // number of days
    int M = rnd.next(1, 1900);      // initial money, capped to keep final ≤500k
    int R = rnd.next(1, 4);         // max daily volatility factor

    println(C, D, M);
    for (int i = 0; i < C; i++) {
        vector<int> price(D);
        // starting price between 1 and 100
        price[0] = rnd.next(1, 100);
        for (int j = 1; j < D; j++) {
            int low = price[j-1] / R;
            if (low < 1) low = 1;
            int high = price[j-1] * R;
            if (high > 1000) high = 1000;
            price[j] = rnd.next(low, high);
        }
        println(price);
    }
    return 0;
}
