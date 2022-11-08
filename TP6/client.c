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

#include "client.h"
#include "bmp.h"


int fsize(const char * fname, long * ptr)
{
    /* Cette fonction retourne 0 en cas de succès, une valeur différente dans le cas contraire. */
    FILE * f;
    int ret = 0;
    f = fopen(fname, "rb");
    if (f != NULL)
    {
        fseek(f, 0, SEEK_END);  /* aller à la fin du fichier */
        *ptr = ftell(f);        /* lire l'offset de ptr par rapport au début du fichier */
        fclose(f);
    }
    else
        ret = 1;
    return ret;
}

void get_commande(Json *instruction){
    char *str_copy = malloc(strlen(instruction->str));
    strcpy(str_copy, instruction->str);
    char delim = ',';
    char *save_str;
    char *code = strtok_r(str_copy, &delim, &save_str);
    char *val = malloc(sizeof(save_str));
    val = save_str;
    instruction->code = code+13;
    instruction->val = val+15;
}

/*
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */

int envoie_recois_message(int socketfd, Json *instruction)
{

    char data[1024];
    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    char message[1024];
    strcpy(message, instruction->val);
    strcpy(data, "message: ");
    strcat(data, message);

    int write_status = (int)write(socketfd, data, strlen(data));
    if (write_status < 0)
    {
        perror("erreur ecriture");
        exit(EXIT_FAILURE);
    }

    // la réinitialisation de l'ensemble des données
    memset(data, 0, sizeof(data));

    // lire les données de la socket
    int read_status = (int)read(socketfd, data, sizeof(data));
    if (read_status < 0)
    {
        perror("erreur lecture");
        return -1;
    }
    printf("Message recu: %s\n", data);
    return 0;
}

void analyse(char *pathname, char *data)
{
  // compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
    int number_of_colors;
    printf("combien de couleurs voulez-vous afficher ? : ");
    scanf("%d", &number_of_colors);
    getchar();
    while(number_of_colors > 30 || number_of_colors < 0){
        printf("combien de couleurs voulez-vous afficher ? : ");
        scanf("%d", &number_of_colors);
        getchar();
    }
    strcpy(data, "couleurs: ");
    char temp_string[10];
    sprintf(temp_string,"%d" ,number_of_colors);
    if (cc->size < 10)
    {
        sprintf(temp_string, "%d,", cc->size);
    }
    strcat(strcat(data, temp_string),",");

  // choisir number_of_colors couleurs
    
  for (count = 1; count < number_of_colors && cc->size - count > 0; count++)
  {
    if (cc->compte_bit == BITS32)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc24[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    if (cc->compte_bit == BITS24)
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc32[cc->size - count].c.rouge, cc->cc.cc32[cc->size - count].c.vert, cc->cc.cc32[cc->size - count].c.bleu);
    }
    strcat(data, temp_string);
  }

  // enlever le dernier virgule
  data[strlen(data) - 1] = '\0';
}

int envoie_couleurs(int socketfd, char *pathname)
{
  char data[1024];
  memset(data, 0, sizeof(data));
  analyse(pathname, data);

  int write_status = (int)write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}


int envoie_operateur_numeros(int socketfd, Json *instruction){
    int write_status;
    int read_status;
    
    char data[1024];
    strcpy(data, instruction->val);
    char message[1024];
    
    char delim[] = ","; // création de la délimitation
    char *ptr = strtok(data, delim);// strtok sépare data en deux : ptr à gauche, le reste de data à droite
    char *operator = ptr+3;         // on récupère l'opérateur
    int len = (int)strlen(operator);
    operator[len-1] = '\0';         //on enlève le " à la fin
    ptr = strtok(NULL, delim);
    char *strV1 = ptr+2;
    len = (int)strlen(strV1);
    strV1[len-1] = '\0';            //on enlève le " à la fin
    ptr = strtok(NULL, delim);
    char *strV2 = ptr+2;
    len = (int)strlen(strV2);
    strV2[len-3] = '\0';            //on enlève le " à la fin
    memset(message, 0, sizeof(message));
    strcpy(message, "calcule: ");
    strcat(strcat(strcat(strcat(strcat(message, operator)," "),strV1)," "),strV2);
    
    printf("%s \n", message);
    
    write_status = (int)write(socketfd, message, sizeof(message));
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
}


