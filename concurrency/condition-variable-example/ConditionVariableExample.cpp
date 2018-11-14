#include "MyManagedObject.h"
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

using std::condition_variable;
using std::cout;
using std::function;
using std::mutex;
using std::ref;
using std::reference_wrapper;
using std::thread;
using std::unique_lock;
using std::vector;

using ProducerQueue = vector<unsigned int>;

void ThreadTask(
    reference_wrapper<condition_variable> condition,
    reference_wrapper<mutex> queueMutex,
    reference_wrapper<ProducerQueue> queueRef,
    reference_wrapper<bool> die)
{
    ProducerQueue& queue{ queueRef.get() };

    while (!die.get() || queue.size())
    {
        unique_lock<mutex> lock{ queueMutex.get() };

        function<bool()> predicate{
            [&queue]()
            {
                return !queue.empty();
            }
        };
        condition.get().wait(lock, predicate);

        unsigned int numberToCreate{ queue.back() };
        queue.pop_back();

        cout << "Creating " <<
            numberToCreate <<
            " objects on thread " <<
            std::this_thread::get_id() << std::endl;

        for (unsigned int i = 0; i < numberToCreate; ++i)
        {
            MyManagedObject* pObject{ new MyManagedObject(i) };
        }
    }
}

int main() {
    condition_variable condition;
    mutex queueMutex;
    ProducerQueue queue;
    bool die{ false };

    thread myThread1{ ThreadTask, ref(condition), ref(queueMutex), ref(queue), ref(die) };
    thread myThread2{ ThreadTask, ref(condition), ref(queueMutex), ref(queue), ref(die) };

    queueMutex.lock();
    queue.emplace_back(300000);
    queue.emplace_back(400000);
    queueMutex.unlock();

    condition.notify_all();

    std::this_thread::sleep_for( std::chrono::milliseconds(10) );
    while (!queueMutex.try_lock())
    {
        cout << "Main waiting for queue access!" << std::endl;
        std::this_thread::sleep_for( std::chrono::milliseconds(100) );
    }

    queue.emplace_back(100000);
    queue.emplace_back(200000);

    std::this_thread::sleep_for( std::chrono::milliseconds(1000) );

    condition.notify_one();

    std::this_thread::sleep_for( std::chrono::milliseconds(1000) );

    condition.notify_one();

    std::this_thread::sleep_for( std::chrono::milliseconds(1000) );

    queueMutex.unlock();

    die = true;

    cout << "main waiting for join!" << std::endl;

    myThread1.join();
    myThread2.join();

    return EXIT_SUCCESS;
}
