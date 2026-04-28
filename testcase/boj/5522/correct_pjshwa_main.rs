fn main() {
  let mut sum = 0;
  let mut line = String::new();

  for _i in 0..5 {
    std::io::stdin().read_line(&mut line).unwrap();
    let mut iter = line.split_whitespace();
    sum += iter.next().unwrap().parse::<usize>().unwrap();
    line.clear();
  }

  println!("{}", sum);
}
