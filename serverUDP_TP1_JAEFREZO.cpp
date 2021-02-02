#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <string>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

SOCKADDR_IN InfoServer;

int main()
{

SOCKET sock;
sock = socket(AF_INET, SOCK_DGRAM, 0);
fprintf(stderr, "socket() message: %s\n", strerror(errno));

InfoServer.sin_addr.s_addr = htonl(INADDR_ANY);
InfoServer.sin_family = AF_INET;
InfoServer.sin_port = htons(9013);

printf("Listage du port %d...\n", 9013);

int error_message;
bool etat = false;
error_message = ::bind(sock, (SOCKADDR*)&InfoServer, sizeof(InfoServer));

char buffer[1500];
char bufferParse[1500];
int i,j=0,chiffre[1500],result[1500],resultat=0;
memset (buffer,'\0', 1500);
sockaddr_in _from;
socklen_t fromlen = sizeof(_from);

do 
{
    error_message = recvfrom(sock, buffer, 1500, 0, reinterpret_cast<sockaddr*>(&_from), &fromlen);

    if (buffer[0] != 'q')
    {
        if(error_message < 1)
        {
            fprintf(stderr, "socket() message: %s\n", strerror(errno));
        }
        else
        {
            printf("\nIP : %s \n", inet_ntoa(_from.sin_addr));
            printf("Port : %d \n", ntohs(_from.sin_port));
            printf("Message reçu : %s \n", buffer);

            for(i = 0; i < strlen(buffer);i++)
            {
                if (buffer[i] == ':')
                {
                    
                } else {
                    sscanf(&buffer[i],"%d",&chiffre[j]);
                    j++;
                }
            }
            for(int x = 0; x < j; x++){
                printf("Chiffre = %d\n",chiffre[x]);
                resultat += chiffre[x];
            }
            printf("Resultat = %d\n",resultat);

            for(int x = 0; x < j; x++){
                chiffre[x] = '\0';
            }
            resultat = 0;
            j = 0;
            for(i = 0; i < 1500; i++){
                buffer[i] = '\0';
                bufferParse[i] = '\0';
            }
        }
    }
    else
    {
        etat = true;
    }

} while(etat != true);

printf("fin du programme\n");
close(sock);
}

