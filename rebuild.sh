#!/bin/bash
set -e
clear

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BOLD='\033[1m'
RESET='\033[0m'

echo -e "${BOLD}${YELLOW}[LangtonAnts] Cleaning...${RESET}"
rm -rf build

echo -e "${BOLD}${YELLOW}[LangtonAnts] Configuring...${RESET}"
cmake -S . -B build

echo -e "${BOLD}${YELLOW}[LangtonAnts] Compiling...${RESET}"
cmake --build build

echo -e "${BOLD}${YELLOW}[LangtonAnts] Updating compile_commands...${RESET}"
ln -sf build/compile_commands.json compile_commands.json

clear
echo -e "${BOLD}${GREEN}[LangtonAnts] Executable Ready! (./build/app)${RESET}"