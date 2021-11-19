#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;

const int N = 100;

int arr[N];

int main() {
  random_device rnd;
  mt19937 mt(rnd());
  uniform_int_distribution<> randN(0, N - 1);

  for (int i = 0; i < N; i++) {
    arr[i] = randN(mt);
    cout << arr[i] << endl;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (arr[i] < arr[j]) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
  cout << "after sort" << endl;
  for (int i = 0; i < N; i++) {
    cout << arr[i] << endl;
  }
  return 0;
}
