// klient wysyła  napis 
// komunikacja lokalna 
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#define IP "127.0.0.1"

int main(){
   int sd, clen, slen;
   char buff[5];

   struct sockaddr_in sad, //adres serwera
	cad; // adres klienta
   sd=socket(AF_INET,SOCK_DGRAM,0);
   if (sd < 0){
	   perror( "socket() ERROR" );
	   exit(1);
   }    
   memset((char *) &sad, 0,sizeof(sad));
   sad.sin_family=AF_INET;
   if( inet_pton(AF_INET, IP, &sad.sin_addr) <= 0 ){
      perror("inet_pton() ERROR");
      exit(1);
   }
   sad.sin_port=htons((ushort) 5000);
   cad.sin_family=AF_INET;
   cad.sin_port=htons(0);  // automatyczny wybor
   slen=sizeof(sad);
   
   char mess[5];
   int x;
   int counter = 0;

   while(1){
      printf("1. Kamien 2. Papier 3. Nozyce 4. Koniec\n");
      
      scanf("%d", &x);
      if ( x == 1) strcpy(buff, "kam");
      else if ( x == 2) strcpy(buff, "pap");
      else if ( x == 3) strcpy(buff, "noz");
      else if ( x == 4) strcpy(buff, "kon");
      else strcpy(buff, "kon");
      
      printf("Wybrano %s", buff);

      if (sendto(sd, buff, sizeof(buff), 0, (struct sockaddr *) &sad, slen) < 0){
         perror("sendto() ERROR");
         exit(1);
      }

      recvfrom(sd, buff, sizeof( buff ), 0, (struct sockaddr *) &sad, &slen);
      printf("odebrane %s z portu nr %d\n", buff, ntohs(sad.sin_port));
      printf("Wynik to: %s \n", buff);
         
      if( strcmp(buff, "kon") == 0){ // serwer zwroci kon
         printf("Wynik: %d", counter);
         exit(1);
      }
      if( strcmp(buff, "win") == 0 ) counter++; //zwieksza wynik jak serwer zwrocil win

   }

   return 0;
}

