#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int roomCount = inf.readInt(1, 200, "F");
    inf.readSpace();
    int passageCount = inf.readInt(1, 1500, "P");
    inf.readEoln();

    for (int i = 0; i < roomCount; ++i) {
        inf.readInt(0, 1000, "current_students");
        inf.readSpace();
        inf.readInt(0, 1000, "sleep_capacity");
        inf.readEoln();
    }

    for (int i = 0; i < passageCount; ++i) {
        inf.readInt(1, roomCount, "room_a");
        inf.readSpace();
        inf.readInt(1, roomCount, "room_b");
        inf.readSpace();
        inf.readInt(0, 1000000000, "travel_time");
        inf.readEoln();
    }

    inf.readEof();
}
