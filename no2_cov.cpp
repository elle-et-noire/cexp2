#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

// x, y : (0,1) の独立な一様分布
// z1, z2 : N(0,1) の独立な正規分布
void box_muller(double x, double y, double &z1, double &z2) {
  z1 = sqrt(-2 * log(x)) * cos(2 * M_PI * y);
  z2 = sqrt(-2 * log(x)) * sin(2 * M_PI * y);
}

vector<double> L(4); // 共分散行列をコレスキー分解した下三角行列
vector<double> S(4); // 共分散行列
double mu1, mu2;     // 平均値
void box_muller_cov(double x, double y, double &z1, double &z2) {
  box_muller(x, y, z1, z2);
  z2 = L[2] * z1 + L[3] * z2 + mu2;
  z1 = L[0] * z1 + mu1;
}

int main() {
  random_device rnd;
  // mt19937 mt(rnd());
  mt19937 mt((int)time(0));
  uniform_real_distribution<> uni_rnd(0, 1);
  uniform_real_distribution<> coef_rnd(-20, 20);

  // L_11, L_12, L_21, L_22 の順に下三角行列を作る
  for (int i = 0; i < 4; i++) {
    L[i] = coef_rnd(mt);
  }
  L[1] = 0; // 下三角
  // S = LL^T
  S[0] = L[0] * L[0];
  S[1] = S[2] = L[0] * L[2];
  S[3] = L[2] * L[2] + L[3] * L[3];
  // 平均値
  mu1 = coef_rnd(mt), mu2 = coef_rnd(mt);

  const int rep_n = 1e7;
  double z1, z2;                         // 正規分布
  double mu1_calc = 0.0, mu2_calc = 0.0; // 平均値計算
  vector<double> cov(4, 0.0);            // 分散、共分散計算
  double t1, t2;                         // temporary variable
  for (int i = 0; i < rep_n; i++) {
    box_muller_cov(uni_rnd(mt), uni_rnd(mt), z1, z2);
    mu1_calc += z1, mu2_calc += z2;
    cov[0] += (z1 - mu1) * (z1 - mu1);
    cov[1] += (z1 - mu1) * (z2 - mu2);
    cov[3] += (z2 - mu2) * (z2 - mu2);
  }
  mu1_calc /= (double)rep_n;
  mu2_calc /= (double)rep_n;
  for (int i = 0; i < 4; i++) {
    cov[i] /= (double)rep_n;
  }
  cov[2] = cov[1];
  cout << "prepared:\n";
  cout << mu1 << ", " << mu2 << endl;
  for (int i = 0; i < 4; i++)
    cout << S[i] << ", ";
  cout << endl;
  cout << "calced:\n";
  cout << mu1_calc << ", " << mu2_calc << endl;
  for (int i = 0; i < 4; i++)
    cout << cov[i] << ", ";
  cout << endl;
}