#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of slots N
    int N = rnd.next(6, 50);

    // Hyper-parameters for preliminary contest sizes
    vector<int> pth = {50, 100, 200, 500};
    int p_t_hi = rnd.any(pth);
    int p_t_lo = rnd.next(0, p_t_hi / 2);

    // Hyper-parameters for regional contest sizes
    vector<int> rth = {20, 50, 100};
    int r_t_hi = rnd.any(rth);
    int r_t_lo = rnd.next(0, r_t_hi / 2);

    // Upper bound on foreign teams
    int f_max = rnd.next(0, min(r_t_hi, 10));

    // Region names
    vector<string> names = {
        "Vietnam", "Indonesia", "Philippines",
        "Korea", "Taiwan", "Japan"
    };
    shuffle(names.begin(), names.end());

    // Containers for the data
    vector<int> p_t(6), p_u(6), r_t(6), r_u(6), f(6), scoreNum(6);

    // Generate until all site score numerators are distinct
    do {
        for (int i = 0; i < 6; i++) {
            // Preliminary teams and universities
            p_t[i] = rnd.next(p_t_lo, p_t_hi);
            p_u[i] = rnd.next(0, p_t[i]);

            // Regional teams and universities
            r_t[i] = rnd.next(r_t_lo, r_t_hi);
            r_u[i] = rnd.next(0, r_t[i]);

            // Foreign teams
            f[i] = rnd.next(0, min(f_max, r_t[i]));

            // Compute numerator of site score:
            // score = (28*r_u +12*r_t +7*p_u +3*p_t +15*f) / 50
            scoreNum[i] = 28*r_u[i] + 12*r_t[i] + 7*p_u[i] + 3*p_t[i] + 15*f[i];
        }
        // Check if all scoreNum are distinct
        set<int> S(scoreNum.begin(), scoreNum.end());
        if ((int)S.size() == 6) break;
    } while (true);

    // Output
    println(N);
    for (int i = 0; i < 6; i++) {
        println(names[i], p_t[i], p_u[i], r_t[i], r_u[i], f[i]);
    }

    return 0;
}
