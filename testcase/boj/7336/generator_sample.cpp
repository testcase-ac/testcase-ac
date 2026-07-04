#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Rectangle {
    int y1;
    int x1;
    int y2;
    int x2;
    int color;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 5);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        int height = rnd.next(1, 9);
        int width = rnd.next(1, 9);
        int targetCount = rnd.next(1, min(15, height * width));

        vector<Rectangle> rectangles = {{0, 0, height, width, 1}};

        while ((int)rectangles.size() < targetCount) {
            vector<int> splittable;
            for (int i = 0; i < (int)rectangles.size(); ++i) {
                int h = rectangles[i].y2 - rectangles[i].y1;
                int w = rectangles[i].x2 - rectangles[i].x1;
                if (h > 1 || w > 1) {
                    splittable.push_back(i);
                }
            }
            if (splittable.empty()) {
                break;
            }

            int index = rnd.any(splittable);
            Rectangle cur = rectangles[index];
            int h = cur.y2 - cur.y1;
            int w = cur.x2 - cur.x1;
            bool splitHorizontal;
            if (h == 1) {
                splitHorizontal = false;
            } else if (w == 1) {
                splitHorizontal = true;
            } else {
                splitHorizontal = rnd.next(0, 1) == 0;
            }

            rectangles.erase(rectangles.begin() + index);
            if (splitHorizontal) {
                int y = rnd.next(cur.y1 + 1, cur.y2 - 1);
                rectangles.push_back({cur.y1, cur.x1, y, cur.x2, 1});
                rectangles.push_back({y, cur.x1, cur.y2, cur.x2, 1});
            } else {
                int x = rnd.next(cur.x1 + 1, cur.x2 - 1);
                rectangles.push_back({cur.y1, cur.x1, cur.y2, x, 1});
                rectangles.push_back({cur.y1, x, cur.y2, cur.x2, 1});
            }
        }

        int paletteSize = rnd.next(1, min(20, max(1, (int)rectangles.size())));
        int pattern = rnd.next(0, 3);
        for (int i = 0; i < (int)rectangles.size(); ++i) {
            if (pattern == 0) {
                rectangles[i].color = rnd.next(1, paletteSize);
            } else if (pattern == 1) {
                rectangles[i].color = (rectangles[i].y1 + rectangles[i].x1) % paletteSize + 1;
            } else if (pattern == 2) {
                rectangles[i].color = i % paletteSize + 1;
            } else {
                rectangles[i].color = rnd.next(1, 20);
            }
        }

        shuffle(rectangles.begin(), rectangles.end());

        println((int)rectangles.size());
        for (const Rectangle& rect : rectangles) {
            println(rect.y1, rect.x1, rect.y2, rect.x2, rect.color);
        }
    }

    return 0;
}
