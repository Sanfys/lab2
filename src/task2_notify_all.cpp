#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

mutex m, out;
condition_variable cv;
int i = 0;

void Print(const string& s) { lock_guard<mutex> l(out); cout << s << endl; }

void Waits(int id)
{
    unique_lock<mutex> lk(m);
    Print("Потік Waits " + to_string(id) + " входить у стан очікування");
    cv.wait(lk, [] { return i == 1; });
    Print("Потік Waits " + to_string(id) + ": очікування завершене");
}

void Awake()
{
    this_thread::sleep_for(chrono::milliseconds(100));
    Print("Awake: починаю повідомляти решту потоків");
    cv.notify_all();
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lk(m);
        i = 1;
    }
    Print("Awake: повторне повідомлення");
    cv.notify_all();
}

int main()
{
    thread w1(Waits, 1), w2(Waits, 2), w3(Waits, 3);
    thread a(Awake);
    a.join();
    w1.join(); w2.join(); w3.join();
    return 0;
}
