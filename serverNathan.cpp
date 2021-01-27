#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main() {
    SOCKET sock;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    fprintf(stderr, "socket() message: %s\n",strerror(errno));

    SOCKADDR_IN InfoServer;
        InfoServer.sin_addr.s_addr  = htonl(INADDR_ANY);
        InfoServer.sin_family       = AF_INET;
        InfoServer.sin_port         = htons(9013);
        printf("Listage du port %d...\n",9013);
    
    int error_message;
    error_message = ::bind(sock, (SOCKADDR*)&InfoServer, sizeof(InfoServer));
    string key;
    getline(std::cin,key);

    char buffer[1500];
    
    /*int recvfrom(
        SOCKET   s,
        char     *buf,
        int      len,
        int      flags,
        sockaddr *from,
        int      *fromlen
    );*/
    recvfrom(sock, buffer, 1500,0, reinterpret_cast<sockaddr*>(&_from), &fromlen);
    
    /*La fonction memset() copie l'octet de poids faible 
    de caractere dans les premiers caractères de compteur 
    du tableau pointé par tampon. Elle renvoie tampon. 
    L'utilisation la plus courante de memset() 
    consiste à initialiser une région de mémoire à une valeur connue*/
    memset(buffer,'\0',1500);
    sockaddr_in _from;
    socklet_t fromlen = sizeof(_from);
    error_message = recvfrom(sock,buffer,1500,0,
reinterpret_cast<sockaddr*>(&_from),&fromlen);

    if(error_message<1){
        fprintf(stderr,"socket() message: %s\n",strerror(errno));
    }else{
        printf(" IP : %s ",inet_ntoa(_from.sin_addr));
        printf(" Port : %d ",ntohs(_from.sin_port));
        printf(" Reçu : %s ",buffer);
    }

    uint8_t _SizepacketBuff = 0;
    
    /*La fonction ioctl() modifie le comportement 
    des périphériques sous-jacents des fichiers spéciaux*/
    //ioctl(sock,FIONREAD,&_SizepacketBuff);
    
    char bufferRecep[1500];
    if(_SizepacketBuff > 0){
        
        if(recvfrom(sock, bufferRecep, 1500,0, reinterpret_cast<sockaddr*>(&_from), &fromlen) == "quit"){
            close(sock);
            exit;
        }
    }else{
        std::cout << "Rien à lire";
    }

    close(sock);
    return 0;
}