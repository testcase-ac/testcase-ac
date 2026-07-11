#include <iostream>
#include <string>

int N;
std::string S;
int A[200002]; // 0:rock, 1:paper, 2:scissor
int fw[3][200002], bw[3][200002];

int main(){

    std::cin >> N >> S;

    for(int i = 1; i <= N; i++){
        if(S[i-1] == 'R') A[i] = 0;
        if(S[i-1] == 'P') A[i] = 1;
        if(S[i-1] == 'S') A[i] = 2;
        fw[A[i]][i]++;
        bw[A[i]][i]++;
    }

    for(int type = 0; type <= 2; type++){
        for(int i = 1; i <= N; i++) fw[type][i] += fw[type][i-1];
        for(int i = N; i >= 0; i--) bw[type][i] += bw[type][i+1];
    }

    for(int i = 1; i <= N; i++){
        int now = A[i];
        int lose = (now+1)%3;
        int win = (now+2)%3;
        int flg = 1;

        if(fw[lose][i-1] > 0 && fw[win][i-1] == 0) flg = 0;
        if(bw[lose][i+1] > 0 && bw[win][i+1] == 0) flg = 0;

        std::cout << (flg ? '1' : '0');
    }
    std::cout << '\n';
}
