#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
/*
back: 트레이싱을 할 때 따라가는 값.
(다음 A 항의 위치 * 1000 + 다음 B 항의 위치)로 해싱.
*/
int Alen, Blen, A[500], B[500], dp[500][500], back[500][500];
 
// LCIS 길이를 구하며 back 배열도 채우는 함수
int LCIS(int Apos, int Bpos){
    // 기저 사례: 어느 한쪽이 수열의 끝에 도달함
    if(Apos==Alen || Bpos==Blen) return 0;
    int &ret = dp[Apos][Bpos];
    if(ret != -1) return ret;
 
    ret = 1;
    // back 배열의 초기값: 더 이상 따라갈 항이 없음
    back[Apos][Bpos] = Alen*1000 + Blen;
    // A의 뒤에 있는 항들에 대해 매칭해서 결과를 구함
    for(int i=Apos+1; i<Alen; i++){
        if(A[Apos] >= A[i]) continue;
        for(int j=Bpos+1; j<Blen; j++){
            if(A[i] == B[j]){
                int temp = LCIS(i, j) + 1;
                if(ret < temp){
                    ret = temp;
                    back[Apos][Bpos] = i*1000 + j;
                }
                break;
            }
        }
    }
    return ret;
}
 
// LCIS를 찾아가는 함수
void trace(int Apos, int Bpos){
    if(Apos==Alen || Bpos==Blen) return;
    printf("%d ", A[Apos]);
    trace(back[Apos][Bpos]/1000, back[Apos][Bpos]%1000);
}
 
int main(){
    scanf("%d", &Alen);
    for(int i=0; i<Alen; i++)
        scanf("%d", A+i);
    scanf("%d", &Blen);
    for(int i=0; i<Blen; i++)
        scanf("%d", B+i);
 
    // dp로 LCIS를 구함. 이때 시작 항의 정보 역시 start에 해싱해서 보유
    memset(dp, -1, sizeof(dp));
    int result = 0, start = -1;
    for(int i=0; i<Alen; i++){
        for(int j=0; j<Blen; j++){
            if(A[i] == B[j]){
                int temp = LCIS(i, j);
                if(result < temp){
                    result = temp;
                    start = i*1000 + j;
                }
                break;
            }
        }
    }
    // LCIS의 길이
    printf("%d\n", result);
    // LCIS 출력
    if(start != -1) trace(start/1000, start%1000);
}
