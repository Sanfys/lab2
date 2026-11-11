#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <deque>
#include <vector>
#include "common.h"
using namespace std;

mutex m;
condition_variable cv;
deque<packaged_task<long long(int)>> tasks;   // завдання
deque<int> numbers;                            // номери n
bool stop = false;

void Worker()
{
    while (true)
    {
        packaged_task<long long(int)> task;
        int n;
        {
            unique_lock<mutex> lk(m);
            cv.wait(lk, [] { return !tasks.empty() || stop; });
            if (tasks.empty()) return;          // stop і завдань немає
            task = move(tasks.front()); tasks.pop_front();
            n = numbers.front();               numbers.pop_front();
        }
        task(n);
    }
}

int main()
{
    thread worker(Worker);
    vector<future<long long>> results;
    vector<int> asked;

    cout << "Введіть n (стоп-символ - будь-який нечисловий символ, наприклад q):" << endl;
    int n;
    while (cin >> n && n > 0)
    {
        packaged_task<long long(int)> task(NthPrime);
        results.push_back(task.get_future());
        asked.push_back(n);
        {
            lock_guard<mutex> lk(m);
            tasks.push_back(move(task));
            numbers.push_back(n);
        }
        cv.notify_one();
    }

    for (size_t k = 0; k < results.size(); ++k)            // очікування всіх завдань
        cout << asked[k] << "-те просте число: " << results[k].get() << endl;

    {
        lock_guard<mutex> lk(m);
        stop = true;
    }
    cv.notify_one();
    worker.join();                                          // коректне завершення потоку
    return 0;
}
