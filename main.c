#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    char service[4] = "ssh";
    struct addrinfo * result , *rp , hints ;
    struct sockaddr_in *socka;
    struct sockaddr *sa;
    struct in_addr * ip ;
    char iptext [INET_ADDRSTRLEN ] ;
    int error , error2;
    memset(&hints , 0 , sizeof ( hints ) ) ;
    hints.ai_family = AF_INET ;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_CANONNAME;
    error = getaddrinfo ( "www.elpais.es" , NULL, &hints , &result ) ;
    if( error != 0) {
        fprintf( stderr , " Error en getaddrinfo : %s \n" , gai_strerror( error ) ) ;
        exit( EXIT_FAILURE) ;
    }
    printf( "Nombre canonico : %s \n" , result->ai_canonname ) ;
    for ( rp = result ; rp != NULL ; rp = rp->ai_next ) {
        socka = (struct sockaddr_in *) rp->ai_addr ;
        ip = &(socka->sin_addr) ;
        if( inet_ntop( rp->ai_family , ip , iptext , sizeof ( iptext ) ) == NULL) {
            perror ( " Error en inet_ntop " ) ;
            exit ( EXIT_FAILURE ) ;
        }
       printf( " Direccion IP : %s \n" , iptext ) ;
    }

    error2 = getnameinfo(sa, sizeof(*sa), iptext, sizeof(iptext),NULL, 0 , NI_NAMEREQD);
    if( error2 != 0) {
        fprintf( stderr , " Error en getaddrinfo : %s \n" , gai_strerror( error2 ) ) ;
        exit( EXIT_FAILURE) ;
    }
    printf( "Puerto : %s \n" , iptext ) ;



    freeaddrinfo ( result ) ;

    return 0;
}
