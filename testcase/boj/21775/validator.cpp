#include "testlib.h"

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Operation {
    int id;
    string kind;
    int resource;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int t = inf.readInt(n, 500000, "T");
    inf.readEoln();

    vector<int> turns(t);
    for (int i = 0; i < t; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        turns[i] = inf.readInt(1, n, "turn_player");
    }
    inf.readEoln();

    vector<Operation> cards(t);
    unordered_set<int> cardIds;
    cardIds.reserve(static_cast<size_t>(t) * 2);

    for (int i = 0; i < t; ++i) {
        cards[i].id = inf.readInt(1, 500000, "card_id");
        ensuref(cardIds.insert(cards[i].id).second,
                "duplicate card id %d at card index %d", cards[i].id, i + 1);
        inf.readSpace();

        cards[i].kind = inf.readToken("next|acquire|release", "operation");
        cards[i].resource = 0;
        if (cards[i].kind == "next") {
            inf.readEoln();
        } else {
            inf.readSpace();
            cards[i].resource = inf.readInt(1, 2000000000, "resource");
            inf.readEoln();
        }
    }

    vector<int> heldCard(n + 1, -1);
    unordered_map<int, int> owner;
    owner.reserve(static_cast<size_t>(t) * 2);
    int nextCard = 0;

    for (int turn = 0; turn < t; ++turn) {
        int player = turns[turn];
        int cardIndex = heldCard[player];
        if (cardIndex == -1) {
            ensuref(nextCard < t, "deck exhausted before turn %d", turn + 1);
            cardIndex = nextCard++;
        }

        const Operation& card = cards[cardIndex];
        if (card.kind == "next") {
            heldCard[player] = -1;
        } else if (card.kind == "acquire") {
            auto it = owner.find(card.resource);
            if (it == owner.end()) {
                owner[card.resource] = player;
                heldCard[player] = -1;
            } else {
                ensuref(it->second != player,
                        "player %d tries to acquire already owned resource %d at turn %d",
                        player, card.resource, turn + 1);
                heldCard[player] = cardIndex;
            }
        } else {
            auto it = owner.find(card.resource);
            ensuref(it != owner.end() && it->second == player,
                    "player %d releases unowned resource %d at turn %d",
                    player, card.resource, turn + 1);
            owner.erase(it);
            heldCard[player] = -1;
        }
    }

    inf.readEof();
}
