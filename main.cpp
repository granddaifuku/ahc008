#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define FOR(i, a, b) for (int i = (int)a; i < (int)b; ++i)
#define rrep(i, n) for (int i = ((int)n - 1); i >= 0; --i)

using ll = long long;
using ld = long double;

__attribute__((unused)) const ll INF = 1e18;
__attribute__((unused)) const int Inf = 1e9;
__attribute__((unused)) const double EPS = 1e-9;
__attribute__((unused)) const ll MOD = 1000000007;

const int WIDTH = 30;
const int TURN = 300;

// U D L R
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

enum Objects {
  Human,
  Cow,
  Pig,
  Rabbit,
  Dog,
  Cat,
  Partition,
  FuturePartition,
  FutureMove,
};

int N, M;
vector<int> hx, hy;
vector<vector<map<Objects, int>>> field(WIDTH,
                                        vector<map<Objects, int>>(WIDTH));

// DEBUG フィールドを出力する
// void output_field() {
//   rep(i, WIDTH) {
//     rep(j, WIDTH) cout << field[i][j];
//     cout << endl;
//   }
// }

// フィールドにセットする
void set_object(int x, int y, Objects obj) { field[x][y][obj]++; }

void unset_object(int x, int y, Objects obj) { field[x][y][obj]--; }

// フィールドに対象がいるかどうかを確認する
bool contain_object(int x, int y, Objects obj) { return field[x][y][obj] > 0; }

// マスに生物がいるかどうかを判定する
bool is_contain_lives(int x, int y) {
  if (field[x][y][Objects::Human] > 0 || field[x][y][Objects::Cow] > 0 ||
      field[x][y][Objects::Pig] > 0 || field[x][y][Objects::Rabbit] > 0 ||
      field[x][y][Objects::Dog] > 0 || field[x][y][Objects::Cat] > 0 ||
      field[x][y][Objects::FutureMove] > 0) {
    return true;
  }

  return false;
}

// マスに動物がいるかどうかを判定する
bool is_contain_animals(int x, int y) {
  if (field[x][y][Objects::Cow] > 0 || field[x][y][Objects::Pig] > 0 ||
      field[x][y][Objects::Rabbit] > 0 || field[x][y][Objects::Dog] > 0 ||
      field[x][y][Objects::Cat] > 0) {
    return true;
  }

  return false;
}

// マスが通行不能かどうかを判定する
bool is_partition(int x, int y) {
  return field[x][y][Objects::Partition] > 0 ||
         field[x][y][Objects::FuturePartition] > 0;
}

// グリッドを超える場合にはtrueを返し、それ以外はfalseを返す
bool is_out_of_bounds(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= WIDTH) {
    return true;
  }

  return false;
}

// しきりを置くことが出来る場合にはtrueを返し、それ以外はfalseを返す
bool can_place_partition(int x, int y) {
  if (is_contain_lives(x, y)) {
    return false;
  }
  if (is_partition(x, y)) {
    return false;
  }

  bool ok = true;
  // 隣接マスに動物がいる場合は置くことができない
  rep(i, 4) {
    int nx = x + dx[i], ny = y + dy[i];
    if (is_out_of_bounds(nx, ny)) {
      continue;
    }
    if (is_contain_animals(nx, ny)) {
      ok = false;
      break;
    }
  }

  return ok;
}

