#! /bin/sh
if [[ -z $1 ]]; then
	libtool --mode=execute valgrind --leak-check=full \
		testrunner
else
	libtool --mode=execute valgrind --leak-check=full mmlparser $1
fi

