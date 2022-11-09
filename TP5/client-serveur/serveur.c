/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = (int)write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("erreur ecriture");
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}


int calcul_or_message(int socketfd){
    char data[1024];
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);

    // nouvelle connection de client
    int client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_fd < 0){
        perror("accept");
        close(socketfd);
        return (EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    
    while(1){
        memset(data, 0, sizeof(data));
        // lecture de données envoyées par un client
        int data_size = (int)read(client_socket_fd, (void *)data, sizeof(data));

        if (data_size < 0){
            perror("erreur lecture");
            return (EXIT_FAILURE);
        }

      /*
       * extraire le code des données envoyées par le client.
       * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
       */
      printf("Message recu: %s\n", data);
      char code[10];
      sscanf(data, "%s:", code);

      // Si le message commence par le mot: 'calcule:'
      if (strcmp(code, "calcule:") == 0){
          recois_numeros_calcule(socketfd,client_socket_fd, data);
      }else if (strcmp(code, "message:") == 0){
          recois_envoie_message(socketfd, client_socket_fd, data);
      }
      else {
          exit(EXIT_SUCCESS);
      }
    }
    return EXIT_SUCCESS;


}
    

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd,int client_socket_fd, char *data ){
  /*
   * extraire le code des données envoyées par le client.
   * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
   */
      printf("message à renvoyer : ");
      scanf("%[^\n]", data);
      renvoie_message(client_socket_fd, data);
//   fermer le socket
//    close(socketfd);
//    close(client_socket_fd);
  return (EXIT_SUCCESS);
}

int recois_numeros_calcule(int socketfd,int client_socket_fd, char *data){
    
    char delim[] = " "; // création de la délimitation
    char *ptr = strtok(data, delim);// strtok sépare data en deux : ptr à gauche, le reste de data à droite
    ptr = strtok(NULL, delim);
    char *operator = ptr;       // on récupère l'opérateur
    ptr = strtok(NULL, delim);
    int v1 = atoi(ptr);         // on récupère la variable 1
    ptr = strtok(NULL, delim);
    int v2 = atoi(ptr);         // on récupère la variable 2
    
//    printf("%d \n", v1);
//    printf("%d \n", v2);
//
//    printf("%x", (int)(*operator));
    
//    int val_operator = v2+v1;
//    printf("%s \n", operator);
//    printf("%d \n", val_operator);
    
    int result = 0;

    switch (*operator) {
        case 0x2B:
            result =  v1+v2;
            break;
        case 0x2A:
            result =  v1 * v2;
            break;
        case 0x2D:
            result =  v1 - v2;
            break;
        case 0x2F:
            result =  v1 / v2;
            break;
        default:
            break;
    }

    char result_str[20];
    sprintf(result_str, "%d", result);
    char message[1024];
    strcpy(message, "calcule: ");
    strcat(message, result_str);
    renvoie_message(client_socket_fd, message);
    printf("%s \n", message);
    
    // fermer le socket
//    close(socketfd);
//    close(client_socket_fd);
    return (EXIT_SUCCESS);
}



// Programme principal
int main(){
    // partie serveur
    int socketfd;
    int bind_status;
    struct sockaddr_in server_addr;

    //partie client
    int client_socket_fd;
    char data[1024];
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);
  
    
    /*
     * Creation d'une socket
     */
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0){
        perror("Unable to open a socket");
        return -1;
    }

    int option = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // détails du serveur (adresse et port)
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Relier l'adresse à la socket
    bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_status < 0){
        perror("bind");
        return (EXIT_FAILURE);
  }
    printf("server waiting for connections \n");
    
    if (listen(socketfd, 10) == -1){
        perror("listen");
            return EXIT_FAILURE;
    }
    calcul_or_message(socketfd);
    
  return 0;
}
