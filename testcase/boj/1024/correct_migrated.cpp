#include <stdio.h>

int getMinDiv(int x, int bottom) {
	int i;
	for(i=bottom; i<=x; i++) {
		if(i > x/i + 1 || i > 100) {
			return -1;
		}
		
		if(x%i == 0) {
			if(i%2 == 0 && (x/i)%2 == 1) {
				return i;
			} else if(i%2 == 1 && (x/i)%2 == 0) {
				return i;
			}
		}
	}
	return -1;
}

int main() {
	int arrSum;
	int minLen;
	scanf("%d %d", &arrSum, &minLen);
	
	int arrLen = getMinDiv(arrSum * 2, minLen);
	if(arrLen != -1) {
		int arrAvg = arrSum/arrLen;
		int i;
		int temp = arrLen/2;
		if(arrLen%2 == 0) {
			for(i=arrAvg-temp+1; i<=arrAvg+temp; i++) {
				printf("%d ", i);
			}
		} else {
			for(i=arrAvg-temp; i<=arrAvg+temp; i++) {
				printf("%d ", i);
			}
		}
	} else {
		printf("%d", -1);
	}
	
	return 0;
}
