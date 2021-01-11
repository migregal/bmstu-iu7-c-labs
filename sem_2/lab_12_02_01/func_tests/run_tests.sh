tput sgr0

red=$(tput setaf 1)
green=$(tput setaf 2)
warning=$(tput setaf 3)
files=$(tput setaf 6)
reset=$(tput sgr0)
toend=$(tput hpa $(tput cols))$(tput cub 9)

echo -e "TESTING BEGIN\n\n"

runs_total=0
runs_successfull=0

prog_name="./app.exe"

if [ -z $prog_name ]; then
    echo -en "  File ${prog_name} not found${warning}${toend}[SKIPPING]\n${reset}"
    continue
    exit 0
fi

touch ./out/.result

echo -en "  Positive tests ${prog_name} :\n${reset}\n"

pos_tests=`find "./func_tests" -name "pos_*_in.txt" | wc -l`
passed_tests=0

for file_in in `find ./func_tests/ -type f -name "pos_*_in.txt" | sort -u`;
do
    > ./out/.result

    file_arg=${file_in/in/arg}
    file_out=${file_in/in/out}


    cat $file_arg | xargs $prog_name
    rc=$?

    if cmp -s $file_out ./out/.result && [[ $rc = 0 ]]
    then
        passed_tests=$((passed_tests + 1))
        echo -en "  ${green}${file_in}${toend}[OK]\n${reset}"
    else
        echo -en "  ${red}${file_in}${toend}[ERROR]\n${reset}"
    fi
done

if [ "$pos_tests" = "$passed_tests" ]; then
    echo -en "\n\t${green}Passed ${passed_tests} of ${pos_tests}${toend}[SUCCESS]\n${reset}\n"
    ((programs_successfull++))
else
    echo -en "\n\t${red}Passed ${passed_tests} of ${pos_tests}${toend}[FAILURE]\n${reset}\n"
fi

echo -en "  Negative tests ${prog_name} :\n${reset}\n"

pos_tests=`find "./func_tests" -name "neg_*_in.txt" | wc -l`
passed_tests=0

for file_in in `find ./func_tests/ -type f -name "neg_*_in.txt" | sort -u`;
do
    > ./out/.result

    file_arg=${file_in/in/arg}
    file_out=${file_in/in/out}

    cat $file_arg | xargs $prog_name
    rc=$?
    if cmp -s $file_out ./out/.result && [[ $rc !=  0 ]]
    then
        passed_tests=$((passed_tests + 1))
        echo -en "  ${green}${file_in}${toend}[OK]\n${reset}"
    else
        echo -en "  ${red}${file_in}${toend}[ERROR]\n${reset}"
    fi
done

rm ./out/.result

if [ "$pos_tests" = "$passed_tests" ]; then
    echo -en "\n\t${green}Passed ${passed_tests} of ${pos_tests}${toend}[SUCCESS]\n${reset}\n"
    ((programs_successfull++))
else
    echo -en "\n\t${red}Passed ${passed_tests} of ${pos_tests}${toend}[FAILURE]\n${reset}\n"
fi

echo -e "\nTESTING END\n\n"

exit 0
