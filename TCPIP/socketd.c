#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define SD_PORT       4567
#define SD_BACK_LOG   10


int sd_listener_fd;


void
sd_init ()
{
    int reuse = 1;

    struct sockaddr_in addr;

    if ((sd_listener_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Create listener socket failed");
        exit(-1);
    }

    if (setsockopt(sd_listener_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        perror("Setup listener socket failed");
        exit(-1);
    }

    bzero(&(addr.sin_zero), 8);

    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(SD_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sd_listener_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Bind listener socket address failed");
        exit(-1);
    }

    if (listen(sd_listener_fd, SD_BACK_LOG) == -1)
    {
        perror("Listen port failed");
        exit(-1);
    }
}


void
sd_loop ()
{
    char buf[1024];

    int ret = 0;

    int client_fd;

    int client_addr_len;

    struct sockaddr_in client_addr;

    printf("Waiting connect on port %d\n", SD_PORT);

    client_addr_len = sizeof(client_addr);

    client_fd = accept(sd_listener_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    printf("Client connected\n");

	while(1);
    for (;;)
    {
        if ((ret = read(client_fd, buf, 1024)) == 0)
        {
            close(client_fd);

            printf("Client closed\n");

            break;
        }
        else
        {
            write(client_fd, buf, ret);
        }
    }
}


void
sd_down ()
{
    close(sd_listener_fd);

    printf("Server shutdown\n");
}


int
main (int argc, char *argv[])
{
    sd_init();

    sd_loop();

    sd_down();

    return 1;
}
