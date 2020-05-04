#ifndef __MALIB_H__
#define __MALIB_H__

typedef unsigned long int time_tp;

typedef enum {VOLET=11,SH,AI}Sensor_t;

typedef struct{
    char id[5];
    float valeur;
    int erreurs;
    int erreurs_valeur;
    bool actif;
}Capteur_t;

void log_error(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info);

void log_error_valeur(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info);

void set_inactif(Capteur_t* capteur1, Capteur_t* capteur2);

void set_actif(Capteur_t* capteur1, Capteur_t* capteur2, time_tp timestamp, Sensor_t sensor);

bool set_mcas(char* status);

bool volet_conforme(float longueur);

bool valider_angle_conforme_AI(EtatAppareil_t etat, float valeur);

bool validation_format_transaction(char* data[4]);

bool validation_timestamp(char* time, time_tp timestamp);

#endif // __MALIB_H__