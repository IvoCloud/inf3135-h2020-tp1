/*
	INF3135 Hiiver 2020
	Ivaylo Ivanov
	TP2 malib.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./data/flop.h"
#include "malib.h"

void log_error(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info){
    ++capteur->erreurs;
    printf("06 %d %lu %s\n", sensor, timestamp, info);
}
void log_error_valeur(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info){
    ++capteur->erreurs_valeur;
    if(capteur->erreurs==5){
        capteur->actif = false;
    }
    printf("08 %d %lu %s\n", sensor, timestamp, info);
}

void set_actif(Capteur_t* capteur1, Capteur_t* capteur2, time_tp timestamp, Sensor_t sensor){
    capteur1->erreurs=0;
    capteur1->erreurs=0;
    capteur1->actif = true;
    capteur2->actif = true;
    printf("07 %d %lu\n", sensor, timestamp);
}

bool set_mcas(char* status){
    bool mcas = true;
    if(strcmp(status,"OFF")==0){
        mcas=false;
    }else{
        mcas=true;
    }
    printf("MCAS IS %s\n", status);
    return mcas;
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