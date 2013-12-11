#!/bin/bash

# Makefile for the SDL Object eXtensions library

# This bash file is used to generate the makefile
# to produce the library for the graphics library
#

cd $(dirname $0)

BINARY_NAME="libslox.a"

obs=()
src=()

function generate_depends {
	# get the dependencies of the dependencies
	next=$(cat $1 | gawk 'match($0, /#include "(.*)"/, m) { print m[1] }')
	deps=$1
	for i in $next ; do
		for canidate in $(generate_depends $i) ; do
			if [[ ! $deps =~ $i ]] && [[ -f $i ]] ; then
				deps="$deps \\$(echo -ne '\n                            ')$i"
			fi
		done
		if [[ $? -ne 0 ]] ; then
			echo "Failed to generate depends">&2
			return 1;
		fi
	done
	echo "$deps"
}

# Iterate through and find the
# c++ source files 
for i in $(find . | egrep '.*\.c(pp|xx)?$') ; do
	# add this file to the list of
	# sources
    echo "Generating from source file: $i"
	deps="$(generate_depends $i)"

	# add the resulting object file to
	# the objects
	src[$cnt]=$deps
	obs+=("obs/`basename $i | sed 's/\.c\(pp\|xx\)\?$/.o/g'`")
	cnt=$[cnt + 1]
done

# remove the Makefile if it exists
rm -f Makefile || true

# open Makefile
exec 3<> Makefile

# some commonly used files to generate
echo 'CPPC?=g++'>&3
echo 'AR?=ar'>&3
echo 'OPTFLAGS?=-g3 -ggdb'>&3
echo "CFLAGS=$CFLAGS -Wall -Wextra -I. "'$(OPTFLAGS)'" -D DEBUG_LEVEL_TRACE -Islox -I../glox">&3
echo "LDFLAGS=$LDFLAGS">&3
echo 'OBJECTS='${obs[@]}>&3
echo 'BINARY='$BINARY_NAME>&3

# Add all, setup and clean rules
echo -e 'all: setup $(OBJECTS)\n\t$(AR) -r $(BINARY) $(OBJECTS)\n'>&3
echo -e 'setup:\n\tmkdir -p obs/\n'>&3
echo -e 'clean:\n\t- rm -rf obs $(BINARY)\n'>&3

# iterate through all of the objects and 
# add a rule for the binary
for ((i=0;i<${#obs[@]};i++)) ; do
    echo "Object file: ${obs[$i]}"
    # add a rule for the new binary
	echo -e "${obs[$i]}: ${src[$i]}\n\t"'$(CPPC) $(CFLAGS) -o $@ -c $<\n'>&3
done

# close Makefile
exec 3>&-
