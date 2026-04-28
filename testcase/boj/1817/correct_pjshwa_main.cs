using System;
using System.Linq;

namespace b_01817 {
	public class Program {
		public static void Main(string[] args){
			int[] nm = (from pars in Console.ReadLine().Split()
						select int.Parse(pars)).ToArray();
			if(nm[0] == 0){
				Console.Write(0);
			}
			else{
				int m = nm[1];
				var books_weight = Console.ReadLine().Split().Select(int.Parse);
				int number_of_boxes = 1;
				int left_weight = m;
				foreach(var i in books_weight){
					if(left_weight >= i) left_weight -= i;
					else {
						left_weight = m - i;
						number_of_boxes++; 
					}
				}
				Console.Write(number_of_boxes);
			}
		}
	}
}