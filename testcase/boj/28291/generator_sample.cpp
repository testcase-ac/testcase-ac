#include "testlib.h"

#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

struct Block {
    string type;
    int x;
    int y;
};

void addBlock(vector<Block>& blocks, set<pair<int, int>>& used, const string& type, int x, int y) {
    if (used.insert({x, y}).second) {
        blocks.push_back({type, x, y});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int w = 1;
    int h = 1;
    vector<Block> blocks;
    set<pair<int, int>> used;

    if (mode == 0) {
        w = rnd.next(1, 4);
        h = rnd.next(1, 4);
        addBlock(blocks, used, "redstone_lamp", rnd.next(0, w - 1), rnd.next(0, h - 1));
    } else if (mode == 1) {
        w = rnd.next(2, 6);
        h = rnd.next(1, 5);
        int y = rnd.next(0, h - 1);
        int x = rnd.next(0, w - 2);
        addBlock(blocks, used, "redstone_block", x, y);
        addBlock(blocks, used, "redstone_lamp", x + 1, y);
    } else if (mode == 2) {
        int len = rnd.next(2, 19);
        bool horizontal = rnd.next(2) == 0;
        w = horizontal ? len + 1 : rnd.next(1, 4);
        h = horizontal ? rnd.next(1, 4) : len + 1;
        int baseX = horizontal ? 0 : rnd.next(0, w - 1);
        int baseY = horizontal ? rnd.next(0, h - 1) : 0;
        for (int i = 0; i <= len; ++i) {
            int x = baseX + (horizontal ? i : 0);
            int y = baseY + (horizontal ? 0 : i);
            if (i == 0) {
                addBlock(blocks, used, "redstone_block", x, y);
            } else if (i == len) {
                addBlock(blocks, used, "redstone_lamp", x, y);
            } else {
                addBlock(blocks, used, "redstone_dust", x, y);
            }
        }
    } else if (mode == 3) {
        w = rnd.next(4, 10);
        h = rnd.next(4, 10);
        int cx = rnd.next(1, w - 2);
        int cy = rnd.next(1, h - 2);
        addBlock(blocks, used, "redstone_block", cx, cy);
        vector<pair<int, int>> arms = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        shuffle(arms.begin(), arms.end());
        int armCount = rnd.next(2, 4);
        for (int i = 0; i < armCount; ++i) {
            auto [dx, dy] = arms[i];
            int maxLen = dx == 0 ? (dy > 0 ? h - 1 - cy : cy) : (dx > 0 ? w - 1 - cx : cx);
            int len = rnd.next(1, maxLen);
            for (int step = 1; step <= len; ++step) {
                string type = step == len ? "redstone_lamp" : "redstone_dust";
                addBlock(blocks, used, type, cx + dx * step, cy + dy * step);
            }
        }
    } else if (mode == 4) {
        w = rnd.next(5, 12);
        h = rnd.next(5, 12);
        int count = rnd.next(5, 18);
        vector<tuple<int, int, string>> cells;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                cells.push_back({x, y, "redstone_dust"});
            }
        }
        shuffle(cells.begin(), cells.end());
        int lamps = rnd.next(1, min(4, count));
        int sources = rnd.next(0, min(3, count - lamps));
        for (int i = 0; i < count; ++i) {
            auto [x, y, type] = cells[i];
            if (i < lamps) {
                type = "redstone_lamp";
            } else if (i < lamps + sources) {
                type = "redstone_block";
            }
            addBlock(blocks, used, type, x, y);
        }
    } else {
        w = rnd.next(1, 50);
        h = rnd.next(1, 50);
        int count = rnd.next(1, min(25, w * h));
        vector<pair<int, int>> cells;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                cells.push_back({x, y});
            }
        }
        shuffle(cells.begin(), cells.end());
        int lampPos = rnd.next(count);
        for (int i = 0; i < count; ++i) {
            auto [x, y] = cells[i];
            string type;
            if (i == lampPos) {
                type = "redstone_lamp";
            } else {
                int pick = rnd.next(10);
                type = pick < 2 ? "redstone_block" : "redstone_dust";
            }
            addBlock(blocks, used, type, x, y);
        }
    }

    shuffle(blocks.begin(), blocks.end());

    println(w, h);
    println(static_cast<int>(blocks.size()));
    for (const Block& block : blocks) {
        println(block.type, block.x, block.y);
    }

    return 0;
}
