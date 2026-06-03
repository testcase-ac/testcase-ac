#include "testlib.h"
#include <cstdio>
#include <vector>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int base = 0xAC00;
    const int initialCount = 19;
    const int medialCount = 21;
    const int finalCount = 28;

    int offset;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        offset = rnd.any(std::vector<int>{0, 1, finalCount - 1, initialCount * medialCount * finalCount - 2,
                                          initialCount * medialCount * finalCount - 1});
    } else if (mode == 1) {
        int initial = rnd.any(std::vector<int>{0, 1, initialCount - 2, initialCount - 1});
        int medial = rnd.next(0, medialCount - 1);
        int final = rnd.next(0, finalCount - 1);
        offset = (initial * medialCount + medial) * finalCount + final;
    } else if (mode == 2) {
        int initial = rnd.next(0, initialCount - 1);
        int medial = rnd.any(std::vector<int>{0, 1, medialCount - 2, medialCount - 1});
        int final = rnd.next(0, finalCount - 1);
        offset = (initial * medialCount + medial) * finalCount + final;
    } else if (mode == 3) {
        int initial = rnd.next(0, initialCount - 1);
        int medial = rnd.next(0, medialCount - 1);
        int final = rnd.any(std::vector<int>{0, 1, finalCount - 2, finalCount - 1});
        offset = (initial * medialCount + medial) * finalCount + final;
    } else {
        offset = rnd.next(0, initialCount * medialCount * finalCount - 1);
    }

    int codepoint = base + offset;
    std::printf("%c%c%c\n",
                0xE0 | (codepoint >> 12),
                0x80 | ((codepoint >> 6) & 0x3F),
                0x80 | (codepoint & 0x3F));

    return 0;
}
