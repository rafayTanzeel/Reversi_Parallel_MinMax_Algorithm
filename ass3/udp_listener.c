#include "udp_listener.h"

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>			// for strncmp()
#include <unistd.h>			// for close()
#include "audioMixer.h"
#include "zencape_inputCtrl.h"

#define MSG_MAX_LEN 1024
#define PORT 12345
void returnPacket(char* message);
void UDP_Listener_init();

void UDP_Listener_init(){

	printf("UDP Listener on port %d:\n", PORT);
//		printf("Connect using: \n");
//		printf("    netcat -u 127.0.0.1 %d\n", PORT);

	// Buffer to hold packet data:
		char message[MSG_MAX_LEN];

		// Address
		struct sockaddr_in sin;
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;                   // Connection may be from network
		sin.sin_addr.s_addr = htonl(INADDR_ANY);    // Host to Network long
		sin.sin_port = htons(PORT);                 // Host to Network short

		// Create the socket for UDP
		int socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0);

		// Bind the socket to the port (PORT) that we specify
		bind (socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

		while (1) {
			unsigned int sin_len = sizeof(sin);
			int bytesRx = recvfrom(socketDescriptor, message, MSG_MAX_LEN, 0, (struct sockaddr *) &sin, &sin_len);

			message[bytesRx] = 0;
			printf("Message received (%d bytes): \n\n'%s'\n", bytesRx, message);

			returnPacket(message);

//			int incMe = atoi(message);
//
//			sprintf(message, "Math: %d + 1 = %d\n", incMe, incMe + 1);
//
//			// Transmit a reply:
//			sin_len = sizeof(sin);
//			sendto( socketDescriptor,
//					message, strlen(message),
//					0,
//					(struct sockaddr *) &sin, sin_len);
		}

		// Close
		close(socketDescriptor);
}

void returnPacket(char* message){
	int value=0;
	char str[1024];
	int n=sscanf(message, "%s %d" ,str, &value);

	if( n==2){

		if(!strncmp(str, "T", 1)){
			AudioMixer_setBPM(value);
		}
		if(!strncmp(str, "V", 1)){
			AudioMixer_setVolume(value);
		}
	}
	else if(n==1){
		if(!strncmp(str, "None", 4)){
			zencape_setMenu(2);
		}
		else if(!strncmp(str, "R1B", 3)){
			zencape_setMenu(0);
		}
		else if(!strncmp(str, "R2B", 3)){
			zencape_setMenu(1);
		}
		else if(!strncmp(str, "Hit_hat", 7)){
			puts("HI");
			Audio_playFile(2);
		}
		else if(!strncmp(str, "Snare", 5)){
			Audio_playFile(8);
		}
		else if(!strncmp(str, "Base", 4)){
			Audio_playFile(0);
		}
	}
	else {
		sprintf(message, "Unknown command\n");
	}

}
