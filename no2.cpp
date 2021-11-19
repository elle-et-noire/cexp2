#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
using namespace std;

// x, y : (0,1) の独立な一様分布
// z1, z2 : N(0,1) の独立な正規分布
void box_muller(double x, double y, double &z1, double &z2) {
  z1 = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
  z2 = sqrt(-2 * log(x)) * sin(2 * M_PI * y);
}

int main() {
  random_device rnd;
  // mt19937 mt(rnd());
  mt19937 mt((int)time(0));
  uniform_real_distribution<> uni_rnd(0, 1);
  const int rep_n = 1e5;
  const int rep_n2 = rep_n * 1e3;
  const int n = 10;      // n-1 次のモーメントまで見る
  const int lit = 6;     // lit 次以降はループ回数を増やす
  double z1, z2;         // 正規分布
  double mu1[n], mu2[n]; // mu[i] : 0 周りの i 次のモーメント
  double t1, t2;         // temporary variable
  for (int i = 0; i < rep_n; i++) {
    box_muller(uni_rnd(mt), uni_rnd(mt), z1, z2);
    t1 = z1, t2 = z2;
    for (int j = 0; j < lit; j++) {
      mu1[j] += t1;
      mu2[j] += t2;
      t1 *= z1, t2 *= z2;
    }
  }
  for (int i = 0; i < lit; i++)
    mu1[i] /= rep_n, mu2[i] /= rep_n;

  for (int i = 0; i < rep_n2; i++) {
    box_muller(uni_rnd(mt), uni_rnd(mt), z1, z2);
    t1 = pow(z1, lit + 1), t2 = pow(z2, lit + 1);
    for (int j = lit; j < n; j++) {
      mu1[j] += t1 / rep_n2;
      mu2[j] += t2 / rep_n2;
      t1 *= z1, t2 *= z2;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << mu1[i] << ", " << mu2[i] << endl;
  }
  return 0;
}