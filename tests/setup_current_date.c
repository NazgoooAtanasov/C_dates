#define C_DATE_IMPL
#include "../c_dates.h"

#include <stdio.h>
#include <assert.h>

int main(void) {
    C_DATE date;
    C_DATE_set_current_date(&date);
    printf("Current date, %lli Passed\n", date.ms);
}
