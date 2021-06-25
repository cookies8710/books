#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int server();
static void print_addrinfos(const struct addrinfo *ai);

int main(int argc, const char **argv)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *ai = NULL;
    int status = 0;

    status = getaddrinfo("localhost",  
            "8080",
            &hints,
            &ai);

    if (status)
    {
        fprintf(stderr, "getaddrinfo error %s\n", gai_strerror(status));
        return 1;
    }

    print_addrinfos(ai);

    freeaddrinfo(ai);

    server();

    return 0;
}

static int server()
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status;
    struct addrinfo *result;

    if (status = getaddrinfo(NULL, "8080", &hints, &result))
    {
        fprintf(stderr, "server: something went wrong: %s\n", gai_strerror(status));
        return status;
    }

    printf("server addresses:\n");
    print_addrinfos(result);

    freeaddrinfo(result);

    return 0;
}

static void print_addrinfos(const struct addrinfo *ai)
{
    int i = 1;
    for (const struct addrinfo *p = ai; p; p = p->ai_next, i++)
    {
        printf("Address # %d\n", i);
        //printf("ai_flags: %d\n", p->ai_flags);
        //printf("ai_family: %d\n", p->ai_family);
        //printf("ai_socktype: %d\n", p->ai_socktype);
        //printf("ai_protocol: %d\n", p->ai_protocol);
        //printf("ai_addrlen: %d\n", p->ai_addrlen);

        char dest[INET6_ADDRSTRLEN];
        memset(dest, 0, INET6_ADDRSTRLEN);

        const char *ip_version = NULL;
        const void *addr = NULL;
        switch (p->ai_family)
        {
            case AF_INET:
                ip_version = "IPv4";
                addr = &(((struct sockaddr_in*)p->ai_addr)->sin_addr);
                break;
            case AF_INET6:
                ip_version = "IPv6";
                addr = &(((struct sockaddr_in6*)p->ai_addr)->sin6_addr);
                break;
            default:
                fprintf(stderr, "Unknown family %d\n", p->ai_family);
                continue;
        }

        inet_ntop(p->ai_family, addr, dest, INET6_ADDRSTRLEN);
        /*printf("str=%x, dest=%x\ndest: %s\nINET_ADDRSTRLEN: %d\n", str, dest, dest,
               INET_ADDRSTRLEN );*/
        printf("\t%s: %s\n", ip_version, dest);

        //printf("ai_protocol: %d\n", p->ai_protocol);

        //printf("ai_canonname: %s\n", p->ai_canonname);
    }
}
