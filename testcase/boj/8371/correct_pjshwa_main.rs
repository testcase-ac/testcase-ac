use std::io::{self, BufRead};

fn main() {
  let stdin = io::stdin();
  let mut iter = stdin.lock().lines();
  let n = iter.next().unwrap().unwrap().parse::<usize>().unwrap();
  let line1 = iter.next().unwrap().unwrap();
  let line2 = iter.next().unwrap().unwrap();
  let line1_bytes = line1.as_bytes();
  let line2_bytes = line2.as_bytes();

  let mut count = 0;

  for i in 0..n {
    if line1_bytes[i] != line2_bytes[i] {
      count += 1;
    }
  }

  println!("{}", count);
}
