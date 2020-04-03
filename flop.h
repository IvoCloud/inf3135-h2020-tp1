#ifndef __FLOP_H__
#define __FLOP_H__

/* @file flop.h
 * @brief Entête des fonctions de la librairie flop
 * @author Alexandre Lachapelle (copyright 2019-2020 Guy Francoeur)
 * @date 2020-03-12
 * @warning 0.0.10008
 * @version 0.0.10008
 * @see http://github.com/guyfrancoeur/INF3135_H2020/README.md
 * @defgroup lib Librairie flop
 */

#include <stdbool.h>

enum EtatAppareil {ETAT_TARMAC = 0, ETAT_DECOLLAGE, ETAT_VOL, ETAT_ATTERRISSAGE, ETAT_ETEINT };
typedef enum EtatAppareil EtatAppareil_t;

typedef struct version_s {
  unsigned char major;
  unsigned char minor;
  unsigned int  build;
} version_t;

/* addtogroup lib
 * @brief Fonction qui indique la version de la librairie
 * @param Un pointeur de struct version_s ou version_t
 * @return void
 */
void flop_version(version_t *v);

/* @defgroup etat
 * @defgroup validation_etat_appareil
 * @brief Regroupe les fonctions de validation d'état de vol de l'appareil
 *
 * Ces fonctions valident si l'état passé en paramètre est un des états valide de l'appareil.
 * @{
 */
bool validation_etat_appareil_v1(EtatAppareil_t etat);
bool validation_etat_appareil_v2(EtatAppareil_t etat);
bool validation_etat_appareil_v3(EtatAppareil_t etat);
/** @}*/ // Fin groupe validation_etat_appareil

/* @defgroup angle_incidence_marge
 * @brief Regroupe les fonctions de validation de cohérence entre deux capteurs d'angle d'incidence
 *
 * Ces fonctions évaluent si les valeurs des deux capteurs d'angle d'incidence sont cohérents
 * (les valeurs ne sont pas trop éloignées l'une de l'autre).
 * @{
 */
bool angle_incidence_marge_v1(float angle1, float angle2);
bool angle_incidence_marge_v2(float angle1, float angle2);
bool angle_incidence_marge_v3(float angle1, float angle2);
/** @}*/ // Fin groupe angle_incidence_marge

/* @addtogroup etat
 * @defgroup Tarmac
 * @brief Regroupe les fonctions de validation de l'angle d'incidence de l'appareil pour l'etat Tarmac
 * Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil sur le tarmac.
 * @{
 */
bool tarmac_angle_conforme_v1(float angle);
bool tarmac_angle_conforme_v2(float angle);
bool tarmac_angle_conforme_v3(float angle);
/** @}*/ // Fin groupe Tarmac

/* @addtogroup etat
 * @defgroup Decollage
 * @brief Regroupe les fonctions de validation de l'angle d'incidence de l'appareil pour l'etat décollage
 * Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil en décollage.
 * @{
 */
bool decollage_angle_conforme_v1(float angle);
bool decollage_angle_conforme_v2(float angle);
bool decollage_angle_conforme_v3(float angle);
/** @}*/ // Fin groupe Decollage

/* @addtogroup etat
 * @defgroup Vol
 * @brief Regroupe les fonctions de validation de l'angle d'incidence de l'appareil pour l'etat vol
 * Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil en vol.
 * @{
 */
bool vol_angle_conforme_v1(float angle);
bool vol_angle_conforme_v2(float angle);
bool vol_angle_conforme_v3(float angle);
/** @}*/ // Fin groupe Vol

/* @addtogroup etat
 * @defgroup Atterrissage
 * @brief Regroupe les fonctions de validation de l'angle d'incidence de l'appareil pour l'etat atterrissage
 * Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil en atterrissage.
 * @{
 */
bool atterrissage_angle_conforme_v1(float angle);
bool atterrissage_angle_conforme_v2(float angle);
bool atterrissage_angle_conforme_v3(float angle);
/** @}*/ // Fin groupe Atterrissage

/* @defgroup volet_ouvert
 * @brief Regroupe les fonctions qui valident si les volets sont considérés ouverts ou fermés.
 * Ces fonctions indiquent si les volets de l'appareil sont ouverts ou non dépendant de longueur déployée.
 * @{
 */
bool volet_ouvert_v1(float longueur);
bool volet_ouvert_v2(float longueur);
bool volet_ouvert_v3(float longueur);
/** @}*/ // Fin groupe Volet_Ouvert

/* @addtogroup marge
 * @defgroup volet_ouverture_marge
 * @brief Regroupe les fonctions qui valident si les volets sont considérés ouverts ou fermés.
 * Ces fonctions évaluent si les valeurs des deux capteurs d'ouverture des volets sont cohérents
 * (les valeurs ne sont pas trop éloignées l'une de l'autre).
 * @{
 */
bool volet_ouverture_marge_v1(float longGauche, float longDroite);
bool volet_ouverture_marge_v2(float longGauche, float longDroite);
bool volet_ouverture_marge_v3(float longGauche, float longDroite);
/** @}*/ // Fin groupe volet_ouverture_marge

/* @defgroup stabilisateur_horizontal_marge
 * @brief Regroupe les fonctions de validation des valeurs des capteurs du stabilisateur horizontal
 * Ces fonctions évaluent si les valeurs des deux capteurs du stabilisateur horizontal sont cohérents
 * (les valeurs ne sont pas trop éloignées l'une de l'autre).
 * @{
 */
bool stabilisateur_horizontal_marge_v1(float gauche, float droite);
bool stabilisateur_horizontal_marge_v2(float gauche, float droite);
bool stabilisateur_horizontal_marge_v3(float gauche, float droite);
/** @}*/ // Fin groupe stabilisateurs_horizontal_marge

/* @defgroup stabilisateur_horizontal_conforme
 * @brief Regroupe les fonctions de validation de l'angle du stabilisateur horizontal
 * Ces fonctions valident si l'angle du stabilisateur horizontal est sous le seuil critique.
 * @{
 */
bool stabilisateur_horizontal_conforme_v1(float angle);
bool stabilisateur_horizontal_conforme_v2(float angle);
bool stabilisateur_horizontal_conforme_v3(float angle);
/** @}*/ // Fin groupe stabilisateurs_horizontal_conforme

#endif // __FLOP_H__
