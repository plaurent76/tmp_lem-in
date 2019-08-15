#!/bin/bash

RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
BASE=$(tput sgr0)
GOOD_MAPS=checker/good_maps/*
BAD_MAPS=checker/bad_maps/*

printf ">> ERROR MANAGEMENT\n"
printf "\n>> 1. BAD MAPS\n"
for f in $BAD_MAPS
	do
		if [[ $(./lem-in < $f 2>&1 | grep "Error") ]]
		then
		    printf ">> ${GREEN}OK${BASE} << ${f##*/}\n"
		else
		    printf ">> ${RED}KO${BASE} << ${f##*/}\n"
		fi
	done
printf "\n>> 2. GOOD MAPS\n"
for f in $GOOD_MAPS
	do
		if [[ $(./lem-in < $f 2>&1 | grep "##start") ]]
		then
		    printf ">> ${GREEN}OK${BASE} << ${f##*/}\n"
		else
		    printf ">> ${RED}KO${BASE} << ${f##*/}\n"
		fi
	done
