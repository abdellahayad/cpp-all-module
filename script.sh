#!/bin/bash

# Server Statistics Script
# Analyzes basic server performance metrics

# Color codes for better readability
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to print section headers
print_header() {
    echo -e "\n${BLUE}================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================${NC}"
}

# Function to print subheaders
print_subheader() {
    echo -e "\n${GREEN}$1${NC}"
}

# Clear screen for better presentation
clear

echo -e "${YELLOW}╔════════════════════════════════════════╗${NC}"
echo -e "${YELLOW}║     SERVER PERFORMANCE STATISTICS      ║${NC}"
echo -e "${YELLOW}╚════════════════════════════════════════╝${NC}\n"

# System Information
print_header "SYSTEM INFORMATION"

# OS Version
print_subheader "OS Version:"
if [ -f /etc/os-release ]; then
    . /etc/os-release
    echo "  $PRETTY_NAME"
else
    echo "  $(uname -s) $(uname -r)"
fi

# Hostname
print_subheader "Hostname:"
echo "  $(hostname)"

# Uptime
print_subheader "System Uptime:"
uptime -p 2>/dev/null || uptime | awk '{print "  " $3 " " $4}'

# Load Average
print_subheader "Load Average (1m, 5m, 15m):"
echo "  $(uptime | awk -F'load average:' '{print $2}')"

# CPU Information
print_header "CPU STATISTICS"

# Total CPU Usage
print_subheader "Total CPU Usage:"
cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)
cpu_idle=$(top -bn1 | grep "Cpu(s)" | awk '{print $8}' | cut -d'%' -f1)
cpu_used=$(echo "100 - $cpu_idle" | bc)
echo "  Used: ${cpu_used}%"
echo "  Idle: ${cpu_idle}%"

# CPU Cores
print_subheader "CPU Cores:"
echo "  $(nproc) cores"

# Memory Statistics
print_header "MEMORY STATISTICS"

print_subheader "RAM Usage:"
memory_info=$(free -h | grep Mem)
total_mem=$(echo $memory_info | awk '{print $2}')
used_mem=$(echo $memory_info | awk '{print $3}')
free_mem=$(echo $memory_info | awk '{print $4}')
available_mem=$(echo $memory_info | awk '{print $7}')

# Calculate percentage
total_mem_kb=$(free | grep Mem | awk '{print $2}')
used_mem_kb=$(free | grep Mem | awk '{print $3}')
mem_percentage=$(awk "BEGIN {printf \"%.2f\", ($used_mem_kb/$total_mem_kb)*100}")

echo "  Total:     $total_mem"
echo "  Used:      $used_mem (${mem_percentage}%)"
echo "  Free:      $free_mem"
echo "  Available: $available_mem"

# Swap Usage
print_subheader "Swap Usage:"
swap_info=$(free -h | grep Swap)
total_swap=$(echo $swap_info | awk '{print $2}')
used_swap=$(echo $swap_info | awk '{print $3}')
free_swap=$(echo $swap_info | awk '{print $4}')

if [ "$total_swap" != "0B" ]; then
    total_swap_kb=$(free | grep Swap | awk '{print $2}')
    used_swap_kb=$(free | grep Swap | awk '{print $3}')
    if [ "$total_swap_kb" -gt 0 ]; then
        swap_percentage=$(awk "BEGIN {printf \"%.2f\", ($used_swap_kb/$total_swap_kb)*100}")
    else
        swap_percentage="0.00"
    fi
    echo "  Total: $total_swap"
    echo "  Used:  $used_swap (${swap_percentage}%)"
    echo "  Free:  $free_swap"
else
    echo "  No swap configured"
fi

# Disk Usage
print_header "DISK STATISTICS"

print_subheader "Disk Usage by Partition:"
df -h | grep -E '^/dev/' | awk '{printf "  %-20s Total: %-8s Used: %-8s Free: %-8s Usage: %s\n", $1, $2, $3, $4, $5}'

# Overall root partition
print_subheader "Root Partition (/):"
root_info=$(df -h / | tail -1)
echo "  Total: $(echo $root_info | awk '{print $2}')"
echo "  Used:  $(echo $root_info | awk '{print $3}') ($(echo $root_info | awk '{print $5}'))"
echo "  Free:  $(echo $root_info | awk '{print $4}')"

# Top 5 Processes by CPU
print_header "TOP 5 PROCESSES BY CPU USAGE"
echo ""
printf "  %-8s %-8s %-8s %-s\n" "PID" "USER" "CPU%" "COMMAND"
echo "  ───────────────────────────────────────────────────────────"
ps aux --sort=-%cpu | head -6 | tail -5 | awk '{printf "  %-8s %-8s %-8s %-s\n", $2, $1, $3, $11}'

