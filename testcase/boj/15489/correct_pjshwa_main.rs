use std::io;

fn main() {
  let mut s = String::new();

  io::stdin().read_line(&mut s).unwrap();

  let values:Vec<i32> = s
      .as_mut_str()
      .split_whitespace()
      .map(|s| s.parse().unwrap())
      .collect();

  let r = values[0];
  let c = values[1];
  let w = values[2];

  let mut res = 1;
  for i in 1..=(c - 1) {
    res *= r - i;
    res /= i;
  }

  let mut tmp = 1;
  for i in 1..=c {
    tmp *= r + w - i;
    tmp /= i;
  }

  for i in 1..=(w - 1) {
    res += tmp;
    tmp *= r + w - c - i;
    tmp /= c + i;
  }

  println!("{}", res);
}
