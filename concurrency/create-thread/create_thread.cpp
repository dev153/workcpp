#include <cstdlib>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

void ThreadTask() {
    for ( unsigned int i{0}; i < 20; ++i ) {
        cout << "Output from thread" << endl;        
    }
}

int main() {
    const unsigned int numberOfCores { std::thread::hardware_concurrency()};
    if ( 1 < numberOfCores ) {
        std::thread myThread{ThreadTask};
        cout << "Output from main" << endl;
        myThread.join();
    } else {
        cout << "CPU does not have multiple cores." << endl;
    }   
    return EXIT_SUCCESS;
}