void apply(string s) {
  assert((int)s.size() == M);
  rep(i, M) {
    if (s[i] == 'U') {
      unset_object(hx[i], hy[i], Objects::Human);
      hx[i] += dx[0];
      hy[i] += dy[0];
      set_object(hx[i], hy[i], Objects::Human);
    } else if (s[i] == 'D') {
      unset_object(hx[i], hy[i], Objects::Human);
      hx[i] += dx[1];
      hy[i] += dy[1];
      set_object(hx[i], hy[i], Objects::Human);
    } else if (s[i] == 'L') {
      unset_object(hx[i], hy[i], Objects::Human);
      hx[i] += dx[2];
      hy[i] += dy[2];
      set_object(hx[i], hy[i], Objects::Human);
    } else if (s[i] == 'R') {
      unset_object(hx[i], hy[i], Objects::Human);
      hx[i] += dx[3];
      hy[i] += dy[3];
      set_object(hx[i], hy[i], Objects::Human);
    } else if (s[i] == 'u') {
      set_object(hx[i] - 1, hy[i], Objects::Partition);
    } else if (s[i] == 'd') {
      set_object(hx[i] + 1, hy[i], Objects::Partition);
    } else if (s[i] == 'l') {
      set_object(hx[i], hy[i] - 1, Objects::Partition);
    } else if (s[i] == 'r') {
      set_object(hx[i], hy[i] + 1, Objects::Partition);
    } else if (s[i] != '.') {
      exit(1);
    }
  }
  rep(i, WIDTH) {
    rep(j, WIDTH) {
      field[i][j][Objects::FuturePartition] = 0;
      field[i][j][Objects::FutureMove] = 0;
    }
  }
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(0);
  // Input
  cin >> N;
  vector<int> px(N), py(N);
  vector<Objects> pt(N);
  rep(i, N) {
    int type;
    cin >> px[i] >> py[i] >> type;
    px[i]--, py[i]--;
    if (type == 1) {
      pt[i] = Objects::Cow;
    } else if (type == 2) {
      pt[i] = Objects::Pig;
    } else if (type == 3) {
      pt[i] = Objects::Rabbit;
    } else if (type == 4) {
      pt[i] = Objects::Dog;
    } else {
      pt[i] = Objects::Cat;
    }
    set_object(px[i], py[i], pt[i]);
  }
  cin >> M;
  hx.resize(M), hy.resize(M);
  vector<int> dhx(M, 1), dhy(M, 1);  //方向を表す
  int mx = 0;
  rep(i, M) {
    cin >> hx[i] >> hy[i];
    hx[i]--, hy[i]--;
    set_object(hx[i], hy[i], Objects::Human);
    if (hx[i] >= mx) {
      mx = hx[i];
    }
  }

  // 各ターンの行動
  rep(_, TURN) {
    // 並行方向に線をひく
    string move(M, 'A');
    rep(i, M) {
      if (hx[i] == mx) {
        move[i] = '.';
        continue;
      }
      // 下に障害物をおくことができる
      if (!is_out_of_bounds(hx[i] + 1, hy[i]) &&
          can_place_partition(hx[i] + 1, hy[i])) {
        move[i] = 'd';
        set_object(hx[i] + 1, hy[i], Objects::FuturePartition);
        continue;
      }
      // 左右に移動する
      int ny;
      if (dhy[i] == 1) {
        ny = hy[i] + 1;
        move[i] = 'R';
        if (ny >= WIDTH) {
          ny = hy[i] - 1;
          dhy[i] = -1;
          move[i] = 'L';
        }
      } else {
        ny = hy[i] - 1;
        move[i] = 'L';
        if (ny < 0) {
          ny = hy[i] + 1;
          dhy[i] = 1;
          move[i] = 'R';
        }
      }
      if (is_partition(hx[i], ny)) {
        move[i] = '.';
      }
      if (move[i] == 'U') {
        set_object(hx[i] - 1, hy[i], Objects::FutureMove);
      } else if (move[i] == 'D') {
        set_object(hx[i] + 1, hy[i], Objects::FutureMove);
      } else if (move[i] == 'L') {
        set_object(hx[i], hy[i] - 1, Objects::FutureMove);
      } else if (move[i] == 'R') {
        set_object(hx[i], hy[i] + 1, Objects::FutureMove);
      }
    }
    cout << move << endl;
    apply(move);

    rep(i, N) {
      string pets;
      cin >> pets;
      unset_object(px[i], py[i], pt[i]);
      rep(j, pets.size()) {
        if (pets[j] == 'U') {
          px[i] += dx[0];
          py[i] += dy[0];
        } else if (pets[j] == 'D') {
          px[i] += dx[1];
          py[i] += dy[1];
        } else if (pets[j] == 'L') {
          px[i] += dx[2];
          py[i] += dy[2];
        } else if (pets[j] == 'R') {
          px[i] += dx[3];
          py[i] += dy[3];
        }
      }
      set_object(px[i], py[i], pt[i]);
    }
  }

  return 0;
}
