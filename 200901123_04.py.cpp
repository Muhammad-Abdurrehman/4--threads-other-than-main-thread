
#include <iostream>
#include <thread>
#include <mutex>
#include <exception>

std::mutex m;
std::string str;
bool input_done = false;

void input_thread()
{
std::cout << "Enter a string: ";
std::getline(std::cin, str);
m.lock();
input_done = true;
m.unlock();
}

void reverse_thread()
{
m.lock();
while (!input_done)
{
m.unlock();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m.lock();
}
m.unlock();
std::string rev_str;
for (int i = str.length() - 1; i >= 0; i--)
rev_str += str[i];
std::cout << "Reverse string: " << rev_str << std::endl;
}

void capital_thread()
{
m.lock();
while (!input_done)
{
m.unlock();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m.lock();
}
m.unlock();
std::string cap_str;
for (int i = 0; i < str.length(); i++)
cap_str += toupper(str[i]);
std::cout << "Capitalized string: " << cap_str << std::endl;
}

void shift_thread()
{
m.lock();
while (!input_done)
{
m.unlock();
std::this_thread::sleep_for(std::chrono::milliseconds(100));
m.lock();
}
m.unlock();
std::string shift_str;
for (int i = 0; i < str.length(); i++)
shift_str += str[i] + 2;
std::cout << "Shifted string: " << shift_str << std::endl;
}

int main()
{
try
{
std::thread t1(input_thread);
std::thread t2(reverse_thread);
std::thread t3(capital_thread);
std::thread t4(shift_thread);
t1.join();
t2.join();
t3.join();
t4.join();
}
catch (const std::exception& e)
{
std::cerr << "Error: " << e.what() << std::endl;
return 1;
}
return 0;
}



