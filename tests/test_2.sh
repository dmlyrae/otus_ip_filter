#!/bin/bash

EXECUTABLE_PATH=$1

if [ -z "$EXECUTABLE_PATH" ]; then
    echo "Usage: $0 <path_to_executable>"
    exit 1
fi

TEST_DATA="1.1.1.1	111	0
1.2.1.1	222	0
1.10.1.1	333	0
46.70.1.1	444	0
46.70.2.2	555	0
46.1.1.1	666	0
2.46.1.1	777	0
10.1.1.1	888	0"

ACTUAL_OUTPUT=$(echo "$TEST_DATA" | "$EXECUTABLE_PATH")

if [ -z "$ACTUAL_OUTPUT" ]; then
    echo "Test 2: Failed - no output"
    exit 1
fi

FIRST_LINE=$(echo "$ACTUAL_OUTPUT" | head -n 1)
if [ "$FIRST_LINE" != "46.70.2.2" ]; then
    echo "Test 2: Failed - incorrect sorting"
    echo "Expected first line: 46.70.2.2"
    echo "Got: $FIRST_LINE"
    exit 1
fi

SORTED_LINES=$(echo "$ACTUAL_OUTPUT" | head -n 8)
EXPECTED_SORTED="46.70.2.2
46.70.1.1
46.1.1.1
10.1.1.1
2.46.1.1
1.10.1.1
1.2.1.1
1.1.1.1"

if [ "$SORTED_LINES" != "$EXPECTED_SORTED" ]; then
    echo "Test 2: Failed - incorrect sorting order"
    echo "Expected:"
    echo "$EXPECTED_SORTED"
    echo "Got:"
    echo "$SORTED_LINES"
    exit 1
fi

FILTER_1_COUNT=$(echo "$ACTUAL_OUTPUT" | grep -c "^1\." || true)
if [ "$FILTER_1_COUNT" -lt 3 ]; then
    echo "Test 2: Failed - missing IPs starting with 1"
    echo "Expected at least 3, got: $FILTER_1_COUNT"
    exit 1
fi

FILTER_46_70_COUNT=$(echo "$ACTUAL_OUTPUT" | grep -c "^46\.70\." || true)
if [ "$FILTER_46_70_COUNT" -lt 2 ]; then
    echo "Test 2: Failed - missing IPs 46.70.x.x"
    echo "Expected at least 2, got: $FILTER_46_70_COUNT"
    exit 1
fi

FILTER_46_COUNT=$(echo "$ACTUAL_OUTPUT" | grep -E "(^46\.|\.46\.)" | wc -l)
if [ "$FILTER_46_COUNT" -lt 4 ]; then
    echo "Test 2: Failed - missing IPs with byte 46"
    echo "Expected at least 4, got: $FILTER_46_COUNT"
    exit 1
fi

echo "Test 2: IP filter functionality test passed"
exit 0
