fn main() {
  let mut line = String::new();
  std::io::stdin().read_line(&mut line).unwrap();
  let mut iter = line.split_whitespace();
  let n = iter.next().unwrap().parse::<u32>().unwrap();

  println!("{}", n * n - n);
}
