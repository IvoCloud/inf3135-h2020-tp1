/*
	INF3135 Hiiver 2020
	Ivaylo Ivanov
	TP3 tp3.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "flop.h"
#include "malib.h"

char* log_error(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info){
    char* message = malloc(25);
    ++capteur->erreurs;
    sprintf(message,"06 %d %lu %s\n", sensor, timestamp, info);
    return message;
}
char* log_error_valeur(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info){
    char* message = malloc(25);
    ++capteur->erreurs_valeur;
    if(capteur->erreurs==5){
        capteur->actif = false;
    }
    sprintf(message, "08 %d %lu %s\n", sensor, timestamp, info);
    return message;
}
char* set_actif(Capteur_t* capteur1, Capteur_t* capteur2, time_tp timestamp, Sensor_t sensor){
    char* message = malloc(25);
    capteur1->erreurs=0;
    capteur1->erreurs=0;
    capteur1->actif = true;
    capteur2->actif = true;
    sprintf(message,"07 %d %lu\n", sensor, timestamp);
    return message;
}
char* set_mcas(char* status, bool* mcas){
    char* message = malloc(25);
    if(strcmp(status,"OFF")==0){
        *mcas=false;
    }else{
        *mcas=true;
    }
    sprintf(message, "MCAS IS %s\n", status);
    return message;
}
void set_inactif(Capteur_t* capteur1, Capteur_t* capteur2){
    capteur1->actif = false;
    capteur2->actif = false;
}
bool volet_conforme(float longueur){
    bool conforme=false;
    if(longueur>=0.0&&longueur<=108.0){
        conforme=true;
    }
    return conforme;
}
bool validation_format_transaction(char* data[4]){
    bool valide = false;
    int transaction = atoi(data[1]);
    if(transaction>=01&&transaction<=05){
        if(transaction==1){
            if(data[3]==NULL){
                valide = true;
            }
        }else{
            if(data[3]!=NULL){
                valide = true;
            }
        }
    }
    return valide;
}
bool validation_timestamp(char* time, time_tp timestamp){
    return (atoi(time)>timestamp);
}
bool valider_angle_conforme_AI(EtatAppareil_t etat, float valeur){
    bool conforme=false;
    switch(etat){
        case 0:
            if(tarmac_angle_conforme_v1(valeur)){
                conforme=true;
            }
        break;
        case 1:
            if(decollage_angle_conforme_v2(valeur)){
                conforme=true;
            }
        break;
        case 2:
            if(vol_angle_conforme_v3(valeur)){
                conforme=true;
            }
        break;
        case 3:
            if(atterrissage_angle_conforme_v1(valeur)){
                conforme=true;
            }
        break;
    }
    return conforme;
}

bool mode_tranquille(int argc, char* argv[]){
    int index = argc-1;
    for (index;index!=0;--index){
        if(strcmp("-t",argv[index])==0) return true;
    }
    return false;
}

void cmd(int argc,char* argv[], Info_t* info){
    bool i = false;
    bool d = false;
    bool s = false;
    int index = argc-1;
    for(index; index!=0;--index){
        if(strcmp("-i",argv[index])==0) i=true;
        if(strcmp("-d",argv[index])==0) d=true;
        if(strcmp("-s",argv[index])==0) s=true;
    }
    
    printf("-----------------\n");
    
    if(i){
        printf("Transactions non renonnues\n");
        printf("Transactions non valides: %d\n", info->trx_non_valide);
        printf("Timestamp non valide: %d\n", info->err_time);
        printf("-----------------\n");
    }
    if(d){
        printf("Information detaillee\n");
        for(index;index<5;++index){
            printf("Transaction no. %d : %d\n", index+1,info->trx_types[index]);
        }
        printf("-----------------\n");
    }
    if(s){
        printf("Information sommaire\n");
        printf("Transactions valides: %d\n", (info->trx_recues-(info->trx_non_valide+info->err_time)));
        printf("Transactions recues: %d\n", info->trx_recues);
        printf("-----------------\n");
    }
}

