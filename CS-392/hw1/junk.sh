#######################################################################################################################
# Name          : junk.sh
# Author        : Jack Harrington
# Date          : February 4, 2022
# Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
# Description   : Creates a junk directory and moves files with similar function to the recycle bin.
#######################################################################################################################

#!/bin/bash

# prints the usage statement for junk.sh
usage() {
    echo "Usage: $0 [-hlp] [list of files]
                    -h: Display help. 
                    -l: List junked files.
                    -p: Purge all files.
                    [list of files] with no other arguments."
}

# checks if .junk exists and makes it if it does not
junk_exists() {
    if [[ -d "~/.junk" ]]
    then 
        exit 0
    else
        mkdir ~/.junk
    fi
}

while getopts ":hlp" options; do                    # include the : in order to stop system error calling 
    if [[ $# -gt 1 ]]                               # checks if the number of args is greater than 1
    then
        echo "Error: Too many options enabled."
        usage
        exit
    fi
        case "${options}" in
            h)  
                usage
                ;;
            l)
                # cd ~/.junk
                # ls -lAF 
                echo "List files in the recycle bin"
                ;;
            p) 
                # rm ~/.junk
                echo "Purge files in the recycle bin"
                ;;
            *)  
                echo "Error: Unknown option '$1'."    # this case handles an unknown flag after execution statement.
                usage
                ;;
    esac
done










