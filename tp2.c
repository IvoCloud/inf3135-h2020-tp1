#include "flop.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned long int time_t;

version_t version = {'1','0', 100};

typedef enum Systeme{VOLET=11, STABILIZATEUR_HORIZONTAL, ANGLE_INCIDENCE}Systeme_t;

typedef struct capteur_AI_s{
    float capteur;
    int erreur;
    bool isOn;
}capteur_AI_t;

typedef struct capteur_VOL_SH_s{
    float angle;
    int erreur;
    bool etatChange;
}capteur_VOL_SH_t;

typedef struct Systeme2_s{
    bool VOLET;
    bool SH;
    bool AI;
    EtatAppareil_t ETAT;
}Systeme2_t;

time_t timestamp = 0;
EtatAppareil_t etat = 0;
const char* A1 = "A1";
const char* A2 = "A2";
const char* A3 = "A3";
const char* ERROR = "ERROR\n";

bool timeIsValid(char* time);
bool trxIsValid(char* trx);
bool dataNotNull(char* data[], int index, int size);
bool capteurValide(char* capteur);
bool mcasSet(bool status);
bool volet_longueur_max(float volet);
void sysError(char* data[], Systeme_t systeme, time_t time, char* info);
void valError(char* data[], Systeme_t systeme, time_t time, char* info);
void AI_Check(char* data[], time_t time, EtatAppareil_t etat, capteur_AI_t *capteurAngle,
			 capteur_AI_t *capteurSecondaire);
void SH_Check(char* data[], time_t timestamp, 
			 capteur_VOL_SH_t *capteurPrimaire, capteur_VOL_SH_t *capteurSecondaire);




bool mcas;

int main()
{
    char input[25];
    char* data[4];
    int trx;
    bool error;
    mcas=true;
    
    capteur_AI_t A1 = {0.0,0,true};
    capteur_AI_t A2 = {0.0,0,true};
    capteur_AI_t A3 = {0.0,0,true};
    capteur_VOL_SH_t voletGauche = {0.0,0,false};
    capteur_VOL_SH_t voletDroite = {0.0,0,false};
    capteur_VOL_SH_t angleStabilizateurGauche = {0.0,0,false};
    capteur_VOL_SH_t angleStabilizateurDroite = {0.0,0,false};
    
    while(fgets(input, 25, stdin) != NULL){
        error = false;
        data[0] = strtok(input, " ");
    
        if(timeIsValid(data[0])){
            timestamp = atoi(data[0]);
            data[1] = strtok(NULL, " ");
            data[2] = strtok(NULL, " ");
            data[3] = strtok(NULL, " ");
            
            if(trxIsValid(data[1])){
                trx = atoi(data[1]);
                
                switch(trx){
                    case 1:
                        if(validation_etat_appareil_v3(atoi(data[2]))){
                            etat=atoi(data[2]);
                        }
                        break;
                    case 2:
                        if(dataNotNull(data,2,4)){
                            switch(data[2][1]-'0'){
                                case 1:
                                    AI_Check(data, timestamp, etat, &A1, &A2);
                                    break;
                                case 2:
                                    AI_Check(data, timestamp, etat, &A2, &A1);
                                    break;
                            }
                        }
                        break;
                    case 3:
                        if(dataNotNull(data,2,4)){
                            switch(data[2][0]){
                                case 'G':
                                    if(strcmp(data[3], ERROR)==0){
                                        voletGauche.erreur++;
                                        if(voletGauche.erreur==3){
                                            sysError(data, 11, timestamp, "ERREUR VOLET GAUCHE");
                                        }
                                    }else{
                                        if(volet_longueur_max(atof(data[3]))==false){
                                            valError(data, 11, timestamp, "ERREUR LONGUEUR MAX G");
                                        }else{
                                            voletGauche.angle = atof(data[3]);
                                            if(volet_ouvert_v2(voletGauche.angle)==1){
                                                mcasSet(false);
                                                voletGauche.etatChange = true;
                                            }
                                            if(voletGauche.etatChange == true && voletDroite.etatChange == true){
                                                if(volet_ouverture_marge_v3(voletGauche.angle, voletDroite.angle)==false){
                                                    valError(data, 11, timestamp, "ERREUR MARGE MAX");
                                                }
                                                voletGauche.etatChange = false;
                                                voletDroite.etatChange = false;
                                            }
                                        }
                                    }
                                    break;
                                case 'D': 
                                    if(strcmp(data[3], ERROR)==0){
                                        voletDroite.erreur++;
                                        if(voletDroite.erreur==3){
                                            sysError(data, 11, timestamp, "ERREUR VOLET DROITE");
                                        }
                                    }else{
                                        if(volet_longueur_max(atof(data[3]))==false){
                                            valError(data, 11, timestamp, "ERREUR LONGUEUR MAX D");
                                        }else{
                                            voletDroite.angle = atof(data[3]);
                                            if(volet_ouvert_v2(voletDroite.angle)==1){
                                                mcasSet(false);
                                                voletDroite.etatChange = true;
                                            }
                                            if(voletGauche.etatChange == true && voletDroite.etatChange == true){
                                                if(volet_ouverture_marge_v3(voletGauche.angle, voletDroite.angle)==0){
                                                    valError(data, 11, timestamp, "ERREUR MARGE MAX");
                                                }
                                                voletGauche.etatChange = false;
                                                voletDroite.etatChange = false;
                                            }
                                        }  
                                    }
                                    break;
                            }
                        }
                        break;
                    case 4:
                        if(dataNotNull(data,2,4)){
                            switch(data[2][0]){
                                case 'G':
                                    SH_Check(data, timestamp, &angleStabilizateurGauche, &angleStabilizateurDroite);
                                    break;
                                case 'D':
                                    SH_Check(data, timestamp, &angleStabilizateurDroite, &angleStabilizateurGauche);
                                    break;
                            }
                        }
                    break;
                    case 5:
                        if(dataNotNull(data,2,4)){
                            
                        }
                    break;
                }
            }
        }
    }
    
    return 0;
}

