#include <iostream>
#include <chrono>
#include <thread>

int main() {
    for(int i = 1; i <= 5; i++) //Anzahl der Durchläufe begrenzt
    {
        for (int output = 128; output >= 1; output /= 2)
        {
            std::cout << output << std::endl; //muss durch output zum B15 ersetzt werden
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        
        for (int output = 1; output <= 128; output *= 2)
        {
            std::cout << output << std::endl; //muss durch output zum B15 ersetzt werden
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
}