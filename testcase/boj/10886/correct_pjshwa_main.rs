use std::io::{self, BufRead};

fn main() {
  let stdin = io::stdin();
  let mut iter = stdin.lock().lines();
  let n = iter.next().unwrap().unwrap().parse::<usize>().unwrap();
  let mut cnt = 0;

  for _ in 0..n {
    cnt += iter.next().unwrap().unwrap().parse::<usize>().unwrap();
  }

  if n < 2 * cnt {
    println!("Junhee is cute!");
  }
  else {
    println!("Junhee is not cute!");
  }
}
