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

void Worker(int id)
{
    unique_lock<mutex> lk(m);
    cv.wait(lk, [] { return i == 1; });
    Print("Повідомлення з потоку " + to_string(id));
}

void Notify()
{
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lk(m);
        i = 1;
    }
    cv.notify_one();
    Print("Notify: надіслано notify_one()");
}

int main()
{
    thread t1(Worker, 1), t2(Worker, 2), t3(Worker, 3);
    t1.detach(); t2.detach(); t3.detach();   // два потоки ніколи не прокинуться
    thread n(Notify);
    n.join();
    this_thread::sleep_for(chrono::milliseconds(300)); // час на вивід потоку, що прокинувся
    return 0;
}
