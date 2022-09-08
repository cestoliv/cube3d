#!/bin/bash

BLUE="\033[34m"
YELLOW="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
BOLD="\033[1m"
END="\033[0m"

HAS_ERROR=0

test_map () {
	echo -en "\tTesting map ${BLUE}$1${END} "
	OUTPUT=$(./cube3d $1)
	if [ "$OUTPUT" != "$2" ]; then
		HAS_ERROR=1
		echo -en "${RED}KO${END}"
		echo -en " ${BOLD}Expected:${END} $2"
		echo -e " ${BOLD}Got:${END} $OUTPUT"
	else
		echo -e "${GREEN}OK${END}"
	fi
}

test_map "tests/maps/m1.ok.cub" "MAP OK."
test_map "tests/maps/m2.ok.cub" "MAP OK."
test_map "tests/maps/m3.ko.cub" "Error. (The map does not contain all the texture information.)"

if [ $HAS_ERROR -eq 0 ]; then
	echo -e "${GREEN}All tests passed!${END}"
else
	echo -e "${RED}Some tests failed${END}"
	exit 1
fi
