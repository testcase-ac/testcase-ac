#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

static string gradeToken(int value) {
    return to_string(value);
}

static int randomGradeForMode(int mode) {
    if (mode == 0) {
        return rnd.next(0, 9);
    }
    if (mode == 1) {
        return rnd.any(vector<int>{0, 1, 9, 10, 11, 19, 90, 99, 100});
    }
    if (mode == 2) {
        return rnd.any(vector<int>{0, 100});
    }
    if (mode == 3) {
        return rnd.next(90, 100);
    }
    return rnd.next(0, 100);
}

static pair<int, string> makeCase(int index, int totalCases) {
    int mode = index % 5;
    int g;

    if (index == totalCases - 1) {
        g = 25;
        mode = rnd.next(1, 4);
    } else if (mode == 0) {
        g = rnd.next(1, 6);
    } else if (mode == 1) {
        g = rnd.next(2, 10);
    } else if (mode == 2) {
        g = rnd.next(8, 18);
    } else {
        g = rnd.next(3, 15);
    }

    vector<int> grades;
    grades.reserve(g);
    for (int i = 0; i < g; ++i) {
        grades.push_back(randomGradeForMode(mode));
    }

    if (g >= 3 && rnd.next(2) == 0) {
        grades[0] = 100;
        grades[1] = 0;
        grades[2] = rnd.next(1, 9);
    }
    if (g >= 4 && rnd.next(3) == 0) {
        grades[g - 2] = rnd.next(10, 19);
        grades[g - 1] = rnd.next(90, 100);
    }

    string s;
    for (int grade : grades) {
        s += gradeToken(grade);
    }

    return {g, s};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(8, 18);
    println(c);

    for (int tc = 0; tc < c; ++tc) {
        auto generated = makeCase(tc, c);
        println(generated.first, generated.second);
    }

    return 0;
}
