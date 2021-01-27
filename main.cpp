#include <iostream>
#include <string>
#include "sendUDP.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	sendUDP sendUDP;
	bool resultConnexion;
	bool resultSend;
	char buffer[7];
	buffer[0] = 'c';
	buffer[1] = 'o';
	buffer[2] = 'u';
	buffer[3] = 'c';
	buffer[4] = 'o';
	buffer[5] = 'u';
	buffer[6] = 0x0a;
	buffer[7] = '\0';

	resultConnexion = sendUDP.connexion();

	if (resultConnexion == true)
	{
		cout << "socket bien connecte";
	}
	else
	{
		cout << "pas reussi a connecte";
	}

	resultSend = sendUDP.sendMsg(buffer, 8);

	if (resultSend == true)
	{
		cout << "message envoye";
	}
	else
	{
		cout << "pas reussi a envoyer le message";
	}

	sendUDP.closeSocket();
}