# Top 5 Processes by Memory
print_header "TOP 5 PROCESSES BY MEMORY USAGE"
echo ""
printf "  %-8s %-8s %-8s %-s\n" "PID" "USER" "MEM%" "COMMAND"
echo "  ───────────────────────────────────────────────────────────"
ps aux --sort=-%mem | head -6 | tail -5 | awk '{printf "  %-8s %-8s %-8s %-s\n", $2, $1, $4, $11}'

# Logged in Users
print_header "USER INFORMATION"

print_subheader "Currently Logged In Users:"
who_output=$(who | wc -l)
if [ "$who_output" -gt 0 ]; then
    who | awk '{printf "  %-12s %-12s %s\n", $1, $2, $3" "$4}'
else
    echo "  No users currently logged in"
fi

# Failed Login Attempts (last 10)
print_subheader "Recent Failed Login Attempts:"
if [ -f /var/log/auth.log ]; then
    failed_logins=$(grep "Failed password" /var/log/auth.log 2>/dev/null | tail -10 | wc -l)
    echo "  Last 10 failed attempts: $failed_logins"
    if [ "$failed_logins" -gt 0 ]; then
        grep "Failed password" /var/log/auth.log 2>/dev/null | tail -5 | awk '{print "    " $1" "$2" "$3" - "$9" from "$11}'
    fi
elif [ -f /var/log/secure ]; then
    failed_logins=$(grep "Failed password" /var/log/secure 2>/dev/null | tail -10 | wc -l)
    echo "  Last 10 failed attempts: $failed_logins"
    if [ "$failed_logins" -gt 0 ]; then
        grep "Failed password" /var/log/secure 2>/dev/null | tail -5 | awk '{print "    " $1" "$2" "$3" - "$9" from "$11}'
#     # fi
# # else
#     # echo "  Unable to read authentication logs (requires sudo)"
# # fi
# # 
# Network Statistics
# # print_header "NETWORK STATISTICS"
# # 
# # print_subheader "Active Network Interfaces:"
# # ip -brief addr 2>/dev/null | grep UP | awk '{printf "  %-12s %s\n", $1, $3}' || ifconfig | grep -E "^[a-z]" | awk '{print "  " $1}'
# # 
# # print_subheader "Network Connections:"
# # echo "  Established: $(ss -tan 2>/dev/null | grep ESTAB | wc -l || netstat -tan 2>/dev/null | grep ESTABLISHED | wc -l)"
# # echo "  Listening:   $(ss -tln 2>/dev/null | grep LISTEN | wc -l || netstat -tln 2>/dev/null | grep LISTEN | wc -l)"
# # 
# # echo -e "${YELLOW}╔════════════════════════════════════════════════════════╗${NC}"
# # echo -e "${YELLOW}║     Report generated: $(date '+%Y-%m-%d %H:%M:%S')              ║${NC}"
# # echo -e "${YELLOW}╚════════════════════════════════════════════════════════╝${NC}\n"
# # 
# 
# 
include "PmergeMe.hpp"
# 
# PmergeMe::PmergeMe() {}
# PmergeMe::~PmergeMe() {}
# 
# // ==================== Jacobsthal Sequence ====================
# // Generates: 1, 3, 5, 11, 21, 43...
# std::vector<int> PmergeMe::generateJacobsthal(int n) {
    # std::vector<int> jac;
    # if (n == 0) return jac;
    # jac.push_back(1);
    # if (n == 1) return jac;
    # jac.push_back(3);
    # while (jac.back() < n) {
        # int next = jac.back() + 2 * jac[jac.size() - 2];
        # jac.push_back(next);
    # }
    # return jac;
# }
# 
# // ==================== Vector Implementation ====================
# std::vector<int> PmergeMe::sortVector(std::vector<int>& v) {
    # if (v.size() <= 1) return v;
# 
    # // 1. Pairing
    # std::vector<std::pair<int, int> > pairs;
    # int leftover = -1;
    # bool hasLeft = (v.size() % 2 != 0);
    # for (size_t i = 0; i < v.size() - (hasLeft ? 1 : 0); i += 2) {
        # if (v[i] > v[i+1]) pairs.push_back(std::make_pair(v[i], v[i+1]));
        # else pairs.push_back(std::make_pair(v[i+1], v[i]));
    # }
    # if (hasLeft) leftover = v.back();
# 
    # // 2. Recursive Sort (Main Chain)
    # std::vector<int> winners;
    # for (size_t i = 0; i < pairs.size(); i++) winners.push_back(pairs[i].first);
    # std::vector<int> mainChain = sortVector(winners);
# 
    # // 3. Prepare Losers (Pend)
    # std::vector<int> pend;
    # for (size_t i = 0; i < mainChain.size(); i++) {
        # for (size_t j = 0; j < pairs.size(); j++) {
            # if (mainChain[i] == pairs[j].first) {
                # pend.push_back(pairs[j].second);
                # break;
            # }
        # }
    # }
