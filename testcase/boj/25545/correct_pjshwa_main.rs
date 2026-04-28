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

struct UnionFind {
  par: Vec<usize>,
  usz: Vec<usize>,
  n: usize,
}

impl UnionFind {
  fn new(n: usize) -> Self {
    Self {
      par: (0..n).collect(),
      usz: vec![1; n],
      n
    }
  }

  fn find(&mut self, x: usize) -> usize {
    if self.par[x] == x { x }
    else {
      let p = self.par[x];
      self.par[x] = self.find(p);
      self.par[x]
    }
  }

  fn unite(&mut self, x: usize, y: usize) {
    let x = self.find(x);
    let y = self.find(y);
    if x == y { return; }
    self.par[x] = y;
    self.usz[y] += self.usz[x];
  }

  fn reset(&mut self) {
    self.par = (0..self.n).collect();
    self.usz = vec![1; self.n];
  }
}

#[derive(Clone)]
pub struct Tuple {
  pub u: usize,
  pub v: usize,
  pub i: usize,
  pub w: i32,
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let (n, m) = (scan.token::<usize>(), scan.token::<usize>());

  let mut uf = UnionFind::new(n);
  let mut edges = vec![];
  for i in 0..m {
    let (u, v, w) = (scan.token::<usize>(), scan.token::<usize>(), scan.token::<i32>());
    edges.push(Tuple { u: u - 1, v: v - 1, w: w, i: i });
  }
  edges.sort_by(|a, b| a.w.cmp(&b.w));

  // Check if we can make a tree first
  let mut uc = 0;
  let mut unused_edge = m;
  for i in 0..m {
    let (u, v) = (edges[i].u, edges[i].v);
    if uf.find(u) != uf.find(v) {
      uf.unite(u, v);
      uc += 1;
    }
    else {
      unused_edge = i;
    }
  }

  if uc < n - 1 || m == n - 1 {
    writeln!(out, "NO").unwrap();
    return;
  }

  let mut ans = vec![];
  uf.reset();
  let (u, v) = (edges[unused_edge].u, edges[unused_edge].v);
  uf.unite(u, v);
  ans.push(edges[unused_edge].i + 1);

  for j in 0..m {
    let (u, v, i) = (edges[j].u, edges[j].v, edges[j].i);
    if uf.find(u) != uf.find(v) {
      uf.unite(u, v);
      ans.push(i + 1);
    }
  }

  writeln!(out, "YES").unwrap();
  for i in 0..n - 1 {
    write!(out, "{} ", ans[i]).unwrap();
  }
  writeln!(out).unwrap();
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
