#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#define NI_MAXHOST 1025
#include <stdio.h>
int main() {
    struct addrinfo * resultado;
    struct addrinfo * res;
    struct sockaddr_in *socka;
    int error;
   error = getaddrinfo (NULL, "ssh", NULL , &resultado);
   if (error != 0)
   {   perror ("getaddrinfo");
       fprintf (stderr, "error en getaddrinfo:%s\n", gai_strerror (error));
        exit (EXIT_FAILURE);
   }
   for (res = resultado; res!= NULL; res = res-> ai_next)
   {
       char hostname [NI_MAXHOST];
       int puerto;
       socka = (struct sockaddr_in *) res->ai_addr ;
       puerto = (socka->sin_port);
       error = getnameinfo (res-> ai_addr, res-> ai_addrlen, hostname, NI_MAXHOST, NULL, 0, 0);
       if (error!= 0)
       {
           fprintf (stderr, "error en getnameinfo:%s \n", gai_strerror (error));
           //Seguir;
       }
       if (* hostname != '\0') printf ("nombre de host:%s \n", hostname);
       printf("Puerto: %d\n", htons(puerto));
   }
   freeaddrinfo (resultado);
   return 0;
}



