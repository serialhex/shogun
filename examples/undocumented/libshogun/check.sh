#!/bin/bash

rm -f error.log

test -n "$LIBRARY_PATH" && LIBRARY_PATH="LIBRARY_PATH=${LIBRARY_PATH}"
test -n "$LIB_PATH" && LIB_PATH="LIB_PATH=${LIB_PATH}"
test -n "$INC_PATH" && INC_PATH="INC_PATH=${INC_PATH}"
test -n "$LIBS" && LIBS="LIBS=${LIBS}"
test -n "$INCLUDES" && INCLUDES="INCLUDES=${INCLUDES}"

for e in `make print_targets | grep -v ^make`
do
	echo -n "running $e .."
	if make "$e" "$LIBRARY_PATH" "$LIB_PATH" "$INC_PATH" "$LIBS" "$INCLUDES" >/dev/null 2>&1 && "./$e" >/dev/null 2>&1
	then
		echo " OK"
	else
		echo " ERROR"
		echo "================================================================================" >>error.log
		echo "error in make $e $LIBRARY_PATH $LIB_PATH $INC_PATH $LIBS" >>error.log
		echo "error in ./$e" >>error.log 2>&1
		echo "================================================================================" >>error.log
		make "$e" "$LIBRARY_PATH" "$LIB_PATH" "$INC_PATH" "$LIBS" >>error.log 2>&1 && "./$e" >>error.log
		echo "================================================================================" >>error.log
		echo >>error.log
		echo >>error.log
	fi
done

if test -f error.log 
then
	cat error.log
	exit 1
fi

exit 0
