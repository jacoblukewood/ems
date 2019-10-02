#include "utility.h"

namespace utility {
    bool IntervalPassed(unsigned long start_time, unsigned int interval) {
        return (((unsigned long) (millis() - start_time)) >= interval); // TODO: Probably could be cleaned up. Need to test to clean.
    }

    unsigned long TimePassed(unsigned long start_time) {
         return ((unsigned long) (millis() - start_time));
    }
}
