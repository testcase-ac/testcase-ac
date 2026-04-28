using System;

class Program {
    
    void Run(){
        long n = long.Parse(Console.ReadLine()) % 1500000;
        long a = 0, b = 1;
        long c = 0;
        if(n == 1){
            Console.WriteLine(1);
        }
        else{
            while(n > 1){
                c = (a + b) % 1000000;
                a = b;
                b = c;
                n--;
            }
            Console.WriteLine(c);
        }
    }
    static void Main(string[] args){
        (new Program()).Run();
    }
}