using System;
using System.Numerics;

class Program {
    
    void Run(){
        var n = int.Parse(Console.ReadLine());
        var a = new BigInteger(0);
        var b = new BigInteger(1);
        var c = new BigInteger(0);
        if(n == 1){
            Console.WriteLine(1);
        }
        else{
            while(n > 1){
                c = a + b;
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