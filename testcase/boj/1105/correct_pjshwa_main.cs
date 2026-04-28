using System;

class Program {

	long PowerOf10(int power){
		long temp = 1;
		for(int i = 0; i < power; i++){
			temp *= 10;
		}
		return temp;
	}

	void Run(){
		long[] a = Array.ConvertAll(Console.ReadLine().Split(), s=>long.Parse(s));
		int digits = 0, digits2 = 0;
		long temp = a[0];
		while(temp != 0){
			temp /= 10;
			digits++;
		}
		temp = a[1];
		while(temp != 0){
			temp /= 10;
			digits2++;
		}
		a[1] %= PowerOf10(digits);
		int answer = 0;
		if(digits == digits2){
			while(a[0] / PowerOf10(digits-1) == a[1] / PowerOf10(digits-1)){
				if(a[0] / PowerOf10(digits-1) == 8) answer++;
				a[0] %= PowerOf10(digits-1);
				a[1] %= PowerOf10(digits-1);
				digits--;
				if (digits == 0) break;
			}
		}
		
		Console.WriteLine(answer);
	}
	static void Main(string[] args){
		(new Program()).Run();
		
	}
}