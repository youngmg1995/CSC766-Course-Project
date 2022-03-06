

// https://web.dev/webassembly-threads/



#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    puts("Before the thread");

    int arg = 42;
    std::thread thread([&]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Inside the thread1: " << arg << std::endl;
    });

    thread.join();

    std::cout << "After the thread" << std::endl;
    exit(0);
    return 0;
}
