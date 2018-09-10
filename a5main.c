#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>		//library functions
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MY_PORT 60003
#define SERVER_IP "10.0.2.15"	//port and IP definitions
#define SERVER_PORT 60003

//function prototypes
void myserver();
void myclient();
void goof();
void msgconvert(char*, int);

//global variable socket
int globalSocket;

int main(int argc, char* argv[])
{
  int keepRunning = 1; 
  int player = 1; 
  int state = 5;

  //Used to hold blank client/server's 
  //original phrase (with chars)
  char serverPhrase[101]; 
  char clientPhrase[101];		
  //Used to hold client/server's guesses 
  //for a phrase (with only '-')
  char serverGuesses[101];
  char clientGuesses[101];
  //Used to hold client/server's guesses 
  //for a phrase (with both '-' and chars)
  char serverMessage[101];
  char clientMessage[101];
  //Used to hold client/server's phrase to be sent 
  //to the socket for 'holding'(with only chars)
  char bufferClient[101]; 
  char bufferServer[101];

  //used for send and recv.
  int bytesRcv;
  int i;
  //catch the ctrl+C if it's done in the program 
  //(signals) and make it go to goof() instead.
  signal(SIGINT, goof);

  //
  if(argc == 2 && keepRunning == 1){
    player = 1;
    printf("Client Connected.\n");
    myclient();
  }
  else if(argc != 2 && keepRunning == 1){
    player = 2;
    printf("Server Online.\n");
    myserver();
  }
  while(keepRunning == 1){
    if(player == 1){
	printf("You're playing Probe, Client...good luck.\n\n");
	printf("Word to Guess: ");

	//ask the client for a word that will be used to
	//be the main word that needs to be guessed by the server
        scanf("%s", clientPhrase);

	//copy that word over to bufferClient so that the original will never
	// be touched (maybe unecessary, but this is how I felt I should).
        strcpy(bufferClient, clientPhrase);
        
	//Send a clientPhrase over to the global socket
        send(globalSocket, clientPhrase, strlen(clientPhrase), 0);
	//Recieve the bufferServer from the globalSocket
        bytesRcv = recv(globalSocket, bufferServer, strlen(serverPhrase), 0);
        bufferServer[bytesRcv] = '\0';

        //converts individual letters of a word to '-'.
        //Then shows the hidden message to the client.
	msgconvert(bufferServer, 1);

     break;
    }
    if(player == 2){
      printf("This is server's Probe. You can't lose...maybe.\n\n");
      printf("Word to Guess: ");

      //ask the server for a word that will be used to
      //be the main word that needs to be guessed by the client
      scanf("%s", serverPhrase);

      //copy that word over to bufferServer so that the original will never
      // be touched (maybe unecessary, but this is how I felt I should).
      strcpy(bufferServer, serverPhrase);
      
      //Send a bufferServer over to the global socket
      send(globalSocket, bufferServer, strlen(serverPhrase), 0);

      //Recieve the bufferClient from the globalSocket
      bytesRcv = recv(globalSocket, bufferClient, strlen(bufferServer), 0);
      bufferClient[bytesRcv] = '\0';

      //converts individual letters of a word to '-'.
      //Then shows the hidden message to the client.
      msgconvert(bufferClient, 2);

      break;
    }
  }
 /*
//Enter a letter guess
  while(keepRunning == 1){
    if(player == 1){
      printf("Really...you're going with that? Fine...Good Luck.\n");
      printf("Guess a Letter: ");

      scanf("%s", clientGuesses);

//if a letter at bufferServer's i is the same as clientGuesses,
//then update the clientGuesses to show that letter.
      for(i = 0; i < strlen(bufferServer); ++i){
        clientGuesses[i] == bufferServer[0];
      }
      send(globalSocket, clientGuesses, strlen(clientGuesses), 0);
      bytesRcv = recv(globalSocket, bufferServer, strlen(bufferServer), 0);      
      
      //victory check
      if(srcmp(clientGuesses, bufferServer) == 0){
	 keepRunning = 2;
         state = 10;
    break;
    }
//Enter a letter guess
    if(player == 2){
      printf("What a marvelous word. No way you can lose, now.\n");
      printf("Guess a Letter: ");

      scanf("%s", serverGuesses);      

//if a letter at bufferClient's i is the same as serverGuesses,
//then update the serverGuesses to show that letter.
      for(i = 0; i < strlen(bufferClient); ++i){
        serverGuesses[i] = bufferClient[0];
      }
      send(globalSocket, serverGuesses, strlen(serverGuesses), 0);
      bytesRcv = recv(globalSocket, bufferClient, strlen(bufferServer), 0);

      //victory check
      if(strcmp(serverGuesses, bufferClient) == 0){
	 keepRunning = 2;
         state = 10;
      }
    break;
    }
  }*/
 /* 

//VICTORY FOR CLIENT!
  while(keepRunning = 2 && state == 10){  
      if(player == 1 && state == 10){
        char choice;
        printf("Wow...You won...Grats, I guess...");
        printf("Play Again? (Y/N): ");
        scanf('%s', choice);
        if(choice == 'Y' || choice == 'Y'){
	  printf("Restarting Game...");
          sleep(5);
	  player = 1;
	  main();	
	}else if(choice == 'N' || choice == 'n'){
	  printf("Good Riddance!");
	  exit(0);
	}
//VICTORY FOR SERVER!
      }else if(player == 2 && state == 10){
	char choice;
	printf("You win. No surprise here.");
	printf("Play Again? (Y/N): ");
        scanf('%s', choice);
        if(choice == 'Y' || choice == 'Y'){
	  printf("Restarting Game...");
          sleep(5);
	  player = 1;
	  main();	
       }else if(choice == 'N' || choice == 'n'){
	    printf("Good Day!");
	    exit(0);
      }
}
  
*/return 0;
}