bool timeIsValid(char* time){
    return atoi(time)>timestamp;
}

bool trxIsValid(char* trx){
    int trxLocal = atoi(trx);
    return (trxLocal >= 1 && trxLocal <= 5);
}

bool capteurValide(char* capteur){
    bool valide=false;
    if(strcmp(capteur,"A1")==0||strcmp(capteur,"A2")==0||strcmp(capteur,"A3")==0){
        valide = true;
    }
    return valide;
}

bool dataNotNull(char* data[],int index, int size){
    bool notNul= true;
    while(index<size){
        if(data[index]==NULL){
            notNul=true;
        }
        index++;
    }
    return notNul;
}

void sysError(char* data[], Systeme_t systeme, time_t time, char* info){
    printf("06 ");
    printf("%i ", systeme);
    printf("%lu ", timestamp);
    printf("%s ", data[2]);
    printf("%s\n", info);
    mcas = mcasSet(false);
}

void valError(char* data[], Systeme_t systeme, time_t time, char* info){
    printf("08 ");
    printf("%i ", systeme);
    printf("%lu ", timestamp);
    printf("%s ", data[2]);
    printf("%s\n", info);
}

bool mcasSet(bool status){
    printf("MCAS ");
    if(status){
        status=true;
        printf("ON\n");
    }else{
        status=false;
        printf("OFF\n");
    }
    return status;
}

bool volet_longueur_max(float volet){
    bool valide = false;
    if(volet>=0.0 && volet <=108.0){
        valide = true;
    }
    return valide;
}

void sysFunction(char* data[], Systeme_t systeme, time_t timestamp){
    
}

void AI_Check(char* data[], time_t time, EtatAppareil_t etat, capteur_AI_t *capteurAngle,
			 capteur_AI_t *capteurSecondaire){
	char* erreurS = "ERREUR ANGLE CONFORME";
	//int angle = data[2][1]-'0');
	float tempCapteur;
	if(strcmp(data[3], ERROR)==0){
		capteurAngle->erreur++;
		if(capteurAngle->erreur==3){
			sysError(data, 13, timestamp, "ERREUR AI");
		}
	}else{
		tempCapteur = atof(data[3]);
		if(tempCapteur<-360 && tempCapteur>360){
			valError(data, 13, timestamp, "ERREUR ANGLE INVALIDE");
		}else{
			if(angle_incidence_marge_v1(tempCapteur, capteurSecondaire->capteur)==0){
				valError(data, 13, timestamp, "ERREUR MARGE INVALIDE");
			}else{
				switch(etat){
					case ETAT_TARMAC:
						if(tarmac_angle_conforme_v1(tempCapteur)==0){
							valError(data, 11, timestamp, erreurS);
						}else{
							capteurAngle->capteur = tempCapteur;
						}
						break;
					case ETAT_DECOLLAGE:
                        printf("%f TEMP CAPTEUR ETAT_DECOLLAGE\n", tempCapteur);
						if(decollage_angle_conforme_v2(tempCapteur)==0){
							valError(data, 11, timestamp, erreurS);
						}else{
							capteurAngle->capteur = tempCapteur;
						}	
						break;
					case ETAT_VOL:
						if(vol_angle_conforme_v3(tempCapteur)==0){
							valError(data, 11, timestamp, erreurS);
						}else{
							capteurAngle->capteur = tempCapteur;
						}
						break;
					case ETAT_ATTERRISSAGE:
						if(atterrissage_angle_conforme_v1(tempCapteur)==0){
							valError(data, 11, timestamp, erreurS);
						}else{
							capteurAngle->capteur = tempCapteur;
						}
					break;
				}
			}
		}
	}
}

void SH_Check(char* data[], time_t timestamp, 
			 capteur_VOL_SH_t *capteurPrimaire, capteur_VOL_SH_t *capteurSecondaire){
	if(strcmp(data[3], ERROR)==0){
		capteurPrimaire->erreur++;
		if(capteurPrimaire->erreur==3){
			sysError(data, 12, timestamp, "ERREUR SH");
		}
	}else{
		if(atof(data[3])<-360 || atof(data[3])>360){
			valError(data, 12, timestamp, "ERREUR DEG");
		}else{
			capteurPrimaire->angle = atof(data[3]);
			if(stabilisateur_horizontal_conforme_v3(capteurPrimaire->angle)==1){
				mcasSet(false);
				capteurPrimaire->etatChange = true;
			}

			if(capteurPrimaire->etatChange == true && capteurSecondaire->etatChange == true){
				if(stabilisateur_horizontal_marge_v3(capteurPrimaire->angle, capteurSecondaire->angle)==false){
					valError(data, 12, timestamp, "ERREUR MARGE MAX");
				}
				capteurPrimaire->etatChange = false;
				capteurSecondaire->etatChange = false;
			}
		}
	}
	
}

//gcc -Wall -pedantic -std=c11 tp2.c flop.o -o tp2
