#define C_DATE_IMPL
#include "../c_dates.h"

#include <stdio.h>
#include <assert.h>

int main(void) {
    C_DATE d;
    C_DATE_set_epoch_date(&d);
    assert(d.year == 1970 && d.ms == 0);
    printf("Setting epoch date PASSED\n");
    return 0;
}