/*
  Function:  myserver()
  Purpose:   initiate a "server" for multi-client use
       in:   no parameters to be taken in
   return:   a "server" will be set up for communication to clients
*/

void myserver()
{
  int myListenSocket, clientSocket;
  struct sockaddr_in  myAddr, clientAddr;
  int i, addrSize;

/* create socket */

  myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (myListenSocket < 0) {
    printf("Couldn't open socket\n");
    exit(-1);
  }


/* setup my server address */
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) MY_PORT);

/* bind my listen socket */

  i = bind(myListenSocket, 
           (struct sockaddr *) &myAddr,
           sizeof(myAddr));
  if (i < 0) {
    printf("Couldn't bind socket\n");
    exit(-1);
  }


/* listen */
  i = listen(myListenSocket, 5);
  if (i < 0) {
    printf("Couldn't listen\n");
    exit(-1);
  }


/* wait for connection request */

  addrSize = sizeof(clientAddr);

  globalSocket = accept(myListenSocket,
                        (struct sockaddr *) &clientAddr,
                         &addrSize);
  if (globalSocket < 0) {
    printf("Couldn't accept the connection\n");
    exit(-1);
  }

  close(myListenSocket);
}

/*
  Function:  myclient()
  Purpose:   initiate a "client" for multi-client use
       in:   no parameters to be taken in
   return:   a "client" will be set up for communication with the server
*/

void myclient()
{
  int mySocket;
  struct sockaddr_in  addr;
  int i;

/* create socket */
  globalSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (globalSocket < 0) {
    printf("Couldn't open socket.\n");
    exit(-1);
  }


/* setup address */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  addr.sin_port = htons((unsigned short) SERVER_PORT);

/* connect to server */

  i = connect(globalSocket, 
             (struct sockaddr *) &addr,
              sizeof(addr));
  if (i<0) {
    printf("Client could not connect!\n");
    exit(-1);
  }
}
/*
  Function:  goof()
  Purpose:   block command line arguments
       in:   no parameters to be taken in
   return:   prints a statement everytime an illegal action is done.
*/

void goof(){
  printf("\nYOU CAN'T JUST QUIT.\n");
}

/*
  Function:  msgconvert()
  Purpose:   initiate a "server" for multi-client use
       in:   a char pointer named "convertThis" that represents the word to be converted
       in:   an int that specifies the player number which is basically the location of the word.
   return:   a string array with "-" in place of the original parameter word's letters.
*/

void msgconvert(char *convertThis, int playerNum){
  int i; 
  char guessesArr[30];
  guessesArr[0] = '\0';
  for(i = 0; i < strlen(convertThis); ++i){
    strcat(guessesArr, "-");
  }
  printf("Player %d's word is: %s \n", playerNum, guessesArr);
  guessesArr[0] = '\0';
}

//Letter and Updating pseudocode

//word[] = something
//display[] = ---
//for(i=0; strlen(word); i++)
//	if word[i] == letterguess,
//		{then display[i] = letterguess}
//return/print display;
//wait for server guess
