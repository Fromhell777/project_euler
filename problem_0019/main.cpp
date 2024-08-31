#include "timer.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include "date.h"

int main () {

  using namespace date;
  weekday target_day{sun};
  year_month_day startdate{jan/1/1901};
  year_month_day enddate{dec/31/2000};
  long result = 0;

  {
    timer Timer;

    while (startdate <= enddate) {
      if (weekday{startdate} == target_day) {
        ++result;
      }
      startdate += months{1};
    }
  }

  std::cout << "Result: " << result << "\n";
}
