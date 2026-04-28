macro_rules! parse_line { ($($t: ty),+) => ({
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  ($(iter.next().unwrap().parse::<$t>().unwrap()),+)
})}

use std::cmp;
use std::cmp::Ordering::*;

fn main() {
  let (br, bc) = parse_line!(i16, i16);
  let (dr, dc) = parse_line!(i16, i16);
  let (jr, jc) = parse_line!(i16, i16);

  let bd = cmp::max((br - jr).abs(), (bc - jc).abs());
  let dd = (dr - jr).abs() + (dc - jc).abs();

  println!("{}", match bd.cmp(&dd) {
    Less    => "bessie",
    Equal   => "tie",
    Greater => "daisy"
  });
}
