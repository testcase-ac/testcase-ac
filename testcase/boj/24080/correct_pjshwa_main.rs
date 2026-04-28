use io::Write;
use std::{io, str};

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
  let _n = scan.token::<usize>();
  let s = scan.token::<String>();

  let mut t = vec![0; 5];
  for c in s.chars() {
    match c {
      'A' => t[0] += 1,
      'B' => t[1] += 1,
      'C' => t[2] += 1,
      'D' => t[3] += 1,
      'E' => t[4] += 1,
      _ => unreachable!(),
    }
  }

  let mut cnt = 0;
  for i in 0..5 { if t[i] > 0 { cnt += 1; } }

  if cnt >= 3 { writeln!(out, "Yes").ok(); }
  else { writeln!(out, "No").ok(); }
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
