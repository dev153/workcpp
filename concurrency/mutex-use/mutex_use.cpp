#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

using std::cout;
using std::mutex;
using std::thread;

static mutex globalMutex;
static mutex sharedMutex;
static mutex counter_mutex;
static std::chrono::milliseconds interval(50);

static int sharedCounter{0};
static int exclusiveCounter{0};
static int counter{0};

void SimpleMutexWorker(int i) {
    // cout is not thread safe, therefore we need to use a mutex.
    // Only one thread will have access to the cout and use it.
    // Every other thread that tries to access the "cout" will wait
    // until the mutex is released.
    globalMutex.lock();
    cout << "Outputting this from thread number: " << i << "\n";
    globalMutex.unlock();
}

void worker0() {
    std::this_thread::sleep_for(interval);
    while (true) {
        // try to acquire the shared resource mutex.
        if(sharedMutex.try_lock()) {
            // Access to shared resource acquired. Shared resource can be modified...
            cout << "Shared (" << sharedCounter << ")\n";
            sharedMutex.unlock();
            return;
        } else {
            // Lock was not possible to be acquired, but there is additional job to be done in this thread.
            ++exclusiveCounter;
            cout << "Exclusive (" << exclusiveCounter << ")\n";
            std::this_thread::sleep_for(interval);
        }
    }
}

void LockGuardWorker() {
    std::lock_guard<mutex> lock(counter_mutex);
    if ( counter == 1 ) {
        counter += 10;
    } else if ( counter >= 10 ) {
        counter += 15;
    } else if ( counter > 50 ) {
        // The complex is quite simple here and the unlock of the mutex is easily visible.
        // In more complex situations it would require to unlock the mutex at this point
        // before returning from the thread function.
        return;
    } else {
        ++counter;
    }
    cout << std::this_thread::get_id() << ": " << counter << '\n';
}

void worker1() {
    sharedMutex.lock();
    std::this_thread::sleep_for(10*interval);
    ++sharedCounter;
    sharedMutex.unlock();
}

bool is_prime(int x) {
    bool result = true;
    for ( int i{2}; i < x; ++i) {
        if ( x % i == 0 ) {
            result = false;
            break;
        }
    }
    return result;
}

void print_int(std::future<int>& fut) {
    int x = fut.get();
    cout << "value: " << x << '\n';
}

int countdown(int from, int to) {
    for ( int i{from}; i != to; --i) {
        cout << i << '\n';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "Finished countdown.\n";
    return from - to;
}

int main() {
    std::thread t1(SimpleMutexWorker, 1);
    std::thread t2(SimpleMutexWorker, 2);
    t1.join();
    t2.join();
    //=========================================================================
    std::thread t3(worker0);
    std::thread t4(worker1);
    t3.join();
    t4.join();
    //=========================================================================
    cout << __func__ << ": " << counter << '\n';
    thread t5(LockGuardWorker);
    thread t6(LockGuardWorker);
    t5.join();
    t6.join();
    cout << __func__ << ": " << counter << '\n';
    //=========================================================================
    // Future example
    std::future<bool> fut = std::async(is_prime, 444444443);
    cout << "Checking, please wait";
    std::chrono::milliseconds span(100);
    while(fut.wait_for(span) == std::future_status::timeout) {
        cout << '.';
    }
    bool x = fut.get();
    std::cout << "\n444444443 is" << ( x ? "" : " not" ) << " prime.\n";
    //=========================================================================
    // Promise example
    std::promise<int> prom;
    std::future<int> futprom = prom.get_future();
    thread t7(print_int, std::ref(futprom));
    prom.set_value(10);
    t7.join();
    //=========================================================================
    // Packaged Task example
    std::packaged_task<int(int,int)> task(countdown);
    std::future<int> result = task.get_future();
    thread t8(std::move(task), 10, 0);
    int value = result.get();
    cout << "The countdown lasted for " << value << " seconds.\n";
    t8.join();
    return EXIT_SUCCESS;
}
