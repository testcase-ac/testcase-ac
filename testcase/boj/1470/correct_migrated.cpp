#include <stdio.h>
#include <algorithm>
#include <queue>
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
struct Team{
    int gold;
    int silver;
    int bronze;
    int number;

    bool operator==(const Team &t) const{
        return number == t.number;
    }
};

const int MAX_CONTESTANTS = 55;

Team contestants[MAX_CONTESTANTS];

int main(){
    int N, L;

    scanf("%d %d", &N, &L);

    for(int i=0; i<N; i++){
        scanf("%d %d %d", &contestants[i].gold, &contestants[i].silver, &contestants[i].bronze);
        contestants[i].number = i + 1;
    }

    contestants[0].gold += L;

    Team first = contestants[0];

    std::sort(
        contestants,
        contestants+N,
        [](const Team &a, const Team &b){ 
        if(a.gold == b.gold){
            if(a.silver == b.silver){
                if(a.bronze == b.bronze){
                    return a.number < b.number;
                }
                return a.bronze > b.bronze;
            }
            return a.silver > b.silver;
        }
        return a.gold > b.gold;
        }
    );

    int rank = 0;

    int bronzeReserve = L;
    int silverReserve = L;

    while(!(first == contestants[rank])) rank++;

    rank++;

    std::priority_queue<int> revertables;

    while(rank < N){
        // printf("%dth team: id %d / %d %d %d\n", rank, contestants[rank].number, contestants[rank].gold, contestants[rank].silver, contestants[rank].bronze);
        
        if(first.gold > contestants[rank].gold) break;

        silverReserve -= (first.silver - contestants[rank].silver);
        if(silverReserve < 0) break;

        if(first.bronze < contestants[rank].bronze){
            rank++;
            continue;
        }

        if((first.bronze - contestants[rank].bronze + 1) + (first.silver - contestants[rank].silver) > L){
            silverReserve--;
            if(silverReserve < 0) break;
            rank++;
            continue;
        }
        
        bronzeReserve -= (first.bronze - contestants[rank].bronze + 1);
        revertables.push((first.bronze - contestants[rank].bronze + 1));

        if(bronzeReserve < 0){
            if(silverReserve > 0) {
                silverReserve--;
                bronzeReserve += revertables.top();
                revertables.pop();
            }
            else break;
        }

        rank++;
    }

    printf("%d", rank);
}
