#ifndef C_DATE_H
#define C_DATE_H

#include <stdlib.h>
#include <time.h>

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
void C_DATE_set_current_date(C_DATE* date);

#ifdef C_DATE_IMPL

#define C_DATE_UNIX_EPOCH_Y_START 1970
#define C_DATE_SECONDS_IN_DAY (24 * 60 * 60)
#define C_DATE_DAYS_IN_YEAR_NO_LEAP 365

#define C_DATE_SEC_MS 1000
#define C_DATE_MIN_MS (60 * C_DATE_SEC_MS)
#define C_DATE_HOUR_MS (60 * C_DATE_MIN_MS)

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

void C_DATE_set_current_date(C_DATE* date) {
    C_DATE_MS current_date = time(NULL);
    date->ms = current_date * C_DATE_SEC_MS;

    size_t passed_days_since_epoch = current_date / C_DATE_SECONDS_IN_DAY;
    size_t passed_years_since_epoch = passed_days_since_epoch / C_DATE_DAYS_IN_YEAR_NO_LEAP;
    date->year = C_DATE_UNIX_EPOCH_Y_START + passed_years_since_epoch;

    C_DATE current_year_start;
    C_DATE_set_date(date->year, 1, 0, &current_year_start); // setting the day to `0` since in that case, the current day will never be over

    // @TODO: idk if size_t is okay here.
    size_t current_year_current_day_diff_sec = (date->ms - current_year_start.ms) / 1000;
    size_t passed_days_diff = current_year_current_day_diff_sec / C_DATE_SECONDS_IN_DAY;
    current_year_current_day_diff_sec -= passed_days_diff * C_DATE_SECONDS_IN_DAY;

    size_t month = 1;
    for (size_t i = 1; i <= 12; ++i, month++) {
        size_t to_substract = 31;

        if (i == 2) to_substract = date->year % 4 == 0 ? 29 : 28;
        else if (i % 2 == 0) to_substract = 30;

        if (passed_days_diff < to_substract) break;

        passed_days_diff -= to_substract;
    }

    date->month = month;
    date->day = passed_days_diff + 1; // adding one here since we need to include the current day.

    date->hours = (current_year_current_day_diff_sec / (60*60)) % 24;
    current_year_current_day_diff_sec -= date->hours * (60*60);

    date->minutes = (current_year_current_day_diff_sec / 60) % 60;
    current_year_current_day_diff_sec -= date->minutes * 60;

    date->seconds = current_year_current_day_diff_sec;
}

#endif

#endif
