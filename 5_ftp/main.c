/**
 * Homework 2: Parallel, binary max function
 *
 * CS4414 Operating Systems
 * Fall 2017
 *
 * Maurice Wong - mzw7af
 *
 * main.c - max function program
 *
 * COMPILE:     make
 * OBJECTS:     main.o
 * RUN:         ./max
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void performOps(int ConnectFD, int control_port);
void upperCaseString(char* str);
int openSocket(int port, char* address);

int main(int argc, char** argv) {
    int SocketFD = openSocket(atoi(argv[1]), "0");
    if (SocketFD < 0) {
        exit(EXIT_FAILURE);
    }

    for (;;) {
        int ConnectFD = accept(SocketFD, NULL, NULL);

        if (0 > ConnectFD) {
            perror("accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        char* connection_received = "220 Service ready for new user.\r\n";
        send(ConnectFD, connection_received, strlen(connection_received), 0);
        performOps(ConnectFD, atoi(argv[1]));

        if (shutdown(ConnectFD, SHUT_RDWR) == -1) {
            perror("shutdown failed");
            close(ConnectFD);
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        close(ConnectFD);
    }

    close(SocketFD);
    return EXIT_SUCCESS;
}


/**
 * Opens a socket to the specified port.
 * If address == "0", then trying to listen. Else connecting to ip address
 * Returns -1 if error creating socket,
 * -2 if error binding socket, -3 if error listening on socket.
 * -4 error connecting to socket
 * Returns the socket FD on success
 */
int openSocket(int port, char* address) {
    struct sockaddr_in sa;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
        return -1;
    }

    memset(&sa, 0, sizeof sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (strcmp(address, "0") == 0) { // bind and listen
        sa.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(SocketFD,(struct sockaddr *)&sa, sizeof sa) == -1) {
            close(SocketFD);
            return -2;
        }

        if (listen(SocketFD, 10) == -1) {
            close(SocketFD);
            return -3;
        }
    } else { // connect
        inet_pton(AF_INET, address, &sa.sin_addr);
        if (connect(SocketFD, (struct sockaddr *)&sa, sizeof sa) == -1) {
          perror("connect failed");
          close(SocketFD);
          return -4;
        }
    }
    return SocketFD;
}

/**
 * Loop to perform control operations in control connection
 */
void performOps(int ConnectFD, int control_port) {
    int full_command_len = 10000;
    char full_command[full_command_len];
    char* command;
    int dataSocketFD;
    for (;;) {
        memset(full_command, '\0', full_command_len);
        int recv_status = recv(ConnectFD, full_command, full_command_len, 0);
        if (recv_status <= 0) { // error receiving message or shutdown
            break;
        }
        printf("recv status %d\n", recv_status);
        printf("full command: %s\n", full_command);
        command = strtok(full_command, " \n\r");
        upperCaseString(command);
        printf("%s\n", command);
        // SWITCH BASED ON WHAT COMMAND IS RECEIVED
        if (strcmp(command, "USER") == 0) { // USER
            printf("USER reached\n");
            char* undefined_command = "230 User logged in, proceed.\r\n";
            send(ConnectFD, undefined_command, strlen(undefined_command), 0);
        } else if (strcmp(command, "QUIT") == 0) { // QUIT
            printf("QUIT reached\n");
            char* quit_command = "221 Service closing control connection.\r\n";
            send(ConnectFD, quit_command, strlen(quit_command), 0);
            break;
        } else if (strcmp(command, "PORT") == 0) { // PORT
            int i = 0;
            char address[20];
            int address_len = 0;
            for (i = 0; i < 4; i++) { // ip address
                char* temp = strtok(NULL, ",");
                strcpy(address + address_len, temp);
                address_len += strlen(temp) + 1;
                address[address_len-1] = '.';
            }
            address[address_len-1] = '\0';
            int p1 = atoi(strtok(NULL, ","));
            int p2 = atoi(strtok(NULL, ","));
            int portNum = (p1 << 8) | p2;
            dataSocketFD = openSocket(portNum, address);
            if (dataSocketFD >= 0) {
                char* port_success = "200 PORT established.\r\n";
                send(ConnectFD, port_success, strlen(port_success), 0);
            } else {
                char* port_failure = "500 PORT not established.\r\n";
                send(ConnectFD, port_failure, strlen(port_failure), 0);
            }
        } else if (strcmp(command, "TYPE") == 0) { // TYPE
        } else if (strcmp(command, "MODE") == 0) { // MODE
        } else if (strcmp(command, "STRU") == 0) { // STRU
        } else if (strcmp(command, "RETR") == 0) { // RETR
        } else if (strcmp(command, "STOR") == 0) { // STOR
        } else if (strcmp(command, "NOOP") == 0) { // NOOP
            printf("NOOP reached\n");
            char* noop_command = "200 Command okay.\r\n";
            send(ConnectFD, noop_command, strlen(noop_command), 0);
        } else if (strcmp(command, "LIST") == 0) { // LIST
            char ls_command[1000];
            strcpy(ls_command, "/bin/ls -l ");
            char* pathname = strtok(NULL, " \n\r");
            if (pathname != NULL) {
                strcat(ls_command, pathname);
            }
            printf("ls command: %s\n", ls_command);
            char* data_connection = "150 Data connection established.\r\n";
            send(ConnectFD, data_connection, strlen(data_connection), 0);
            FILE *fp;
            fp = popen(ls_command, "r");
            char ls_content[10000];
            while (fgets(ls_content, 10000, fp) != NULL) {
                write(dataSocketFD, ls_content, strlen(ls_content));
            }
            pclose(fp);
            shutdown(dataSocketFD, SHUT_RDWR);
            close(dataSocketFD);
            char* transfer_done = "226 Transfer Complete.\r\n";
            send(ConnectFD, transfer_done, strlen(transfer_done), 0);
        } else { // unsupported commands
            printf("Unsupported command reached\n");
            char* undefined_command = "500 Syntax error, command unrecognized.\r\n";
            send(ConnectFD, undefined_command, strlen(undefined_command), 0);
        }

    }
}

void upperCaseString(char* str) {
    while(*str) {
      *str = (toupper(*str));
      str++;
    }
}
