#!/bin/bash

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
BASE=$(tput sgr0)
GOOD_MAPS=checker/good_maps/*
BAD_MAPS=checker/bad_maps/*

printf ">> LEAK MANAGEMENT\n"
WHAT="lost"
for f in $BAD_MAPS
	do
		printf "\n>> testing ${f##*/}:\n"
		WHERE="$(valgrind --tool=memcheck --leak-check=full ./lem-in 2>&1 < $f | grep $WHAT)"
		res=$(echo "$WHERE" | grep -E 'directly|definitely' | cut -c 14-)
		echo "${res}"
	done
printf "\n>> 2. GOOD MAPS\n"
for f in $GOOD_MAPS
	do
		printf "\n>> testing ${f##*/}:\n"
		WHERE="$(valgrind --tool=memcheck --leak-check=full ./lem-in 2>&1 < $f | grep $WHAT)"
		res=$(echo "$WHERE" | grep -E 'directly|definitely' | cut -c 14-)
		echo "${res}"
	done
