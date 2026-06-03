#include "testlib.h"

#include <tuple>
#include <vector>

using namespace std;

using Student = tuple<int, int, int>;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Student> pool;
    int mode = rnd.next(0, 5);

    for (int grade = 1; grade <= 3; ++grade) {
        for (int classroom = 1; classroom <= 4; ++classroom) {
            for (int number = 1; number <= 20; ++number) {
                bool take = false;
                if (mode == 0) {
                    take = true;
                } else if (mode == 1) {
                    take = grade == 1;
                } else if (mode == 2) {
                    take = grade >= 2 && classroom <= 2;
                } else if (mode == 3) {
                    take = grade >= 2 && classroom >= 3;
                } else if (mode == 4) {
                    take = number == 1 || number == 20;
                } else {
                    take = rnd.next(0, 99) < 45;
                }

                if (take) {
                    pool.emplace_back(grade, classroom, number);
                }
            }
        }
    }

    shuffle(pool.begin(), pool.end());

    int maxP = min<int>(100, pool.size());
    int p;
    if (mode == 0) {
        p = rnd.next(60, maxP);
    } else if (mode == 1) {
        p = rnd.next(1, min(40, maxP));
    } else {
        p = rnd.next(1, maxP);
    }

    println(p);
    for (int i = 0; i < p; ++i) {
        int grade, classroom, number;
        tie(grade, classroom, number) = pool[i];
        println(grade, classroom, number);
    }

    return 0;
}
