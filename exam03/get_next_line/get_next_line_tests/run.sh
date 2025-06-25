#!/bin/bash

GREEN='\033[1;32m'
YELLOW='\e[1;33m'
PURPLE='\e[1;35m'
NO_COLOR='\033[0m'

echo -e "\n${GREEN}Running Norminette${NO_COLOR}"
cd src && \
# norminette && \

echo -e "\n${GREEN}Compiling the test program with ${YELLOW}BUFFER_SIZE = 1${NO_COLOR}"
cd ../tests && \
make clean && \
make BUFFER_SIZE=1 && \

echo -e "${GREEN}Running Valgrind tests...${NO_COLOR}"
make leakfull && \

echo -e "\n${GREEN}Compiling the test program with ${YELLOW}BUFFER_SIZE = 10${NO_COLOR}"
make clean && \
make BUFFER_SIZE=10 && \

echo -e "${GREEN}Running Valgrind tests...${NO_COLOR}"
make leakfull && \

echo -e "\n${GREEN}Compiling the test program with ${YELLOW}BUFFER_SIZE = 1000000${NO_COLOR}"
make clean && \
make BUFFER_SIZE=1000000 && \

echo -e "${GREEN}Running Valgrind tests...${NO_COLOR}"
make leakfull

# echo -e "\n${GREEN}Compiling the ${PURPLE}bonus ${GREEN}test program with ${YELLOW}BUFFER_SIZE = 1${NO_COLOR}"
# cd ../tests && \ 
# make clean && \
# make bonus BUFFER_SIZE=1 && \

# echo -e "${GREEN}Running Valgrind bonus tests...${NO_COLOR}"
# make leakfullbonus && \

# echo -e "\n${GREEN}Compiling the ${PURPLE}bonus ${GREEN}test program with ${YELLOW}BUFFER_SIZE = 10${NO_COLOR}"
# make clean && \
# make bonus BUFFER_SIZE=10 && \

# echo -e "${GREEN}Running Valgrind bonus tests...${NO_COLOR}"
# make leakfullbonus && \

# echo -e "\n${GREEN}Compiling the ${PURPLE}bonus ${GREEN}test program with ${YELLOW}BUFFER_SIZE = 1000000${NO_COLOR}"
# make clean && \
# make bonus BUFFER_SIZE=1000000 && \

# echo -e "${GREEN}Running Valgrind tests...${NO_COLOR}"
# make leakfullbonus && \

# echo -e "\n${GREEN}Running Francinette tests...${NO_COLOR}"
# cd ../src && \
# ~/francinette/tester.sh && \

# echo -e "\n${GREEN}All tasks completed successfully!${NO_COLOR}"
