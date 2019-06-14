#! bin/sh

EXE="wolf3d"
TEST="unit-tests"
SCRIPT="unit-tests.sh"
DIRECTORY="42-Wolf3D"

function usage()
{
	echo "\nusage: sh $SCRIPT 'options'\n\n\tAvailable options :"
	echo "\n\t--debug   : Launch the program with a valid map"
	echo "\t--help    : Display informations about the script"
	# echo "\t--hard    : Add few more test to go through"
	# echo "\t--verbose : Display information during errors analysis"
}

if [ "$1" == "--debug" ]; then
	./$EXE $TEST/wolf.w3d
elif [ "$1" == "--help" ]; then
	usage
else
	echo "--- Error tests (Wolf3D) ---\n"
	echo "Wrong directory"
	cd ..
	./$DIRECTORY/$EXE $TEST/00
	cd $DIRECTORY
	echo "\nWrong filename"
	./$EXE $TEST/00
	echo "\nInexistant file"
	./$EXE $TEST/000.w3d
	echo "\nDirectory"
	./$EXE $TEST/00.w3d
	echo "\nEmpty file"
	./$EXE $TEST/01.w3d
	echo "\nUnequal width"
	./$EXE $TEST/02.w3d
	./$EXE $TEST/03.w3d
	echo "\nNo spawnable room"
	./$EXE $TEST/04.w3d
	echo "\nUnounded map"
	./$EXE $TEST/05.w3d
	./$EXE $TEST/06.w3d
	./$EXE $TEST/07.w3d
	./$EXE $TEST/08.w3d
	./$EXE $TEST/09.w3d
	./$EXE $TEST/10.w3d
	./$EXE $TEST/11.w3d
	./$EXE $TEST/12.w3d
	echo "\nIncorrect format"
	./$EXE $TEST/13.w3d
	./$EXE $TEST/14.w3d
	echo "\nReading rights"
	./$EXE $TEST/15.w3d
	if [ "$1" == "--hard" ]; then
		echo "\nHard tests"
		./$EXE /dev/random
		./$EXE /dev/urandom
		./$EXE /dev/null
	fi
fi
