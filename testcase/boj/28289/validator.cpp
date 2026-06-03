#include "testlib.h"

#include <set>
#include <tuple>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 100, "P");
    inf.readEoln();

    set<tuple<int, int, int>> students;
    for (int i = 0; i < p; ++i) {
        int grade = inf.readInt(1, 3, "G_P");
        inf.readSpace();
        int classroom = inf.readInt(1, 4, "C_P");
        inf.readSpace();
        int number = inf.readInt(1, 20, "N_P");
        inf.readEoln();

        ensuref(students.emplace(grade, classroom, number).second,
                "duplicate student tuple at index %d: (%d, %d, %d)",
                i + 1,
                grade,
                classroom,
                number);
    }

    inf.readEof();
}
