#pragma once
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


template <auto...>
struct Timer
{
      Timer (...) {}
};


template <bool run>
class Timer <run> {
public:
      
//       clears the timer
      
      constexpr Timer(const char* msg)  : m_msg(msg), m_start(system_clock::time_point::min()) {
            Start();
      }
      
      
      
      
      
//      Timer(unsigned long& time) : m_time(time), m_start(system_clock::time_point::min()) {
//            Start();
//      }
      
      
      
      ~Timer(){
//            m_time += GetMs();
            cout << m_msg << ": " << GetMs() << " ms" << endl;
      }
      
      // clears the timer
      void Clear(){
            m_start = system_clock::time_point::min();
      }
      
      // returns true if the timer is running
      bool IsStarted() const{
            return (m_start != system_clock::time_point::min());
      }
      
      // start the timer
      void Start(){
            m_start = std::chrono::system_clock::now();
      }
      
      // get the number of milliseconds since the timer was started
      unsigned long GetMs(){
            if (IsStarted()) {
                  system_clock::duration diff;
                  diff = system_clock::now() - m_start;
                  return (unsigned) (duration_cast<milliseconds>(diff).count());
            }
            return 0;
      }
      
private:
      std::chrono::system_clock::time_point m_start;
      const char* m_msg;
//      unsigned long& m_time;
};







template <>
struct Timer <false> {
      Timer (...){}
};

//template <>
//struct Timer <> {
//      Timer (...) {}
//};



#define PH_TIMER_LOOP(x, y, ...) \
for(Starter<__VA_ARGS__> __o = {x, std::string(__FILE_NAME__).append("::" + std::to_string(__LINE__).append(" ").append(y)).c_str()}; __o < x; ++__o)

namespace {
template<bool...>
struct Starter;
//{
//
//      Starter (...) {}
//      bool operator< (int i) {
//            return false;
//      }
//      Starter& operator++ ()
//      {
//            return *this;
//      }
//};

template <bool run>
struct Starter <run> : Timer<run> {
      int max;
      int i;
      
      
      
      Starter(int max, char const* msg) requires (run) : i (0), max (max), Timer<run> (msg) { }
      Starter(int max, char const* msg) requires (!run) : i (max), max (max), Timer<run> () { }
      
      
      ~Starter() {  }
      bool operator< (int n) {
            return i < n;
      }
      Starter<run>& operator++ ()
      {
            ++i;
            return *this;
      }
      friend ostream& operator<< (ostream& os, Starter& s) {
            os << s.i;
            return os;
      }
};


template<>
struct Starter <> : Starter <true>
{
      Starter (auto&& ... i) : Starter<true>(i...){}
};
}