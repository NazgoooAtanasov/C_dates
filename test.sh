#!/bin/sh
TEST_SRC=(
    "tests/setup_date.c"
    "tests/setup_full_date.c"
    "tests/setup_current_date.c"
    "tests/cmp_dates.c"
    "tests/setup_epoch_date.c"
    )

TEST_EXEC=(
    "tests/build/setup_date"
    "tests/build/setup_full_date"
    "tests/build/setup_current_date"
    "tests/build/cmp_dates"
    "tests/build/setup_epoch_date"
    )


TEST_SRC_LEN="${#TEST_SRC[@]}"

for (( j=0; j<"${TEST_SRC_LEN}"; j++));
do
    gcc "${TEST_SRC[$j]}" -o "${TEST_EXEC[$j]}"
    ./"${TEST_EXEC[$j]}" &
    wait
done
