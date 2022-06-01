  #include <stdio.h>
   #include <stdlib.h>
   #include <ctype.h>
   #include <sys/socket.h>
   #include <sys/types.h>
   #include <netinet/in.h>
   #include <string.h>
   #include <arpa/inet.h>
   #define IP "127.0.0.1"
   int main(){
      int sd,clen;
      char buff[5], buff2[5];
      int client_counter1 = 0;
      int client_counter2 = 0;
      struct sockaddr_in sad, //adres serwera
                     cad2, //adres klienta2
	                 cad; // adres klienta
      
      sd=socket(AF_INET,SOCK_DGRAM,0);
      memset((char *) &sad, 0,sizeof(sad));
      sad.sin_family=AF_INET;
      
      if( inet_pton(AF_INET, IP, &sad.sin_addr) <= 0 ){
        perror("inet_pton() ERROR");
        exit(1);
      }
      sad.sin_port=htons((ushort) 5000);
      bind(sd,(struct sockaddr *) &sad, sizeof(sad));

      while (1){
        // OTRZYMUJE
        recvfrom(sd,buff, sizeof(buff),0, (struct sockaddr *) &cad, &clen);
	      printf("odebrane, port klienta %d\n ", ntohs(cad.sin_port));

        recvfrom(sd,buff2, sizeof(buff2),0, (struct sockaddr *) &cad2, &clen);
	      printf("odebrane, port klienta %d\n ", ntohs(cad2.sin_port));

        if (strcmp(buff, "kon") == 0 || strcmp(buff2, "kon") == 0){
          strcpy(buff, "kon");
          strcpy(buff2, "kon");
        }
        else if (strcmp(buff, buff2) == 0){
          strcpy(buff, "draw");
          strcpy(buff2, "draw");
        }
        else if(strcmp(buff, "kam") == 0){
          if(strcmp(buff2, "noz") == 0){
            strcpy(buff, "win");
            strcpy(buff2, "los");
          }
          else{
            strcpy(buff, "los");
            strcpy(buff2, "win");
          }
        }
        else if(strcmp(buff, "pap") == 0 && strcmp(buff2, "kam") == 0){
          strcpy(buff, "win");
          strcpy(buff2, "los");
        }
        else if(strcmp(buff, "noz") == 0 && strcmp(buff2, "pap") == 0){
          strcpy(buff, "win");
          strcpy(buff2, "los");
        }
        else{
          strcpy(buff, "los");
          strcpy(buff2, "win");
        }

         sendto(sd,buff, sizeof(buff), 0, (struct sockaddr *) &cad, clen);
         sendto(sd,buff2, sizeof(buff2), 0, (struct sockaddr *) &cad2, clen);
      
        if (strcmp(buff, "win") == 0) client_counter1++;
        else if (strcmp(buff, "draw") == 0);
        else if (strcmp(buff2, "win") == 0) client_counter2++;

        printf("\n Gracz 1#: %d\n Gracz 2#: %d\n", client_counter1, client_counter2);
      }

      return 0;
   }

