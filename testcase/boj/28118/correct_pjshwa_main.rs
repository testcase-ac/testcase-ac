use io::Write;
use std::{io, str};
use std::collections::HashSet;

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

fn find(parent: &mut Vec<usize>, x: usize) -> usize {
  if parent[x] == x { return x; }
  parent[x] = find(parent, parent[x]);
  parent[x]
}

fn union(parent: &mut Vec<usize>, x: usize, y: usize) {
  let x = find(parent, x);
  let y = find(parent, y);
  if x != y { parent[y] = x; }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());

  let mut parent = vec![0; n + 1];
  for i in 1..=n { parent[i] = i; }

  for _ in 0..m {
    let (u, v) = (scan.token::<usize>(), scan.token::<usize>());
    union(&mut parent, u, v);
  }

  let mut set = HashSet::new();
  for i in 1..=n { set.insert(find(&mut parent, i)); }
  writeln!(out, "{}", set.len() - 1).ok();
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
