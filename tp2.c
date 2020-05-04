/*
	INF3135 Hiiver 2020
	Ivaylo Ivanov
	TP2 tp2.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./data/flop.h"
#include "malib.h"

int main(){
    bool mcas = true;
    static char* ERROR = "ERROR\n";
    char* data[4];
    char input[25];
    time_tp timestamp = 0;
    EtatAppareil_t etat = 0;
    float sensor_valeur = 0.0;
    int sys_en_erreur=0;
    int transaction;
	
 	version_t version;
  	flop_version(&version);
    
    Capteur_t AI_A1 = {"A1",0.0,0,0,true};
    Capteur_t AI_A2 = {"A2",0.0,0,0,true};
    Capteur_t AI_A3 = {"A3",0.0,0,0,false};
    Capteur_t VOL_G = {"G",0.0,0,0,true};
    Capteur_t VOL_D = {"D",0.0,0,0,true};
    Capteur_t SH_G = {"G",0.0,0,0,true};
    Capteur_t SH_D = {"D",0.0,0,0,true};
    Capteur_t capteur_temp;
    
    //Read input
    while(fgets(input,25,stdin)){
        //Assign to variables
        data[0] = strtok(input," ");
        data[1] = strtok(NULL, " ");
        data[2] = strtok(NULL, " ");
        data[3] = strtok(NULL, " ");
  	//Validate timestamp
        if(validation_timestamp(data[0],timestamp)){
            timestamp = atoi(data[0]);
      //Handle trx num
            if(validation_format_transaction(data)){
                transaction = atoi(data[1]);
                if(transaction==1&&validation_etat_appareil_v3(atoi(data[2]))){
                //TRX 01
                        etat = atoi(data[2]);
                }else if(transaction==2){
                //TRX 02 Read AI
                    sensor_valeur = atof(data[3]);
                    if((strcmp(data[2],"A1")==0)&&AI_A1.actif){
                        if((strcmp(data[3],ERROR)==0)||(strcmp(data[3],"ERROR")==0)){
                            log_error(&AI_A1,timestamp, AI, AI_A1.id);
                        }else{
                            if(valider_angle_conforme_AI(etat, sensor_valeur)){
                                if(AI_A2.actif){
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, AI_A2.valeur)){
                                        log_error_valeur(&AI_A1, timestamp, AI, "A1_MARGE");
                                    }else{
                                        AI_A1.valeur = sensor_valeur;
                                    }
                                }else{
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, AI_A3.valeur)){
                                        log_error_valeur(&AI_A1, timestamp, AI, "A1_MARGE");
                                    }else{
                                        AI_A1.valeur = sensor_valeur;
                                    }
                                }
                            }else{
                                log_error_valeur(&AI_A1, timestamp, AI, AI_A1.id);
                            }
                        }
                        if(AI_A1.erreurs==3&&(AI_A2.erreurs==3||AI_A3.erreurs==3)){
                            ++sys_en_erreur;
                            AI_A1.actif = false;
                            AI_A2.actif = false;
                            AI_A3.actif = false;
                        }
                    }else if((strcmp(data[2],"A2")==0)&&AI_A2.actif){
					//02 A2
                        if((strcmp(data[3],ERROR)==0)||(strcmp(data[3],"ERROR")==0)){
                            log_error(&AI_A2,timestamp, AI, AI_A2.id);
                        }else{
                           if(valider_angle_conforme_AI(etat, sensor_valeur)){
                                if(AI_A1.actif){
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, AI_A2.valeur)){
                                        log_error_valeur(&AI_A1,timestamp, AI, "A2_MARGE");
                                    }else{
                                        AI_A2.valeur = sensor_valeur;
                                    }
                                }else{
                                    if(!angle_incidence_marge_v1(AI_A2.valeur, AI_A3.valeur)){
                                        log_error_valeur(&AI_A1,timestamp, AI, "A2_MARGE");
                                    }else{
                                        AI_A2.valeur = sensor_valeur;
                                    }
                                }
                            }else{
                                log_error_valeur(&AI_A2, timestamp, AI, AI_A2.id);
                            }
                        }
                        if(AI_A2.erreurs==3&&(AI_A1.erreurs==3||AI_A3.erreurs==3)){
                            ++sys_en_erreur;
                            AI_A1.actif = false;
                            AI_A2.actif = false;
                            AI_A3.actif = false;
                        }
                    }else if(strcmp(data[2],"A3")==0){
					//02 A3
                        if((strcmp(data[3],ERROR)==0)||(strcmp(data[3],"ERROR")==0)){
                            log_error(&AI_A3,timestamp, AI, AI_A3.id);
                        }else{
                           if(valider_angle_conforme_AI(etat, sensor_valeur)){
                                if(!AI_A1.actif&&AI_A2.actif){
                                    if(!angle_incidence_marge_v1(AI_A2.valeur, sensor_valeur)){
                                        log_error_valeur(&AI_A3,timestamp, AI, "A3_MARGE");
                                    }else{
                                        AI_A3.valeur = sensor_valeur;
                                    }
                                }else if(!AI_A2.actif&&AI_A1.actif){
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, sensor_valeur)){
                                        log_error_valeur(&AI_A3,timestamp, AI, "A3_MARGE");
                                    }else{
                                        AI_A3.valeur = sensor_valeur;
                                    }
                                }
                            }else{
                                log_error_valeur(&AI_A3, timestamp, AI, AI_A3.id);
                            }
                        }
                        if(AI_A3.erreurs==3&&(AI_A2.erreurs==3||AI_A1.erreurs==3)){
                            ++sys_en_erreur;
                            AI_A1.actif = false;
                            AI_A2.actif = false;
                            AI_A3.actif = false;
                        }
                    }
                }else if(transaction==3){
                //TRX 03
                    if(VOL_G.actif&&VOL_D.actif){
                        if((strcmp(data[2],"G")==0)){
                            capteur_temp = VOL_G;
                        }else if((strcmp(data[2],"D")==0)){
                            capteur_temp = VOL_D;
                        }
                        if(strcmp(data[3],ERROR)==0||strcmp(data[3],"ERROR")==0){
                            log_error(&capteur_temp,timestamp, VOLET, capteur_temp.id);
                        }else{
                            sensor_valeur = atof(data[3]);
                            if(capteur_temp.actif&&volet_conforme(sensor_valeur)){
                                if(!(volet_ouverture_marge_v3(sensor_valeur, VOL_D.valeur)&&
                                volet_ouverture_marge_v3(sensor_valeur, VOL_G.valeur))){
                                    char info[7] = "MARGE ";
                                    strcat(info, capteur_temp.id);
                                    log_error_valeur(&capteur_temp, timestamp, VOLET, info);
                                }else{
                                    capteur_temp.valeur = sensor_valeur;
                                    if(volet_ouvert_v2(capteur_temp.valeur)){
                                        mcas = set_mcas("OFF");
                                    }else if(sys_en_erreur<2){
                                        mcas = set_mcas("ON");
                                    }
                                }
                            }else if(capteur_temp.actif){
                                log_error_valeur(&capteur_temp, timestamp, 11, capteur_temp.id);
                            }
                        }
                        if(strcmp(data[2],"G")==0){
                            VOL_G = capteur_temp;
                        }else if(strcmp(data[2],"D")==0){
                            VOL_D = capteur_temp;
                        }
                        if(VOL_G.erreurs==3||VOL_D.erreurs==3){
                            ++sys_en_erreur;
                            set_inactif(&VOL_D,&VOL_G);
                        }
                    }
                }else if(transaction==4){
                //TRX 04
                    if(SH_G.actif&&SH_D.actif){
                        if((strcmp(data[2],"G")==0)&&SH_G.actif){
                            capteur_temp = SH_G;
                        }else if((strcmp(data[2],"D")==0)&&SH_D.actif){
                            capteur_temp = SH_D;
                        }
                        if(((strcmp(data[3],ERROR)==0)||(strcmp(data[3],"ERROR")==0))&&(SH_D.actif||SH_G.actif)){
                            log_error(&capteur_temp,timestamp, SH, capteur_temp.id);
                        }else{
                            sensor_valeur = atof(data[3]);
                            if(capteur_temp.actif&&stabilisateur_horizontal_conforme_v3(sensor_valeur)){
                                if(!(stabilisateur_horizontal_marge_v3(sensor_valeur, SH_D.valeur)&&
                                stabilisateur_horizontal_marge_v3(sensor_valeur, SH_G.valeur))){
                                    char info[7] = "MARGE ";
                                    strcat(info, capteur_temp.id);
                                    log_error_valeur(&capteur_temp, timestamp, SH, info);
                                }else{
                                    capteur_temp.valeur = sensor_valeur;
                                }
                            }else if(capteur_temp.actif){
                                    log_error_valeur(&capteur_temp, timestamp, 12, capteur_temp.id);
                            }
                        }
                        if(strcmp(data[2],"G")==0){
                            SH_G = capteur_temp;
                        }else if(strcmp(data[2],"D")==0){
                            SH_D = capteur_temp;
                        }
                        if(SH_G.erreurs==3||SH_D.erreurs==3){
                            ++sys_en_erreur;
                            set_inactif(&SH_D,&SH_G);
                        }
                    }
                }else{
                    switch(atoi(data[2])){
                        case 11://VOL
                            if(atoi(data[3])==0){
                                set_actif(&VOL_G,&VOL_D, timestamp, VOLET);
                                --sys_en_erreur;
                                if(sys_en_erreur<2){
                                    mcas = set_mcas("ON");
                                }
                            }else{
                                ++VOL_G.erreurs;
                                ++VOL_D.erreurs;
                                if(VOL_D.erreurs==3||VOL_G.erreurs==3){
                                    set_inactif(&VOL_G,&VOL_D);
                                    if(sys_en_erreur<2){
                                        ++sys_en_erreur;
                                    }
                                }
                            }
                        break;
                        case 12://SH
                            if(atoi(data[3])==0){
                                set_actif(&SH_G,&SH_D, timestamp, SH);
                                --sys_en_erreur;
                                if(sys_en_erreur<2){
                                    mcas = set_mcas("ON");
                                }
                            }else{
                                ++SH_G.erreurs;
                                ++SH_D.erreurs;
                                if(SH_D.erreurs==3||SH_G.erreurs==3){
                                    set_inactif(&SH_D,&SH_G);
                                    if(sys_en_erreur<3){
                                        ++sys_en_erreur;
                                    }
                                }
                            }
                        break;
                        case 13://AI
                            if(atoi(data[3])==0){
                                set_actif(&AI_A1,&AI_A2, timestamp, AI);
                                AI_A3.actif = true;
                                --sys_en_erreur;
                                if(sys_en_erreur<2){
                                    mcas = set_mcas("ON");
                                }
                            }else{
                                if((AI_A1.erreurs==3||AI_A2.erreurs==3)&&AI_A3.erreurs==3){
                                    set_inactif(&AI_A1,&AI_A2);
                                    AI_A3.actif = false;
                                    if(sys_en_erreur<2){
                                        ++sys_en_erreur;
                                    }
                                }
                            }
                        break;
                    }
                }//MAIN LOOP
                if(sys_en_erreur>=2&&mcas){
                    mcas = set_mcas("OFF");
                }
            }else{
            }//validation_format_transaction
        }else{
        }
    }//while read
}

