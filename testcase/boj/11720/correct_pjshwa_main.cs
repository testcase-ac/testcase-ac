using System;
using System.Linq;

namespace b_11720 {
	public class Program {
		public static void Main(string[] args){
			Console.ReadLine();
			var numbers = Console.ReadLine();
			int sum = 0;
			foreach(var i in numbers){
				sum += (int)Char.GetNumericValue(i);
			}
			Console.Write(sum);
		}
	}
}