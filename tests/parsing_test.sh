#!/bin/bash

BLUE="\033[34m"
YELLOW="\033[33m"
GREEN="\033[32m"
RED="\033[31m"
BOLD="\033[1m"
END="\033[0m"

HAS_ERROR=0

VALGRIND_CMD=1
if ! command -v valgrind &> /dev/null; then
	VALGRIND_CMD=0
	echo -e "${YELLOW}valgrind could not be found${END}"
fi
LEAKS_CMD=1
if ! command -v leaks &> /dev/null; then
	LEAKS_CMD=0
	echo -e "${YELLOW}leaks could not be found${END}"
fi
if [ $VALGRIND_CMD -eq 0 ] && [ $LEAKS_CMD -eq 0 ]; then
	echo -e "${YELLOW}no leak tests will be performed${END}"
fi

test_map () {
	echo -en "\tTesting map: ${BLUE}$1${END} "
	OUTPUT_MD5=$(./cube3d -p $2 | md5sum)
	WANTED_MD5=$(echo -e $3 | md5sum)

	if [ $VALGRIND_CMD -eq 1 ]; then
		valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=113 ./cube3d -p $2 >/dev/null 2>&1
		if [ $? -eq 113 ]; then
			echo -en "${YELLOW}Leaks${END} "
			HAS_ERROR=1
		fi
	elif [ $LEAKS_CMD -eq 1 ]; then
		leaks --atExit -- ./cube3d -p $2 >/dev/null 2>&1
		if [ $? -eq 1 ]; then
			echo -en "${YELLOW}Leaks${END} "
			HAS_ERROR=1
		fi
	else
		echo -en "${YELLOW}No leaks check${END} "
	fi


	if [ "$OUTPUT_MD5" != "$WANTED_MD5" ]; then
		HAS_ERROR=1
		OUTPUT=$(./cube3d $2)
		echo -en "${RED}KO${END}"
		echo -en " ${BOLD}Expected:${END} $3"
		echo -e " ${BOLD}Got:${END} $OUTPUT"
	else
		echo -e "${GREEN}OK${END}"
	fi
}

test_map "Non-existent map file" "tests/maps/m0.ok.cub" "Error\n(Unable to open the map file)"
test_map "Correct map" "tests/maps/m1.ok.cub" "MAP OK."
test_map "Correct map with spaces and newline" "tests/maps/m2.ok.cub" "MAP OK."
test_map "Map without ceiling color" "tests/maps/m3.ko.cub" "Error\n(The map does not contain all the textures and colors information)"
test_map "Map content with invalid characters" "tests/maps/m4.ko.cub" "Error\n(The map content contains invalid characters)"
test_map "Map content with empty lines" "tests/maps/m5.ko.cub" "Error\n(The map content contains empty lines)"
test_map "Map content with whitespaces only lines" "tests/maps/m6.ko.cub" "Error\n(The map content contains invalid characters)"
test_map "Map content with spaces only lines" "tests/maps/m7.ko.cub" "Error\n(The map content contains lines with only spaces)"
test_map "Map with two north texture" "tests/maps/m8.ko.cub" "Error\n(You can't set a texture more than once)"
test_map "Map with a texture file that cannot be opened" "tests/maps/m9.ko.cub" "Error\n(Unable to open texture file)"
test_map "Correct map with spaces after and inside texture" "tests/maps/m10.ok.cub" "MAP OK."
test_map "RGB color value over 255" "tests/maps/m11.ko.cub" "Error\n(Color value must be between 0 and 255)"
test_map "4-values color codes" "tests/maps/m12.ko.cub" "Error\n(Invalid RGB color format)"
test_map "RGB color with unauthorized characters" "tests/maps/m13.ko.cub" "Error\n(Invalid RGB color format)"
test_map "Map with two ceiling color" "tests/maps/m14.ko.cub" "Error\n(You can't set a color more than once)"
test_map "Map with multiple player positions" "tests/maps/m15.ko.cub" "Error\n(Map contains multiple positions for the player)"
test_map "Map not closed" "tests/maps/m16.ko.cub" "Error\n(Map is not closed)"
test_map "Empty map content" "tests/maps/m17.ko.cub" "Error\n(The content of the map is empty)"
test_map "Empty map content without every textures/colors" "tests/maps/m18.ko.cub" "Error\n(The map does not contain all the textures and colors information)"
test_map "Empty file" "tests/maps/m19.ko.cub" "Error\n(The map does not contain all the textures and colors information)"

if [ $HAS_ERROR -eq 0 ]; then
	echo -e "${GREEN}All tests passed!${END}"
else
	echo -e "${RED}Some tests failed${END}"
	exit 1
fi
