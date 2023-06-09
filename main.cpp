#include <iostream>
#include <string>
#include <memory>
#include "Thread.hpp"

int main (int argc, char* argv[]) {
    std::unique_ptr<Thread> mainThread = std::make_unique<Thread>(argv);
    return 0;
}