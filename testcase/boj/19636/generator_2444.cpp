/* generator code */
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Pre-diet parameters
    int W0 = rnd.next(1, 1000);    // initial weight in grams
    int I0 = rnd.next(1, 500);     // initial intake and basal metabolic in Kcal
    int T  = rnd.next(1, 500);     // threshold for metabolic change

    // Diet-period parameters
    int D  = rnd.next(1, 10);      // days of diet
    int A  = rnd.next(0, 500);     // activity metabolic per day in Kcal
    // Ensure no weight gain during diet:
    // daily consumption = I0 + A, so intake I <= I0 + A
    int maxI = I0 + A;
    int I = rnd.next(0, maxI);

    // Output
    println(W0, I0, T);
    println(D, I, A);
    return 0;
}
