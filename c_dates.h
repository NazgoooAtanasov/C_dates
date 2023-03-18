#ifndef C_DATE_H
#define C_DATE_H

#include <stdlib.h>

typedef long long C_DATE_MS;

typedef struct _c_date_str {
    C_DATE_MS ms;
    size_t year;
    size_t month;
    size_t day;
    size_t hours;
    size_t minutes;
    size_t seconds;
} C_DATE;

void C_DATE_set_date(size_t y, size_t m, size_t d, C_DATE* date);
void C_DATE_set_full_date(size_t y, size_t m, size_t d, size_t h, size_t min, size_t s, C_DATE* date);

#ifdef C_DATE_IMPL

#define C_DATE_UNIX_EPOCH_Y_START 1970
#define C_DATE_SECONDS_IN_DAY 24 * 60 * 60
#define C_DATE_DAYS_IN_YEAR_NO_LEAP 365

#define C_DATE_SEC_MS 1000;
#define C_DATE_MIN_MS 60 * C_DATE_SEC_MS
#define C_DATE_HOUR_MS 60 * C_DATE_MIN_MS

void C_DATE_set_date(size_t y, size_t m, size_t d, C_DATE* date) {
    // This only works for years that are after the EPOCH start.
    // @TODO: check how to handle years before EPOCH start.
    size_t passed_years_since_epoch = y - C_DATE_UNIX_EPOCH_Y_START;
    size_t leap_years_days = passed_years_since_epoch / 4;
    size_t passed_days_since_epoch = (passed_years_since_epoch * C_DATE_DAYS_IN_YEAR_NO_LEAP) + leap_years_days;

    date->ms = (passed_days_since_epoch * C_DATE_SECONDS_IN_DAY) * 1000; // to this point we have calculated just the year in ms.

    size_t passed_days_of_current_year = d;
    for (size_t i = 1; i <= m - 1; ++i) {
        if (i == 2) {
            passed_days_of_current_year += y % 2 == 0 && y % 4 == 0 ? 29 : 28;
            continue;
        }

        passed_days_of_current_year += i % 2 == 0 ? 30 : 31;
    }

    date->ms += (passed_days_of_current_year * C_DATE_SECONDS_IN_DAY) * 1000; // adding the passed days in current year based on the provided month as param.

    date->year = y;
    date->month = m;
    date->day = d;
}

void C_DATE_set_full_date(size_t y, size_t m, size_t d, size_t h, size_t min, size_t s, C_DATE* date) {
    C_DATE_set_date(y, m, d, date);

    size_t hours_in_ms = h * C_DATE_HOUR_MS;
    size_t min_in_ms = min * C_DATE_MIN_MS;
    size_t sec_in_ms = s * C_DATE_SEC_MS;

    date->ms += hours_in_ms + min_in_ms + sec_in_ms;
    date->hours = h;
    date->minutes = min;
    date->seconds = s;
}

#endif

#endif
