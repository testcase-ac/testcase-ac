using System;
using System.Collections.Generic;

class Program {

    void WriteRoman(int number){
        if(number / 1000 != 0){
            for(int i = 0; i < number / 1000; i++){
                Console.Write("M");
            }
            number %= 1000;
        }
        if(number / 500 != 0){
            if(number >= 900){
                Console.Write("CM");
                number -= 900;
            }
            else {
                Console.Write("D");
                number %= 500;
            }
        }
        if(number >= 400){
            Console.Write("CD");
            number -= 400;
        }
        if(number / 100 != 0){
            for(int i = 0; i < number / 100; i++){
                Console.Write("C");
            }
            number %= 100;
        }
        if(number / 50 != 0){
            if(number >= 90){
                Console.Write("XC");
                number -= 90;
            }
            else {
                Console.Write("L");
                number %= 50;
            }
        }
        if(number >= 40){
            Console.Write("XL");
            number -= 40;
        }
        if(number / 10 != 0){
            for(int i = 0; i < number / 10; i++){
                Console.Write("X");
            }
            number %= 10;
        }
        if(number / 5 != 0){
            if(number >= 9){
                Console.Write("IX");
                number -= 9;
            }
            else {
                Console.Write("V");
                number %= 5;
            }
        }
        if(number >= 4){
            Console.Write("IV");
            number -= 4;
        }
        if(number != 0){
            for(int i = 0; i < number; i++){
                Console.Write("I");
            }
        }
    }

    int ReadRoman(string romannumber){
        int result = 0, len = romannumber.Length;
        for(int i = 0; i < len; i++){
            switch (romannumber[i])
            {
                case 'M':
                result += 1000;
                break;
                case 'D':
                result += 500;
                break;
                case 'C':
                if(i < len - 1 && (romannumber[i+1] == 'M' || romannumber[i+1] == 'D')){
                    result -= 100;
                }
                else {
                    result += 100;
                }
                break;
                case 'L':
                result += 50;
                break;
                case 'X':
                if(i < len - 1 && (romannumber[i+1] == 'C' || romannumber[i+1] == 'L')){
                    result -= 10;
                }
                else {
                    result += 10;
                }
                break;
                case 'V':
                result += 5;
                break;
                case 'I':
                if(i < len - 1 && (romannumber[i+1] == 'X' || romannumber[i+1] == 'V')){
                    result -= 1;
                }
                else {
                    result += 1;
                }
                break;
            }
        }
        return result;
    }

    void Run(){
      int n = int.Parse(Console.ReadLine());
      for(int i = 0; i < n; i++){
        var str = Console.ReadLine();
        if (
          str.StartsWith('I') ||
          str.StartsWith('V') ||
          str.StartsWith('X') ||
          str.StartsWith('L') ||
          str.StartsWith('C') ||
          str.StartsWith('D') ||
          str.StartsWith('M')
        ) {
          Console.WriteLine(ReadRoman(str));
        }
        else {
          WriteRoman(int.Parse(str));
          Console.WriteLine();
        }
      }
    }

    static void Main(string[] args){
      (new Program()).Run();
    }
}
