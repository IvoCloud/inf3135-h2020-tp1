/*
	INF3135 Hiiver 2020
	Ivaylo Ivanov
	TP3 tp3.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "flop.h"
#include "malib.h"

int main(int argc, char *argv[]){
    char message_out[25]="";
    char mcas_msg[25]="";
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
    
    bool etat_tranquille = mode_tranquille(argc, argv);
 	if(!etat_tranquille){
 		printf("Version #: %c.%c.%d",version.major,version.minor,version.build);
 	}
    
    Capteur_t AI_A1 = {"A1",0.0,0,0,true};
    Capteur_t AI_A2 = {"A2",0.0,0,0,true};
    Capteur_t AI_A3 = {"A3",0.0,0,0,false};
    Capteur_t VOL_G = {"G",0.0,0,0,true};
    Capteur_t VOL_D = {"D",0.0,0,0,true};
    Capteur_t SH_G = {"G",0.0,0,0,true};
    Capteur_t SH_D = {"D",0.0,0,0,true};
    Capteur_t capteur_temp;
    
    Info_t infos = {0,0,{0,0,0,0,0},0,0};
    
    //Read input
    while(fgets(input,25,stdin)){
        //Assign to variables
        data[0] = strtok(input," ");
        data[1] = strtok(NULL, " ");
        data[2] = strtok(NULL, " ");
        data[3] = strtok(NULL, " ");
  	//Validate timestamp
        ++infos.trx_recues;
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
                            strcpy(message_out,log_error(&AI_A1,timestamp, AI, AI_A1.id));
                        }else{
                            if(valider_angle_conforme_AI(etat, &AI_A1, timestamp, sensor_valeur)){
                                if(AI_A2.actif){
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, AI_A2.valeur)){
                                        strcpy(message_out,log_error_valeur(&AI_A1, timestamp, AI, "A1_MARGE"));
                                    }else{
                                        AI_A1.valeur = sensor_valeur;
                                        ++infos.trx_valide;
                                    }
                                }else{
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, AI_A3.valeur)){
                                        strcpy(message_out,log_error_valeur(&AI_A1, timestamp, AI, "A1_MARGE"));
                                    }else{
                                        AI_A1.valeur = sensor_valeur;
                                        ++infos.trx_valide;
                                    }
                                }
                            }else{
                                strcpy(message_out,log_error_valeur(&AI_A1, timestamp, AI, AI_A1.id));
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
                            strcpy(message_out,log_error(&AI_A2,timestamp, AI, AI_A2.id));
                        }else{
                           if(valider_angle_conforme_AI(etat, &AI_A2, timestamp, sensor_valeur)){
                                if(AI_A1.actif){
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, AI_A2.valeur)){
                                        strcpy(message_out,log_error_valeur(&AI_A1,timestamp, AI, "A2_MARGE"));
                                    }else{
                                        AI_A2.valeur = sensor_valeur;
                                        ++infos.trx_valide;
                                    }
                                }else{
                                    if(!angle_incidence_marge_v1(AI_A2.valeur, AI_A3.valeur)){
                                        strcpy(message_out,log_error_valeur(&AI_A1,timestamp, AI, "A2_MARGE"));
                                    }else{
                                        AI_A2.valeur = sensor_valeur;
                                        ++infos.trx_valide;
                                    }
                                }
                            }else{
                                strcpy(message_out,log_error_valeur(&AI_A2, timestamp, AI, AI_A2.id));
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
                            strcpy(message_out,log_error(&AI_A3,timestamp, AI, AI_A3.id));
                        }else{
                           if(valider_angle_conforme_AI(etat, &AI_A3, timestamp, sensor_valeur)){
                                if(!AI_A1.actif&&AI_A2.actif){
                                    if(!angle_incidence_marge_v1(AI_A2.valeur, sensor_valeur)){
                                        strcpy(message_out,log_error_valeur(&AI_A3,timestamp, AI, "A3_MARGE"));
                                    }else{
                                        AI_A3.valeur = sensor_valeur;
                                        ++infos.trx_valide;
                                    }
                                }else if(!AI_A2.actif&&AI_A1.actif){
                                    if(!angle_incidence_marge_v1(AI_A1.valeur, sensor_valeur)){
                                        strcpy(message_out,log_error_valeur(&AI_A3,timestamp, AI, "A3_MARGE"));
                                    }else{
                                        AI_A3.valeur = sensor_valeur;
                                        ++infos.trx_valide;
                                    }
                                }
                            }else{
                                strcpy(message_out,log_error_valeur(&AI_A3, timestamp, AI, AI_A3.id));
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
                            strcpy(message_out,log_error(&capteur_temp,timestamp, VOLET, capteur_temp.id));
                        }else{
                            sensor_valeur = atof(data[3]);
                            if(capteur_temp.actif&&valider_angle_conforme_VOL(&capteur_temp, timestamp, sensor_valeur)){
                                if(!(volet_ouverture_marge_v3(sensor_valeur, VOL_D.valeur)&&
                                volet_ouverture_marge_v3(sensor_valeur, VOL_G.valeur))){
                                    char info[7] = "MARGE ";
                                    strcat(info, capteur_temp.id);
                                    strcpy(message_out,log_error_valeur(&capteur_temp, timestamp, VOLET, info));
                                }else{
                                    ++infos.trx_valide;
                                    capteur_temp.valeur = sensor_valeur;
                                    if(volet_ouvert_v2(capteur_temp.valeur)){
                                        strcpy(mcas_msg, set_mcas("OFF", &mcas));
                                    }else if(sys_en_erreur<2){
                                        strcpy(mcas_msg, set_mcas("ON", &mcas));
                                    }
                                }
                            }else if(capteur_temp.actif){
                                strcpy(message_out,log_error_valeur(&capteur_temp, timestamp, 11, capteur_temp.id));
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
                        if((strcmp(data[3],ERROR)==0)||(strcmp(data[3],"ERROR")==0)&&(SH_D.actif||SH_G.actif)){
                            strcpy(message_out,log_error(&capteur_temp,timestamp, SH, capteur_temp.id));
                        }else{
                            sensor_valeur = atof(data[3]);
                            if(capteur_temp.actif&&valider_angle_conforme_SH(&capteur_temp, timestamp, sensor_valeur)){
                                if(!(stabilisateur_horizontal_marge_v3(sensor_valeur, SH_D.valeur)&&
                                stabilisateur_horizontal_marge_v3(sensor_valeur, SH_G.valeur))){
                                    char info[7] = "MARGE ";
                                    strcat(info, capteur_temp.id);
                                    strcpy(message_out,log_error_valeur(&capteur_temp, timestamp, SH, info));
                                }else{
                                    capteur_temp.valeur = sensor_valeur;
                                    ++infos.trx_valide;
                                }
                            }else if(capteur_temp.actif){
                                    strcpy(message_out,log_error_valeur(&capteur_temp, timestamp, 12, capteur_temp.id));
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
                                strcpy(message_out,set_actif(&VOL_G,&VOL_D, timestamp, VOLET));
                                --sys_en_erreur;
                                if(sys_en_erreur<2){
                                    strcpy(mcas_msg, set_mcas("ON", &mcas));
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
                                strcpy(message_out,set_actif(&SH_G,&SH_D, timestamp, SH));
                                --sys_en_erreur;
                                if(sys_en_erreur<2){
                                    strcpy(mcas_msg,set_mcas("ON", &mcas));
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
                                strcpy(message_out,set_actif(&AI_A1,&AI_A2, timestamp, AI));
                                AI_A3.actif = true;
                                --sys_en_erreur;
                                if(sys_en_erreur<2){
                                    strcpy(mcas_msg,set_mcas("ON", &mcas));
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
                ++infos.trx_types[transaction-1];
                if(sys_en_erreur>=2&&mcas){
                    strcpy(mcas_msg,set_mcas("OFF", &mcas));
                }
            }else{
                ++infos.trx_non_valide;
            }//validation_format_transaction
        }else{
            ++infos.err_time;
        }
        if(!etat_tranquille){
            printf("%s", message_out);
            printf("%s", mcas_msg);
        }
        strcpy(message_out,"");
        strcpy(mcas_msg,"");
    }//while read
    cmd(argc,argv,&infos);
}

