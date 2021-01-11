#!/bin/bash
# clear
tput sgr0

red=$(tput setaf 1)
green=$(tput setaf 2)
warning=$(tput setaf 3)
files=$(tput setaf 6)
reset=$(tput sgr0)
toend=$(tput hpa $(tput cols))$(tput cub 9)

return_code=0

prog_name=$1
if [[ -z $prog_name || ! -f $prog_name ]]; then
    echo -en "  File ${prog_name} not found${warning}${toend}[SKIPPING]\n${reset}"
    exit 0
fi

pos_dir="./func_tests/pos"
pos_files_format="pos_*_in.txt"
neg_dir="./func_tests/neg"
neg_files_format="neg_*_in.txt"
result_file="./out/.res.txt"

echo -e "TESTING BEGIN\n\n"
echo -en "  Positive tests ${prog_name} :\n${reset}\n"

function run_tests()
{
    local program_name=$1
    local tests_dir=$2
    local test_file_name_format=$3
    local res_file=$4
    local return_code=$5
    local passed=0

    for file_in in `find ${func_dir} -type f -name ${test_file_name_format} | sort -u`;
    do
        > $res_file

        file_arg=${file_in/in/arg}
        file_out=${file_in/in/out}

        cat $file_arg | xargs $program_name > $res_file
        rc=$?

        if (cmp -s $file_out $res_file) &&
        ((  ( $return_code != 0 ) &&  ( $rc != 0 ) || ( $return_code == 0 ) && ( $rc == 0 ) ))
        then
            ((passed+=1))
            echo -en "  ${green}${file_in}${toend}[OK]\n${reset}"
        else
            echo -en "  ${red}${file_in}${toend}[ERROR]\n${reset}"
        fi
    done

    return $passed
}

touch $result_file

pos_tests=`find ${pos_dir} -name ${pos_files_format} | wc -l`

run_tests $prog_name $pos_dir $pos_files_format $result_file 0
passed_tests=$?

if [ "$pos_tests" = "$passed_tests" ]; then
    echo -en "\n\t${green}Passed ${passed_tests} of ${pos_tests}${toend}[SUCCESS]\n${reset}\n"
else
    echo -en "\n\t${red}Passed ${passed_tests} of ${pos_tests}${toend}[FAILURE]\n${reset}\n"
    ((return_code+=1))
fi

echo -en "  Negative tests ${prog_name} :\n${reset}\n"

neg_tests=`find ${neg_dir} -name ${neg_files_format} | wc -l`

run_tests $prog_name $neg_dir $neg_files_format $result_file 1
passed_tests=$?

if [ "$neg_tests" = "$passed_tests" ]; then
    echo -en "\n\t${green}Passed ${passed_tests} of ${neg_tests}${toend}[SUCCESS]\n${reset}\n"
else
    echo -en "\n\t${red}Passed ${passed_tests} of ${neg_tests}${toend}[FAILURE]\n${reset}\n"
    ((return_code+=1))
fi

rm $result_file

echo -e "\nTESTING END\n\n"

exit $return_code
