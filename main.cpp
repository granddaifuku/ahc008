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

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

enum Objects {
  None,
  Cow,
  Pig,
  Rabbit,
  Dog,
  Cat,
  Human,
  Partition,
};
vector<vector<int>> field(WIDTH, vector<int>(WIDTH, Objects::None));

// DEBUG フィールドを出力する
void output_field() {
  rep(i, WIDTH) {
    rep(j, WIDTH) cout << field[i][j];
    cout << endl;
  }
}

// マスに生物がいるかどうかを判定する
bool is_contain_lives(int x, int y) {
  if (field[x][y] == Objects::Human || field[x][y] == Objects::Cow ||
      field[x][y] == Objects::Pig || field[x][y] == Objects::Rabbit ||
      field[x][y] == Objects::Dog || field[x][y] == Objects::Cat) {
    return true;
  }

  return false;
}

// マスに動物がいるかどうかを判定する
bool is_contain_animals(int x, int y) {
  if (field[x][y] == Objects::Cow || field[x][y] == Objects::Pig ||
      field[x][y] == Objects::Rabbit || field[x][y] == Objects::Dog ||
      field[x][y] == Objects::Cat) {
    return true;
  }

  return false;
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
  if (field[x][y] == Objects::Human || field[x][y] == Objects::Cow ||
      field[x][y] == Objects::Pig || field[x][y] == Objects::Rabbit ||
      field[x][y] == Objects::Dog || field[x][y] == Objects::Cat ||
      field[x][y] == Objects::Partition) {
    return false;
  }

  bool ok = true;
  // 隣接マスに動物がいる場合は置くことができない
  rep(i, 4) {
    int nx = x + dx[i], ny = y + dy[i];
    if (is_out_of_bounds(nx, ny)) {
      continue;
    }
    if (field[nx][ny] == Objects::Cow || field[nx][ny] == Objects::Pig ||
        field[nx][ny] == Objects::Rabbit || field[nx][ny] == Objects::Dog ||
        field[nx][ny] == Objects::Cat) {
      ok = false;
      break;
    }
  }

  return ok;
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(0);
  // Input
  int N, M;
  cin >> N;
  vector<int> px(N), py(N), pt(N);
  rep(i, N) {
    cin >> px[i] >> py[i] >> pt[i];
    px[i]--, py[i]--;
    field[px[i]][py[i]] = pt[i];
  }
  cin >> M;
  vector<int> hx(M), hy(M);
  vector<int> dhx(M, 1), dhy(M, 1);  //方向を表す
  rep(i, M) {
    cin >> hx[i] >> hy[i];
    hx[i]--, hy[i]--;
    field[hx[i]][hy[i]] = Objects::Human;
  }

  rep(_, TURN) {
    // 並行方向に線をひく
    string move(M, 'A');
    rep(i, M) {
      // 下に障害物をおくことができる
      if (!is_out_of_bounds(hx[i] + 1, hy[i]) &&
          can_place_partition(hx[i] + 1, hy[i])) {
        field[hx[i] + 1][hy[i]] = Objects::Partition;
        move[i] = 'd';
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
      if (field[hx[i]][ny] == Objects::Partition) {
        move[i] = '.';
      } else {
        field[hx[i]][hy[i]] = Objects::None;
        field[hx[i]][ny] = Objects::Human;
        hy[i] = ny;
      }
    }
    cout << move << endl;

    rep(i, N) {
      string pets;
      cin >> pets;
      field[px[i]][py[i]] = -1;
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
      field[px[i]][py[i]] = pt[i];
    }
  }

  return 0;
}
