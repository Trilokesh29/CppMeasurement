# CppMeasurement

This is sample project to measure time taken for the execution of section of code under triage.

benchmarking::timer tm("MeasuringSection***");

// do someting here

const auto results = tm.get_elapsed_ms();

std::cout << "TIme consumed: " << results << " nanoseconds." << std::endl;

tm.restart() // this resets the start value

// do someting here

const auto results = tm.get_elapsed_ms();
or
tm.print_time_consumed() // this prints the time consumed into standard out along with the identifier.
