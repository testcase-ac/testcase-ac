use std::io;
use std::io::BufRead;

fn main() {
  let stdin = io::stdin();
  let mut lines = stdin.lock().lines();       
  let n = lines.next().unwrap().unwrap().parse::<usize>().unwrap();

  let mut res = 1;
  let modulo = 1000000;
  let mut tmp;

  for i in 1..=n {
    tmp = i;
    res = tmp * res;
    while tmp % 5 == 0 {
      res /= 10;
      tmp /= 5;
    }
    res %= modulo;
  }
  println!("{}", res % 10);
}
