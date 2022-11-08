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

void plot(char *data)
{
    printf("%s", data);
    char delim[] = " "; // création de la délimitation
    char *str = strtok(data, delim);//strtok sépare data en deux : ptr à gauche, le reste de data à droite
    str = strtok(NULL, delim);      // on récupère le nombre de couleurs à afficher
    
    
    // Extraire le compteur et les couleurs RGB
    FILE *p = popen("gnuplot -persist", "w");
    printf("Plot\n");
    int count = 0;
    int n;
    char *saveptr = NULL;
    fprintf(p, "set xrange [-15:15]\n");
    fprintf(p, "set yrange [-15:15]\n");
    fprintf(p, "set style fill transparent solid 0.9 noborder\n");
    fprintf(p, "set title 'Top 10 colors'\n");
    fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
    
    float number_of_colors = atoi(str);
    float number_cases = 360/number_of_colors;
    
    while (1)
    {
        char *token = strtok_r(str, ",", &saveptr);
        if (token == NULL)
        {
            break;
        }
        str = NULL;
    printf("%d: %s\n", count, token);
        if (count == 1)
        {
            n = atoi(token);
            printf("n = %d\n", n);
        }
        else
        {
            // Le numéro 36, parceque 360° (cercle) / 10 couleurs = 36
            fprintf(p, "0 0 10 %f %f 0x%s\n", (count-1) * number_cases, count * number_cases, token + 1);
        }
        count++;
    }
    fprintf(p, "e\n");
    printf("Plot: FIN\n");
    pclose(p);
}


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

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */

int calcul_or_message(int socketfd){
    char data[1024];
    char code[10];
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
    int i =0;
    while(i ==0){
        memset(data, 0, sizeof(data));
        memset(code, 0, sizeof(code));
        // lecture de données envoyées par un client
        int data_size = (int)read(client_socket_fd, (void *)data, sizeof(data));
        if (data_size < 0){
            perror("erreur lecture");
            return (EXIT_FAILURE);
        }
        sscanf(data, "%s:", code);
        
        // Si le message commence par le mot: 'calcule:'
        if (strcmp(code, "calcule:") == 0){
            recois_numeros_calcule(socketfd,client_socket_fd, data);
        }else if (strcmp(code, "message:") == 0){
            renvoie_message(client_socket_fd, data);
        }
        else if (strcmp(code, "couleurs:") == 0){
            plot(data);
        }
        else{
            i = 1;
            return 1;
        }
    }
    close(socketfd);
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
    
    int result = 0;
    
    switch (*operator) {
        case 0x2B:
            result =  v1 + v2;
            break;
        case 0x2A:
            result =  v1 * v2;
        case 0x2D:
            result =  v1 - v2;
        case 0x2F:
            result =  v1 / v2;
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

void viderBuffer(void){
  int c;
  while((c=getchar()) != EOF && c != '\n');
}

int main()
{

  int socketfd;
  int bind_status;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
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
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Écouter les messages envoyés par le client
  listen(socketfd, 10);

  // Lire et répondre au client
  calcul_or_message(socketfd);

  return 0;
}
