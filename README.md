# C_dates
### Stb style library for dates in C.

The library is not intended for any production environments. It was implemented for educational purposes. Mainly to understand how dates work and are being calculated. Inspired by the `Date` class in JavaScript.

### API
#### The `C_DATE` structure
```c
struct {
    C_DATE_MS ms;
    size_t year;
    size_t month;
    size_t day;
    size_t hours;
    size_t minutes;
    size_t seconds;
} C_DATE
```
---
#### Fill `C_DATE` instance with a date information
```c
void C_DATE_set_date(size_t y, size_t m, size_t d, C_DATE* date);
```
##### Example
```c
C_DATE date;
C_DATE_set_date(2004, 9, 16, &date);
```
The date instance will get modified with the passed parameters, plus the milliseconds will be calculated.

---
#### Fill `C_DATE` instance with a date information (including hours, minutes, seconds)
```c
void C_DATE_set_full_date(size_t y, size_t m, size_t d, size_t h, size_t min, size_t s, C_DATE* date);
```
##### Example
```c
C_DATE date;
C_DATE_set_full_date(2004, 9, 16, 10, 19, 0, &date);
```
The date instance will get modified with the passed parameters, plus the milliseconds will be calculated.

---
#### Fill `C_DATE` instance with current date information
```c
void C_DATE_set_current_date(C_DATE* date);
```
##### Example
```c
C_DATE date;
C_DATE_set_current_date(&date);
```
The instance will be modified to represent the current date and time. It uses the `<time.h>` header just to fetch current date in seconds. Everything else is calculated on the fly.

---
#### Fill `C_DATE` instance with 1970/01/01 date.
##### Example
```c
C_DATE date;
C_DATE_set_epoch_date(&date);
```

---
#### Comparing two `C_DATES`
```c
bool C_DATE_cmp_dates(const C_DATE* d1, const C_DATE* d2);
```
##### Example
```c
C_DATE d1;
C_DATE_set_date(2023, 3, 18, &d1);
C_DATE d2;
C_DATE_set_date(2023, 3, 19, &d2);
bool d2_bigger = C_DATE_cmp_dates(&d2, &d1);
```
