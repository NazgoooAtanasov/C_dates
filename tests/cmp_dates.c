#define C_DATE_IMPL
#include "../c_dates.h"

#include <stdio.h>
#include <assert.h>

int main(void) {
    C_DATE d1;
    C_DATE_set_date(2023, 3, 18, &d1);
    C_DATE d2;
    C_DATE_set_date(2023, 3, 19, &d2);

    bool d2_bigger = C_DATE_cmp_dates(&d2, &d1);
    assert(d2_bigger);

    bool d1_bigger = C_DATE_cmp_dates(&d1, &d2);
    assert(!d1_bigger);

    printf("CMP dates PASSED\n");
    return 0;
}
