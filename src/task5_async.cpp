#include <iostream>
#include <future>
#include <chrono>
#include <cmath>
#include "common.h"
using namespace std;
using namespace chrono;

void Run(launch policy, const char* name, int n)
{
    cout << "\n=== Режим " << name << " ===" << endl;
    auto t0 = steady_clock::now();
    future<long long> f = async(policy, NthPrime, n);

    cout << "Яку функцію обчислити від номера " << n << "? (1 - sqrt, 2 - sin, 3 - ln): " << flush;
    int c; cin >> c;
    double v = c == 1 ? sqrt((double)n) : c == 2 ? sin((double)n) : log((double)n);
    cout << "Значення функції: " << v << endl;

    auto t1 = steady_clock::now();
    long long p = f.get();
    auto t2 = steady_clock::now();
    cout << n << "-те просте число: " << p << endl;
    cout << "Очікування на get(): "
         << duration_cast<milliseconds>(t2 - t1).count() << " мс; "
         << "загальний час: " << duration_cast<milliseconds>(t2 - t0).count() << " мс" << endl;
}

int main()
{
    int n;
    cout << "Введіть n: ";
    cin >> n;
    Run(launch::deferred, "launch::deferred", n);
    Run(launch::async, "launch::async", n);
    return 0;
}
