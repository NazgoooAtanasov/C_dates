#define C_DATE_IMPL
#include "../c_dates.h"

#include <stdio.h>
#include <assert.h>

int main(void) {
    C_DATE date;
    C_DATE_set_full_date(2004, 9, 16, 10, 19, 0, &date);
    assert(date.ms == 1095329940000);
    printf("Setting up specific date plus hours, minutes and seconds PASSED\n");
    return 0;
}
