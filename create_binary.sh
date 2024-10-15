#!/bin/bash

# Prompt the user to enter the number of days (maximum 30 days)
read -p "Enter the number of days the binary should be valid for (max 30): " days

if ((days > 30)); then
  echo "Error: Maximum allowed is 30 days."
  exit 1
fi

# Create the C code
cat <<EOF > bgmi.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DAYS $days

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <ip> <port> <time> <threads>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int time_duration = atoi(argv[3]);
    int threads = atoi(argv[4]);

    // Check expiration
    time_t now = time(NULL);
    struct tm expiry_time;
    expiry_time = *localtime(&now);
    expiry_time.tm_mday += MAX_DAYS;

    if (mktime(&expiry_time) < now) {
        printf("Error: This binary has expired after %d days.\n", MAX_DAYS);
        return 1;
    }

    printf("IP: %s\nPort: %d\nTime: %d seconds\nThreads: %d\n", ip, port, time_duration, threads);
    
    // Put your actual functionality here

    return 0;
}
EOF

# Compile the binary using gcc
gcc -o bgmi bgmi.c

# Clean up the C file
rm bgmi.c

# Notify user
echo "Binary created successfully Join@creativeydv on TG. You can run it with ./bgmi <ip> <port> <tim
e> <threads>"
