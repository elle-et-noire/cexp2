#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

const unsigned long long N = 1e7;

double f1(double x) {
  return x * x;
}

double f2(double x) {
  return -log(x);
}

double f3(double x, double y) {
  return x * y;
}

void rnd_method1() {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<> urnd(0, 1);

  /* prepare vector for histogram */
  int bins = 16;
  double sum = 0, xmax = 1, xmin = 0;
  double dx = (xmax - xmin) / bins;
  double dh = 1.0 / (N * dx);
  vector<int> hist(bins, 0);
  for (int i = 0; i < N; i++) {
    double x = f1(urnd(mt));
    sum += x;
    hist[(x - xmin) / dx] += 1;
  }
  char *data_file = "out.dat";
  FILE *data = fopen(data_file, "w");

  for (int j = 0; j < bins; ++j) {
    double x = (j + 0.5) * dx;
    double ave = hist[j] * dh;
    double err = sqrt(hist[j]) * dh;
    fprintf(data, "%d %15.10f %15.10f %15.10f\n", j, x, ave, err);
  }
  fclose(data);

  cout << setprecision(30) << sum / N << endl;
}

void rnd_method2() {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<> urnd(0, 1);

  double sum = 0;
  for (int i = 0; i < N; i++) {
    sum += f2(urnd(mt));
  }
  cout << setprecision(30) << sum / N << endl;
}

void rnd_method3() {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_real_distribution<> urnd(0, 1);

  double sum = 0;
  for (int i = 0; i < N; i++) {
    sum += f3(urnd(mt), urnd(mt));
  }
  cout << setprecision(30) << sum / N << endl;
}