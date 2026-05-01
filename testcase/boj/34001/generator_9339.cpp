#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Zone {
    int quest;
    int r1;
    int r2;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Define Arcane River zones
    vector<Zone> arc = {
        {200, 210, 220}, // 소멸의 여로
        {210, 220, 225}, // 츄츄 아일랜드
        {220, 225, 230}, // 꿈의 도시 레헬른
        {225, 230, 235}, // 신비의 숲 아르카나
        {230, 235, 245}, // 기억의 늪 모라스
        {235, 245, 250}  // 태초의 바다 에스페라
    };

    // Define Grandis zones
    vector<Zone> grand = {
        {260, 265, 270}, // 세르니움
        {265, 270, 275}, // 호텔 아르크스
        {270, 275, 280}, // 오디움
        {275, 280, 285}, // 도원경
        {280, 285, 290}, // 아르테리아
        {285, 290, 295}, // 카르시온
        {290, 295, 300}  // 탈라하트
    };

    // Collect interesting/special levels
    vector<int> special;
    auto add_level = [&](int x) {
        if (x < 200 || x > 300) return;
        special.push_back(x);
    };

    // Add quest and reduction levels and their neighbors
    auto collect = [&](const vector<Zone>& zs) {
        for (const auto& z : zs) {
            for (int d = -1; d <= 1; ++d) {
                add_level(z.quest + d);
                add_level(z.r1 + d);
                add_level(z.r2 + d);
            }
        }
    };
    collect(arc);
    collect(grand);

    // Always include bounds and a few middle levels
    add_level(200);
    add_level(210);
    add_level(220);
    add_level(250);
    add_level(260);
    add_level(280);
    add_level(300);

    sort(special.begin(), special.end());
    special.erase(unique(special.begin(), special.end()), special.end());

    int L = 200;

    int patternType = rnd.next(0, 2);
    if (patternType == 0) {
        // Fully random between bounds
        L = rnd.next(200, 300);
    } else if (patternType == 1) {
        // Choose from curated special levels
        L = rnd.any(special);
    } else {
        // Focus around a specific zone and its reduction thresholds
        bool useArc = rnd.next(0, 1) == 0;
        if (useArc) {
            Zone z = rnd.any(arc);
            int kind = rnd.next(0, 5);
            if (kind == 0) {
                // Just below or at quest level
                L = max(200, z.quest - 1);
            } else if (kind == 1) {
                // Exactly quest level
                L = z.quest;
            } else if (kind == 2) {
                // Between quest and first reduction
                if (z.r1 - z.quest > 1)
                    L = rnd.next(z.quest + 1, z.r1 - 1);
                else
                    L = z.quest;
            } else if (kind == 3) {
                // Exactly first reduction level
                L = z.r1;
            } else if (kind == 4) {
                // Between first and second reduction
                if (z.r2 - z.r1 > 1)
                    L = rnd.next(z.r1 + 1, z.r2 - 1);
                else
                    L = z.r1;
            } else {
                // At or above second reduction
                if (z.r2 >= 300) L = 300;
                else L = rnd.next(z.r2, 300);
            }
        } else {
            Zone z = rnd.any(grand);
            int kind = rnd.next(0, 5);
            if (kind == 0) {
                // Below quest (or minimal)
                L = max(200, z.quest - 1);
            } else if (kind == 1) {
                L = z.quest;
            } else if (kind == 2) {
                if (z.r1 - z.quest > 1)
                    L = rnd.next(z.quest + 1, z.r1 - 1);
                else
                    L = z.quest;
            } else if (kind == 3) {
                L = z.r1;
            } else if (kind == 4) {
                if (z.r2 - z.r1 > 1)
                    L = rnd.next(z.r1 + 1, z.r2 - 1);
                else
                    L = z.r1;
            } else {
                if (z.r2 >= 300) L = 300;
                else L = rnd.next(z.r2, 300);
            }
        }
        if (L < 200) L = 200;
        if (L > 300) L = 300;
    }

    println(L);
    return 0;
}
