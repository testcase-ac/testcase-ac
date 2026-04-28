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

fn dfs(
  cur: &mut Vec<usize>,
  sum: usize,
  ord: &mut usize,
  n: usize,
  k: usize,
) {
  if sum == n {
    *ord += 1;
    if *ord == k {
      let z = cur.len();
      for i in 0..z - 1 {
        print!("{}+", cur[i]);
      }
      println!("{}", cur[z - 1]);
      std::process::exit(0);
    }
    return;
  }

  for i in 1..=3 {
    if sum + i <= n {
      cur.push(i);
      dfs(cur, sum + i, ord, n, k);
      cur.pop();
    }
  }
  
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, k) = (scan.token::<usize>(), scan.token::<usize>());

  let mut cur = vec![];
  let mut ord = 0;

  dfs(&mut cur, 0, &mut ord, n, k);
  println!("-1");
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
