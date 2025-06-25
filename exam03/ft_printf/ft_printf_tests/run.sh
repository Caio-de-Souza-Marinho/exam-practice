#!/bin/bash

GREEN='\033[1;32m'
NO_COLOR='\033[0m' # No Color

# Run norminette and rebuild libft in src
echo -e "${GREEN}Running Norminette${NO_COLOR}"
cd src && \
norminette && \

echo -e "\n${GREEN}Rebuilding ft_printf...${NO_COLOR}"
make re && \

echo -e "\n${GREEN}Compiling the test program...${NO_COLOR}"
# Compile the test program
cd ../tests && \
make && \

# Run the tests with Valgrind for memory checking
echo -e "\n${GREEN}Running Valgrind tests...${NO_COLOR}"
make leakfull && \

# Run francinette tests
# echo -e "\n${GREEN}Running Francinette tests...${NO_COLOR}"
# cd ../src && \
# ~/francinette/tester.sh && \

echo -e "\n${GREEN}All tasks completed successfully!${NO_COLOR}"
