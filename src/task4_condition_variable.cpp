#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "common.h"
using namespace std;

mutex m;
queue<int> data_queue;
condition_variable cv;
bool finished = false;   // кінець вводу

void DataPreparation()
{
    int x;
    cout << "Вводьте цілі числа (будь-який нечисловий символ або EOF - кінець вводу):" << endl;
    while (cin >> x)
    {
        {
            lock_guard<mutex> lk(m);
            data_queue.push(x);
        }
        cv.notify_one();
    }
    {
        lock_guard<mutex> lk(m);
        finished = true;
    }
    cv.notify_one();
}

void DataProcessing()
{
    cout << "Прості числа з черги:";
    while (true)
    {
        unique_lock<mutex> lk(m);
        cv.wait(lk, [] { return !data_queue.empty() || finished; });
        if (data_queue.empty()) break;       // finished і черга порожня
        int v = data_queue.front();
        data_queue.pop();
        lk.unlock();
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
