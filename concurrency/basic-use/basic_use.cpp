#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::endl;
using std::mutex;
using std::quoted;
using std::string;
using std::thread;
using namespace std::chrono_literals;

mutex display_mutex;

class Foo {
public:
    Foo() = default;
    /*  If the copy constructor is deleted then it won't be defined.
        Therefore the class can't be used as an argument to a thread.
        Foo(const Foo&) = delete; 
    */
    Foo(const Foo&) = default;
};

void worker(int n, std::string str ) {
    cout << "n: " << n << ", str: " << quoted(str) << endl;
}
void foo_worker(Foo foo) {
}
void move_worker() {
}

void ShowThreadIdWorker() {
    thread::id this_id = std::this_thread::get_id();
    display_mutex.lock();
    cout << "thread " << this_id << " sleeping..." << endl;
    display_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void SwapWorker() {
    std::this_thread::sleep_for(std::chrono::duration(2s));
}


using timepoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

int main() {
    int n = 14;
    string str("14");
    thread t(worker, n, str);
    t.join();
    Foo foo;
    thread fooWorker(foo_worker, foo);
    fooWorker.join();

    // t0 will exit immediately and we don't have to wait for it.
    // The thread function execution will resume in t1.
    // Thus we only need to join and wait t1.
    thread t0(move_worker);
    thread t1(std::move(t0));
    t1.join();

    // Testing the id of threads;
    thread thrdA(ShowThreadIdWorker);
    thread::id aId = thrdA.get_id();
    thread thrdB(ShowThreadIdWorker);
    thread::id bId = thrdB.get_id();

    display_mutex.lock();
    cout << "thrdA's id: " << aId << endl;
    cout << "thrdB's id: " << bId << endl;    
    display_mutex.unlock();

    thrdA.join();
    thrdB.join();

    cout << "Start sleep." << endl;
    timepoint start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(std::chrono::duration(2s));
    timepoint end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::milli> elapsed = end - start;
    cout << "Slept for: " << elapsed.count() << endl;

    thread swapThread1(SwapWorker);
    thread swapThread2(SwapWorker);

    cout << "swap thread 1 id: " << swapThread1.get_id() << endl;
    cout << "swap thread 2 id: " << swapThread2.get_id() << endl;
    std::swap(swapThread1,swapThread2);
    cout << "swap thread 1 id: " << swapThread1.get_id() << endl;
    cout << "swap thread 2 id: " << swapThread2.get_id() << endl;
    swapThread1.swap(swapThread2);
    cout << "swap thread 1 id: " << swapThread1.get_id() << endl;
    cout << "swap thread 2 id: " << swapThread2.get_id() << endl;
    swapThread1.join();
    swapThread2.join();
    return EXIT_SUCCESS;
}
