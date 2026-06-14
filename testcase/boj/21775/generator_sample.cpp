#include "testlib.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Card {
    int id;
    string op;
    int resource;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    int t;
    if (mode == 0) {
        n = 1;
        t = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 4);
        t = rnd.next(n, 18);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        t = rnd.next(max(n, 12), 45);
    } else {
        n = rnd.next(6, 15);
        t = rnd.next(max(n, 30), 90);
    }

    vector<int> turns(t);
    for (int i = 0; i < t; ++i) {
        if (mode == 1 && i > 0 && rnd.next(100) < 55) {
            turns[i] = turns[i - 1] == 1 ? 2 : 1;
        } else {
            turns[i] = rnd.next(1, n);
        }
    }

    int idBase = rnd.next(1, 500000 - t + 1);
    vector<Card> cards;
    vector<int> held(n + 1, -1);
    map<int, int> owner;
    int maxResource = mode == 0 ? 3 : rnd.next(3, 20);

    auto resourcesOwnedBy = [&](int player) {
        vector<int> resources;
        for (const auto& entry : owner) {
            if (entry.second == player) {
                resources.push_back(entry.first);
            }
        }
        return resources;
    };

    auto resourcesOwnedByOthers = [&](int player) {
        vector<int> resources;
        for (const auto& entry : owner) {
            if (entry.second != player) {
                resources.push_back(entry.first);
            }
        }
        return resources;
    };

    auto publicResources = [&]() {
        vector<int> resources;
        for (int r = 1; r <= maxResource; ++r) {
            if (!owner.count(r)) {
                resources.push_back(r);
            }
        }
        return resources;
    };

    for (int turn = 0; turn < t; ++turn) {
        int player = turns[turn];

        if (held[player] != -1) {
            Card& card = cards[held[player]];
            if (!owner.count(card.resource)) {
                owner[card.resource] = player;
                held[player] = -1;
            }
            continue;
        }

        int choice = rnd.next(100);
        vector<int> mine = resourcesOwnedBy(player);
        vector<int> others = resourcesOwnedByOthers(player);
        vector<int> free = publicResources();

        Card card{idBase + static_cast<int>(cards.size()), "next", 0};
        if (!mine.empty() && choice < 25) {
            card.op = "release";
            card.resource = rnd.any(mine);
            owner.erase(card.resource);
        } else if (!others.empty() && choice < 65) {
            card.op = "acquire";
            card.resource = rnd.any(others);
            held[player] = static_cast<int>(cards.size());
        } else if (!free.empty() && choice < 90) {
            card.op = "acquire";
            card.resource = rnd.any(free);
            owner[card.resource] = player;
        }
        cards.push_back(card);
    }

    while (static_cast<int>(cards.size()) < t) {
        cards.push_back({idBase + static_cast<int>(cards.size()), "next", 0});
    }

    println(n, t);
    println(turns);
    for (const Card& card : cards) {
        if (card.op == "next") {
            println(card.id, card.op);
        } else {
            println(card.id, card.op, card.resource);
        }
    }

    return 0;
}
