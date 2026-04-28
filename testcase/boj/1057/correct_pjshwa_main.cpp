#include <cstdio>

int main(){
	int n, k, l;
	scanf("%d%d%d", &n, &k, &l);
	int fights = 0;
	if(k > l){
		int temp = k;
		k = l;
		l = temp;
	}
	bool didNotCompete = true;
	while(n != 1){
		fights++;
		if(l % 2 == 0 && l == k + 1){
			didNotCompete = false;
			break;
		}
		n++; k++; l++;
		n/=2;k/=2;l/=2;
		
	}
	if(didNotCompete) fights = -1;
	printf("%d", fights);
}