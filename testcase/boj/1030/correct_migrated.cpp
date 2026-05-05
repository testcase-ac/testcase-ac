#include<cstdio>
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main(){
	int s,N,K,r1,r2,c1,c2;
	scanf("%d %d %d %d %d %d %d",&s,&N,&K,&r1,&r2,&c1,&c2);
	for(int i=r1;i<=r2;i++){
		for(int j=c1;j<=c2;j++){
			int ii = i, jj = j, black = 0;
			//ii--;jj--;
			while(ii|jj){
				if(ii%N >= (N-K)/2 && ii%N < (N-K)/2 + K && jj%N >= (N-K)/2 && jj%N < (N-K)/2 + K){
					black = 1;
					break;
				}
				ii /= N; jj /= N;
			}
			printf("%d",black);
		}
		printf("\n");
	}
}
