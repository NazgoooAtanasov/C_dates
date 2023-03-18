#define C_DATE_IMPL
#include "../c_dates.h"

#include <stdio.h>
#include <assert.h>

int main(void) {
    C_DATE date;
    C_DATE_set_date(2004, 9, 16, &date);
    assert(date.ms == 1095292800000);
    printf("Setting up specific date PASSED\n");
    return 0;
}
