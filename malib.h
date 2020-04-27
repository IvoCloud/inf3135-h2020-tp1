typedef unsigned long int time_tp;

typedef enum {VOLET=11,SH,AI}Sensor_t;

typedef struct{
    char id[5];
    float valeur;
    int erreurs;
    int erreurs_valeur;
    bool actif;
}Capteur_t;

typedef struct {
    int trx_non_valide;
    int err_time;
    int trx_types[5];
    int trx_valide;
    int trx_recues;
}Info_t;

char* log_error(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info);

char* log_error_valeur(Capteur_t* capteur, time_tp timestamp, Sensor_t sensor, char* info);

void set_inactif(Capteur_t* capteur1, Capteur_t* capteur2);

char* set_actif(Capteur_t* capteur1, Capteur_t* capteur2, time_tp timestamp, Sensor_t sensor);

char* set_mcas(char* status, bool* mcas);

bool volet_conforme(float longueur);

bool valider_angle_conforme_AI(EtatAppareil_t etat, Capteur_t* capteur,time_tp timestamp, float valeur);

bool valider_angle_conforme_SH(Capteur_t* capteur, time_tp timestamp, float valeur);

bool valider_angle_conforme_VOL(Capteur_t* capteur, time_tp timestamp, float valeur);

bool validation_format_transaction(char* data[4]);

bool validation_timestamp(char* time, time_tp timestamp);

void cmd(int argc,char* argv[], Info_t* info);

bool mode_tranquille(int argc, char* argv[]);

