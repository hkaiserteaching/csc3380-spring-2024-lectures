#include <chrono>
#include <iostream>
#include <thread>

//#include "chrono_io.hpp"

void system_clock()
{
    // Get current time from system_clock, returns a time point
    auto tp1 = std::chrono::system_clock::now();
    std::cout << "The current UTC time is: " << tp1 << "\n";

    // difference of two time points is a duration
    auto tp2 = std::chrono::system_clock::now();
    auto duration = tp2 - tp1;
    std::cout << "Time elapsed between calls: " << duration << "\n";
}

void steady_clock()
{
    // bring in literals from std::chrono
    using namespace std::literals;

    // Same interface as system_clock:
    auto tp1 = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(1ms);    // millisecond literal
    auto tp2 = std::chrono::steady_clock::now();

    auto duration = tp2 - tp1;
    std::cout << "Slept for " << duration << "\n";
    std::cout << "Which is " << (duration - 1ms)
              << " more than the requested duration.\n";
}

void dates()
{
    using namespace std::literals;
    using namespace std::chrono;

    // Day in a year can be specified using literals and operator/
    std::cout << "Christmas 2023 is on a " << weekday(2023y / December / 24d)
              << "\n";

    // Last day for February 2020
    std::cout << "Leap day in 2020: " << year_month_day(2020y / February / last)
              << "\n";

    // Last Sunday of 2023
    year_month_weekday_last last_sunday = 2023y / December / Sunday[last];
    std::cout << "Last Sunday in 2023: " << year_month_day(last_sunday) << "\n";

    // US Thanksgiving in 2024
    auto thanksgiving = November / Thursday[4];
    std::cout << "Thanksgiving in 2024: "
              << year_month_day(thanksgiving / 2024y) << "\n";
}

void time_zones()
{
    using namespace std::literals;
    using namespace std::chrono;

    // Weekly meeting each Wednesday 15:00, as un-zoned time
    auto meeting = local_days{2023y / June / Wednesday[1]} + 15h;
    auto prague = locate_zone("Europe/Prague");
    auto new_york = locate_zone("America/New_York");

    // local_time -> zoned_time: the time is local to this zone
    zoned_time<seconds> local(prague, meeting);
    zoned_time<seconds> remote(new_york, local);        // time zone conversion
    std::cout << "Prague meeting time: " << local << "\n";
    std::cout << "New York meeting time: " << remote << "\n";

    zoned_time<seconds> next_local(prague, meeting + weeks(1));
    zoned_time<seconds> next_remote(new_york, next_local);
    std::cout << "Prague next week's meeting time: " << next_local << "\n";
    std::cout << "New York next week's meeting time: " << next_remote << "\n";
}

int main()
{
    system_clock();
    steady_clock();

    dates();

    time_zones();

    return 0;
}
