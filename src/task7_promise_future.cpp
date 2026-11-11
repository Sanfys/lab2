#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <cmath>
#include "common.h"
using namespace std;

void First(int n, promise<long long> p1, promise<bool> signal, promise<long long> p2)
{
    p1.set_value(NthPrime(n));
    signal.set_value(true);                 // сигнал другому потоку
    p2.set_value(NthPrime(n * 10));
}

void Second(future<bool> signal, int n)
{
    signal.get();                           // очікування сигналу
    this_thread::sleep_for(chrono::seconds(2));
    cout << "[Другий потік] sqrt(" << n << ") = " << sqrt((double)n) << endl;
}

int main()
{
    int n;
    cout << "Введіть n: ";
    cin >> n;

    promise<long long> p1, p2;
    promise<bool> signal;
    future<long long> f1 = p1.get_future(), f2 = p2.get_future();
    future<bool> fs = signal.get_future();

    auto t0 = chrono::steady_clock::now();
    auto el = [&] { return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - t0).count(); };

    thread t1(First, n, move(p1), move(signal), move(p2));
    thread t2(Second, move(fs), n);

    cout << n << "-те просте число: " << f1.get() << "  (через " << el() << " мс)" << endl;
    cout << n * 10 << "-те просте число: " << f2.get() << "  (через " << el() << " мс)" << endl;

    t1.join();
    t2.join();
    cout << "Завершено через " << el() << " мс" << endl;
    return 0;
}
