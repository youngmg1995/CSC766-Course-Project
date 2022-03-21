

// https://web.dev/webassembly-threads/



#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

#define TYPE int

void foo1(TYPE arr[], int size){
    //this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Inside the thread1: ";
    for(int i=0;i<size;i++)
        cout<< "th1: "<< arr[i] << " ";
    cout<<endl;
}

void foo2(TYPE arr[], int size){
    //this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Inside the thread2: ";
    for(int i=0;i<size;i++)
        cout<< "th2: "<< arr[i] << " ";
    cout<<endl;
}

int main()
{
    puts("Before the thread");

    int arg = 42;
    TYPE arr[16] = {5,0,0,3,1,1,3,0,1,0,0,1,3,1,1,0};
    int size =16;
    //std::thread thread([&]() {
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
    //    std::cout << "Inside the thread1: " << arg << std::endl;
    //});
    thread th1(foo1,arr,size);
    thread th2(foo2,arr,size);
    th2.join();
    th1.join();

    std::cout << "After the thread" << std::endl;
    exit(0);
    return 0;
}