int envoie_couleurs_bis(int socketfd, Json *instruction){
//    int write_status;
//    int read_status;
    
    char message[1024];
    char data[1024];
    strcpy(data, instruction->val);     //on copie pour pas modifier l'original dans instruction
//    printf("%s", data);
    char delim_commande = ',';
    int i = 0;
    int nb_couleurs= 1;
                                // stocke le nombre de couleurs à afficher
    while(*(data+i) != '\0'){
        if(*(data+i) == delim_commande){
            nb_couleurs++;
        }
        i++;
    }
    char *nb_couleurs_str = malloc(sizeof(nb_couleurs));
    sprintf(nb_couleurs_str, "%d", nb_couleurs);
    printf("%s \n", nb_couleurs_str);
    memset(message, 0, sizeof(message));
    strcat(message, "couleurs:");
    strcat(strcat(strcat(message, " "),nb_couleurs_str),",");
    int offset = 5;
    char color[9]= "#";
    char *color_ptr = &color[0];
    char tamp[1024];
    
    for(int j = 0; j<nb_couleurs; j++){
        memset(color, 0, sizeof(color));
        strcat(color, "#");
//        printf("%s \n", color);
        strcpy(tamp, data+offset);
        tamp[6] = '\0';
        offset = offset+11;
        strcat(color, tamp);
        strcat(strcat(message, color),",");
//        printf("%s \n", color);
    }
    message[strlen(message) - 1] = '\0';
    printf("%s \n", message);
    
    int write_status = (int)write(socketfd, message, strlen(message));
    if (write_status < 0)
    {
      perror("erreur ecriture");
      exit(EXIT_FAILURE);
    }
    return 0;
}
    

int send_Json_cmd(int socketfd){
    // envoyer et recevoir un message
      char *path = "test.json";
      
      long size_of_file = 0;
      long *size_of_file_ptr = &size_of_file;
      if(fsize(path, size_of_file_ptr) !=0){// on récupère la taille du fichier
          return EXIT_FAILURE;
      }
      char chaine[size_of_file];  // allocation d'un tableau de la taille du fichier
      
      FILE* fichier;
      fichier = fopen(path, "r");
      if (fichier != NULL)
      {
          fread(chaine, size_of_file, 1, fichier);
          fclose(fichier);
      }
      else{
          return 1;
      }
      
      char delim_commande = '}';
      int i = 0;
      int nb_instrcution= 0;               // stocke le nombre d'instructions dans le json
      while(*(chaine+i) != '\0'){
          if(*(chaine+i) == delim_commande){
              nb_instrcution++;
          }
          i++;
      }
      Json instruction[3];
      
      char delim[] = "}";
      char *save_str;
      char *ptr_instruction = strtok_r(chaine, delim, &save_str);
      instruction[0].str = ptr_instruction;
      get_commande(&instruction[0]);
      for(int i = 1; i< nb_instrcution; i++){
          ptr_instruction = strtok_r(save_str, delim, &save_str);
          instruction[i].str = ptr_instruction+2;
          get_commande(&instruction[i]);
      }
    int choice;
    while(1){
        printf("1: envoyer json , 2: fermer:");
        scanf("%d", &choice);
        viderBuffer();
        if(choice == 1){
            printf("quelle instruction réaliser ? \n");
            for(int i = 0; i< nb_instrcution; i++){
                printf("%d  :", i);
            }
            scanf("%d", &choice);
            viderBuffer();
//            printf("%d \n",strcmp(instruction[2].code, " \"couleurs\""));
            if( strcmp(instruction[choice].code, "\"message\"")==0){
                envoie_recois_message(socketfd, &instruction[0]);
            }
            if( strcmp(instruction[choice].code, "\"calcule\"")==0){
                envoie_operateur_numeros(socketfd, &instruction[1]);
            }
            if( strcmp(instruction[choice].code, " \"couleurs\"")==0){
                printf("la\n");
                envoie_couleurs_bis(socketfd, &instruction[2]);
            }
        }
        else if (choice == 2){
            exit(4);
        }
    }
    return EXIT_SUCCESS;
}


void viderBuffer(void){
  int c;
  while((c=getchar()) != EOF && c != '\n');
}


int main(int argc, char **argv)
{
  int socketfd;
  struct sockaddr_in server_addr;
  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
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
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }
  if (argc != 2)
  {
      send_Json_cmd(socketfd);
  }
  else
  {
    // envoyer et recevoir les couleurs prédominantes
    // d'une image au format BMP (argv[1])
      envoie_couleurs(socketfd, argv[1]);
  }
    return 0;
}
