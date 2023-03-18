#!/bin/sh
TEST_SRC=(
    "tests/setup_date.c"
    "tests/setup_full_date.c"
    )

TEST_EXEC=(
    "tests/build/setup_date"
    "tests/build/setup_full_date"
    )


TEST_SRC_LEN="${#TEST_SRC[@]}"

for (( j=0; j<"${TEST_SRC_LEN}"; j++));
do
    gcc "${TEST_SRC[$j]}" -o "${TEST_EXEC[$j]}"
    ./"${TEST_EXEC[$j]}" &
    wait
done
