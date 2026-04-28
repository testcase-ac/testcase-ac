use io::Write;
use std::{io, str, collections::BTreeMap};

pub struct UnsafeScanner<R> {
  reader: R,
  buf_str: Vec<u8>,
  buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
  pub fn new(reader: R) -> Self {
    Self {
      reader,
      buf_str: vec![],
      buf_iter: "".split_ascii_whitespace(),
    }
  }
  
  pub fn token<T: str::FromStr>(&mut self) -> T {
    loop {
      if let Some(token) = self.buf_iter.next() {
        return token.parse().ok().expect("Failed parse");
      }
      self.buf_str.clear();
      self.reader
          .read_until(b'\n', &mut self.buf_str)
          .expect("Failed read");
      self.buf_iter = unsafe {
        let slice = str::from_utf8_unchecked(&self.buf_str);
        std::mem::transmute(slice.split_ascii_whitespace())
      }
    }
  }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();

  let mut sum = 0;
  let mut map = BTreeMap::new();
  for _ in 0..n {
    let x = scan.token::<usize>();
    sum += x;
    *map.entry(x).or_insert(0) += 1;
  }

  let (mut vk, mut ans) = (0, sum);
  for (k, v) in map.iter() {
    let val = sum + k * v;
    if val > ans {
      ans = val;
      vk = *k;
    }
  }

  let (mut vec1, mut vec2) = (vec![], vec![]);
  for (k, v) in map.iter() {
    if *k < vk {
      for _ in 0..*v { vec1.push(*k); }
    }
    else if *k > vk {
      for _ in 0..*v { vec2.push(*k); }
    }
  }
  vec2.reverse();

  writeln!(out, "{}", ans).ok();
  for x in vec2 { write!(out, "{} ", x).ok(); }
  for x in vec1 { write!(out, "{} ", x).ok(); }
  for _ in 0..map[&vk] { write!(out, "{} ", vk).ok(); }
  writeln!(out).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  let t = 1;
  // let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}
