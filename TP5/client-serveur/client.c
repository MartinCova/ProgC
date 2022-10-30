/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dirent.h>

#include "client.h"

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(int socketfd){
    char data[1024];
    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // Demandez à l'utilisateur d'entrer un message
    char message[1024];
    printf("Votre message (max 1000 caracteres): ");
    memset(message, 0, sizeof(message));
    fgets(message, sizeof(message), stdin);
//    scanf("%[^\n]", message);
    strcpy(data, "message: ");
    strcat(data, message);

    int write_status = (int)write(socketfd, data, strlen(data));
    if (write_status <= 0){
        perror("erreur ecriture");
        exit(EXIT_FAILURE);
    }

  // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

  // lire les données de la socket
    int read_status = (int)read(socketfd, data, sizeof(data));
    if (read_status < 0){
        perror("erreur lecture");
    return -1;
    }

    printf("Message recu: %s\n", data);

    return 0;
}


int envoie_operateur_numeros(int socketfd, int choice, int V1, int V2){
    char data[1024];
    char message[1024];
    int write_status;
    int read_status;
    
    char strV1[4];
    sprintf(strV1, "%d", V1);
    char strV2[4];
    sprintf(strV2, "%d", V2);
    
    char delim[] = " "; // création de la délimitation
    char *ptr = strtok(data, delim);// strtok sépare data en deux : ptr à gauche, le reste de data à droite
    ptr = strtok(NULL, delim);
    char *operator = ptr;       // on récupère l'opérateur
    
    switch (choice) {
        case 1:// l'utilisateur demande a faire un calcul
            memset(data, 0, sizeof(data));
            memset(message, 0, sizeof(message));
            printf("Votre calcul du type: operateur V1 V2: ");
            fgets(message, sizeof(message), stdin);
            strcpy(data, "calcule: ");
            strcat(data, message);
            
            write_status = (int)write(socketfd, data, strlen(data));
            if (write_status < 0){
                perror("erreur ecriture");
                exit(EXIT_FAILURE);
            }
            
            // la réinitialisation de l'ensemble des données
            memset(data, 0, sizeof(data));

            // lire les données de la socket
            read_status = (int)read(socketfd, data, sizeof(data));
            if (read_status < 0)
            {
              perror("erreur lecture");
              return -1;
            }
            printf("Message recu: %s\n", data);
            return 0;
            break;
        case 2: // pour les fichiers, le user ne rentre pas les nombres lui même
            memset(data, 0, sizeof(data));
            memset(message, 0, sizeof(message));
            strcpy(data, "calcule: ");
            strcat(strcat(strcat(strcat(message, "+ "),strV1)," "),strV2);
            
            strcat(data, message);
            
            write_status = (int)write(socketfd, data, strlen(data));
            if (write_status < 0){
                perror("erreur ecriture");
                exit(EXIT_FAILURE);
            }
            
            // la réinitialisation de l'ensemble des données
            memset(data, 0, sizeof(data));

            // lire les données de la socket
            read_status = (int)read(socketfd, data, sizeof(data));
            if (read_status < 0)
            {
              perror("erreur lecture");
              return -1;
            }
            printf("Message recu: %s\n", data);
            char *ptr = strtok(data, delim);// strtok sépare data en deux : ptr à gauche, le reste de
            ptr = strtok(NULL, delim);      // data à droite
            int result = atoi(ptr);
            return result;      // renvoie le résultat de la somme
        default:
            break;
    }
    return 0;
}

int lire_fichier(int socketfd){
    FILE *fptr;

    float moyenne_eleve[5];
    float *ptr_moyenne = &moyenne_eleve[0];
    
    for(int j= 1; j<6; j++){
        int tab_val[5];
        int *ptr_tab = &tab_val[0];
        
        char index_j[4];
        sprintf(index_j, "%d", j);
        for(int i =1; i<6; i++){
            char index_i[4];
                 char rep[4096] = "etudiant/";
                 sprintf(index_i, "%d", i);
                 strcat(strcat(strcat(strcat(rep, index_j),"/note"),index_i),".txt");
                 
                 if ((fptr = fopen(rep,"r")) == NULL){
                     printf("Error! opening file");
                     // Program exits if the file pointer returns NULL.
                     exit(1);
                 }
                 int num;
                 fscanf(fptr,"%d", &num);
                 *(ptr_tab+i-1) = num;
                 fclose(fptr);
             }
         int result = tab_val[0];
         
         for(int j = 1; j<5; j++){
             //on somme tab_val[0] et [1] , puis la somme des deux avec [2] et ainsi de suite
             result = envoie_operateur_numeros(socketfd, 2, result, *(ptr_tab+j));
//                 printf(" resultat : %d\n", result);
         }
        float moyenne= result;
        *(ptr_moyenne+j-1) = moyenne/5;
        printf(" somme des notes %d \n", result);
        }
    float moyenne_classe =0;
    
    for(int i = 0; i<5; i++){
        printf("moyenne eleve %d: %f \n",i+1, *(ptr_moyenne+i));
        moyenne_classe = moyenne_classe + *(ptr_moyenne+i);
    }
    printf("moyenne classe : %f \n",moyenne_classe/5);
    return 0;
}




void viderBuffer(void){
  int c;
  while((c=getchar()) != EOF && c != '\n');
}


int main(){
    int socketfd;

     struct sockaddr_in server_addr;

   /*
    * Creation d'une socket
    */
     socketfd = socket(AF_INET, SOCK_STREAM, 0);
     if (socketfd < 0){
         perror("socket");
         exit(EXIT_FAILURE);
     }

   // détails du serveur (adresse et port)
     memset(&server_addr, 0, sizeof(server_addr));
     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(PORT);
     server_addr.sin_addr.s_addr = INADDR_ANY;

   // demande de connection au serveur
     int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
     if (connect_status < 0){
         perror("connection serveur");
         exit(EXIT_FAILURE);
   }
    
//    envoie_operateur_numeros(socketfd);
    int choice;
//    int *ptr_choice = &choice;
    printf("que voulez vous faire ? 1: message   2:  calcul   3: fichier 4: fermer \n");
    scanf("%d", &choice);
    viderBuffer();
    switch (choice) {
        case 1:
            envoie_recois_message(socketfd);
            break;
        case 2:
            envoie_operateur_numeros(socketfd,1, 0,0);
            break;
        case 3:
            lire_fichier(socketfd);
        case 4:
            EXIT_SUCCESS;
        default:
            break;
}
    close(socketfd);
    return EXIT_SUCCESS;

}
