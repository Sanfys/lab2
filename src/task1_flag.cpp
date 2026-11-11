#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include "common.h"
using namespace std;

mutex m;
queue<int> data_queue;
bool flag = false;

void DataPreparation()
{
    int x;
    cout << "Вводьте цілі числа (будь-який нечисловий символ або EOF - кінець вводу):" << endl;
    while (cin >> x)
    {
        lock_guard<mutex> lk(m);
        data_queue.push(x);
    }
    lock_guard<mutex> lk(m);
    flag = true;                       // сигнал для DataProcessing
}

void DataProcessing()
{
    unique_lock<mutex> lk(m);
    while (!flag)
    {
        lk.unlock();
        this_thread::sleep_for(chrono::milliseconds(100));
        lk.lock();
    }
    cout << "Прості числа з черги:";
    while (!data_queue.empty())
    {
        int v = data_queue.front();
        data_queue.pop();
        if (IsPrime(v)) cout << " " << v;
    }
    cout << endl;
}

int main()
{
    thread prep(DataPreparation);
    prep.detach();
    thread proc(DataProcessing);
    proc.join();
    return 0;
}
