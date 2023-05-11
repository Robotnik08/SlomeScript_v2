#include <iostream>
#include <string>
#include <memory>
#include "Thread.hpp"

using namespace std;

int main (int argc, char* argv[]) {
    unique_ptr<Thread> mainThread(new Thread(argv));
    return 0;
}