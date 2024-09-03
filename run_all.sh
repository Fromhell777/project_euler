#! /bin/bash -e

usage() {
  echo "run_all version 1.0"
  echo "SYNOPSIS: run_all.sh [-h] [-m] [-r] [-c]"
  echo "          where:"
  echo "             -h  Shows this message."
  echo "             -m  Make all the programs."
  echo "             -r  run all the programs."
  echo "             -c  clean all the programs."
  echo
  echo "DESCRIPTION: Run all the Project Euler problems"
  exit 0
}

# A POSIX variable
OPTIND=1 # Reset in case getopts has been used previously in the shell.

export DO_MAKE=0
export DO_RUN=0
export DO_CLEAN=0

while getopts "hmrc" opt; do
    case "$opt" in
    h)
        usage
        exit 0
        ;;
    m)  export DO_MAKE=1
        echo "Selected to make all the problems"
        ;;
    r)  export DO_RUN=1
        echo "Selected to run all the problems"
        ;;
    c)  export DO_CLEAN=1
        echo "Selected to clean all the problems"
        ;;
    *)
        echo "Error: incorrect arguments"
        usage
        exit 1
        ;;
    esac
done

problems=$(find -maxdepth 1 -name "problem_*")

if [[ $DO_MAKE = 1 ]]; then
  echo ""
  echo "###########################"
  echo "# Making all the problems #"
  echo "###########################"
  for problem in $problems;
  do
    echo ""
    echo "Making problem ${problem##*_}:"
    (cd $problem && make)
  done
fi

if [[ $DO_RUN = 1 ]]; then
  echo ""
  echo "############################"
  echo "# Running all the problems #"
  echo "############################"
  for problem in $problems;
  do
    echo ""
    echo "Problem ${problem##*_}:"
    (cd $problem && ./program)
  done
fi

if [[ $DO_CLEAN = 1 ]]; then
  echo ""
  echo "#############################"
  echo "# Cleaning all the problems #"
  echo "#############################"
  for problem in $problems;
  do
    echo ""
    echo "Cleaning problem ${problem##*_}:"
    (cd $problem && make clean)
  done
fi

if [[ $DO_MAKE = 0 && $DO_RUN = 0 && $DO_CLEAN = 0 ]]; then
  usage
else
  echo ""
  echo "Finished"
fi