# 
    # // 4. Insertion using Jacobsthal & Binary Search
    # std::vector<int> result = mainChain;
    # result.insert(result.begin(), pend[0]); // b1 is always smaller than a1
# 
    # std::vector<int> jac = generateJacobsthal(pend.size());
    # std::vector<bool> inserted(pend.size(), false);
    # inserted[0] = true;
# 
    # for (size_t i = 0; i < jac.size(); i++) {
        # int target = std::min(jac[i], (int)pend.size());
        # for (int j = target - 1; j >= 0; j--) {
            # if (!inserted[j]) {
                # // std::lower_bound is a built-in Binary Search
                # result.insert(std::lower_bound(result.begin(), result.end(), pend[j]), pend[j]);
                # inserted[j] = true;
            # }
        # }
    # }
    # if (hasLeft)
        # result.insert(std::lower_bound(result.begin(), result.end(), leftover), leftover);
    # return result;
# }
# 
# // ==================== List Implementation ====================
# std::list<int> PmergeMe::sortList(std::list<int>& l) {
    # if (l.size() <= 1) return l;
# 
    # // 1. Pairing
    # std::list<std::pair<int, int> > pairs;
    # int leftover = -1;
    # bool hasLeft = (l.size() % 2 != 0);
    # std::list<int>::iterator it = l.begin();
    # for (size_t i = 0; i < l.size() / 2; i++) {
        # int a = *it++; int b = *it++;
        # if (a > b) pairs.push_back(std::make_pair(a, b));
        # else pairs.push_back(std::make_pair(b, a));
    # }
    # if (hasLeft) leftover = l.back();
# 
    # // 2. Recursive Sort
    # std::list<int> winners;
    # for (std::list<std::pair<int, int> >::iterator p = pairs.begin(); p != pairs.end(); ++p)
        # winners.push_back(p->first);
    # std::list<int> mainChain = sortList(winners);
# 
    # // 3. Prepare Pend (Losers)
    # std::vector<int> pend; // Using vector for pend makes Jacobsthal index access easy
    # for (std::list<int>::iterator m = mainChain.begin(); m != mainChain.end(); ++m) {
        # for (std::list<std::pair<int, int> >::iterator p = pairs.begin(); p != pairs.end(); ++p) {
            # if (*m == p->first) { pend.push_back(p->second); break; }
        # }
    # }
# 
    # // 4. Insertion
    # std::list<int> result = mainChain;
    # result.push_front(pend[0]);
# 
    # std::vector<int> jac = generateJacobsthal(pend.size());
    # std::vector<bool> inserted(pend.size(), false);
    # inserted[0] = true;
# 
    # for (size_t i = 0; i < jac.size(); i++) {
        # int target = std::min(jac[i], (int)pend.size());
        # for (int j = target - 1; j >= 0; j--) {
            # if (!inserted[j]) {
                # result.insert(std::lower_bound(result.begin(), result.end(), pend[j]), pend[j]);
                # inserted[j] = true;
            # }
        # }
    # }
    # if (hasLeft)
        # result.insert(std::lower_bound(result.begin(), result.end(), leftover), leftover);
    # return result;
# }
# 
# // ==================== Parse & Run ====================
# 
# void PmergeMe::parseInput(int ac, char **av) {
    # for (int i = 1; i < ac; i++) {
        # std::string s(av[i]);
        # if (s.find_first_not_of("0123456789") != std::string::npos) throw std::runtime_error("Error");
        # long n = std::atol(av[i]);
        # if (n <= 0 || n > INT_MAX) throw std::runtime_error("Error");
        # _vec.push_back((int)n);
        # _lst.push_back((int)n);
    # }
# }
# 
# void PmergeMe::run() {
    # std::cout << "Before: ";
    # for (size_t i = 0; i < _vec.size(); i++) std::cout << _vec[i] << " ";
    # std::cout << "\n";
# 
    # clock_t startV = clock();
    # std::vector<int> resV = sortVector(_vec);
    # clock_t endV = clock();
# 
    # clock_t startL = clock();
    # std::list<int> resL = sortList(_lst);
    # clock_t endL = clock();
# 
    # std::cout << "After:  ";
    # for (size_t i = 0; i < resV.size(); i++) std::cout << resV[i] << " ";
    # std::cout << "\n";
# 
    # double tV = (double)(endV - startV) / CLOCKS_PER_SEC * 1e6;
    # double tL = (double)(endL - startL) / CLOCKS_PER_SEC * 1e6;
# 
    # std::cout << "Time for vector: " << std::fixed << std::setprecision(5) << tV << " us\n";
    # std::cout << "Time for list:   " << tL << " us\n";
# }