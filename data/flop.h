#ifndef __FLOP_H__
#define __FLOP_H__

/*!  \file flop.h
     \brief Entête des fonctions de la librairie flop
     \author Alexandre Lachapelle
 */

#include <stdbool.h>

enum EtatAppareil {ETAT_TARMAC = 0, ETAT_DECOLLAGE, ETAT_VOL, ETAT_ATTERRISSAGE, ETAT_ETEINT };
typedef enum EtatAppareil EtatAppareil_t;

/*! \defgroup Etat_Appareil
    Regroupe les fonctions de validation d'état de vol de l'appareil
    Ces fonctions valident si l'état passé en paramètre est un des états valide de l'appareil.
    @{
 */
bool validation_etat_appareil_v1(EtatAppareil_t etat);
bool validation_etat_appareil_v2(EtatAppareil_t etat);
bool validation_etat_appareil_v3(EtatAppareil_t etat);
/*! @}*/ // Fin groupe Etat_Appareil

/*! \defgroup Angles_Incidence_Marge
    Regroupe les fonctions de validation de cohérence entre les deux capteurs d'angle d'incidence
    Ces fonctions évaluent si les valeurs des deux capteurs d'angle d'incidence sont cohérents
    (les valeurs ne sont pas trop éloignées l'une de l'autre).
    @{
 */
bool angle_incidence_marge_v1(float angle1, float angle2);
bool angle_incidence_marge_v2(float angle1, float angle2);
bool angle_incidence_marge_v3(float angle1, float angle2);
/*! @}*/ // Fin groupe Angles_Incidence_Marge

/*! \defgroup Tarmac
    Regroupe les fonctions de validation de l'angle d'incidence de l'appareil sur le Tarmac
    Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil sur le tarmac.
    @{
 */
bool tarmac_angle_conforme_v1(float angle);
bool tarmac_angle_conforme_v2(float angle);
bool tarmac_angle_conforme_v3(float angle);
/*! @}*/ // Fin groupe Tarmac

/*! \defgroup Decollage
    Regroupe les fonctions de validation de l'angle d'incidence de l'appareil lors du décollage
    Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil en décollage.
    @{
 */
bool decollage_angle_conforme_v1(float angle);
bool decollage_angle_conforme_v2(float angle);
bool decollage_angle_conforme_v3(float angle);
/*! @}*/ // Fin groupe Decollage

/*! \defgroup Vol
    Regroupe les fonctions de validation de l'angle d'incidence de l'appareil en vol
    Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil en vol.
    @{
 */
bool vol_angle_conforme_v1(float angle);
bool vol_angle_conforme_v2(float angle);
bool vol_angle_conforme_v3(float angle);
/*! @}*/ // Fin groupe Vol

/*! \defgroup Atterrissage
    Regroupe les fonctions de validation de l'angle d'incidence de l'appareil lors de l'atterrissage
    Ces fonctions valident si l'angle d'incidence passé en paramètre est normal pour un appareil en atterrissage.
    @{
 */
bool atterrissage_angle_conforme_v1(float angle);
bool atterrissage_angle_conforme_v2(float angle);
bool atterrissage_angle_conforme_v3(float angle);
/*! @}*/ // Fin groupe Atterrissage

/*! \defgroup Volet_Ouvert
    Regroupe les fonctions qui valident si les volets sont considérés ouverts ou fermés.
    Ces fonctions indiquent si les volets de l'appareil sont ouverts ou non dépendant de longueur déployée.
    @{
 */
bool volet_ouvert_v1(float longueur);
bool volet_ouvert_v2(float longueur);
bool volet_ouvert_v3(float longueur);
/*! @}*/ // Fin groupe Volet_Ouvert

/*! \defgroup Volet_Ouverture_Marge
    Regroupe les fonctions qui valident si les volets sont considérés ouverts ou fermés.
    Ces fonctions évaluent si les valeurs des deux capteurs d'ouverture des volets sont cohérents
    (les valeurs ne sont pas trop éloignées l'une de l'autre).
    @{
 */
bool volet_ouverture_marge_v1(float longGauche, float longDroite);
bool volet_ouverture_marge_v2(float longGauche, float longDroite);
bool volet_ouverture_marge_v3(float longGauche, float longDroite);
/*! @}*/ // Fin groupe Volet_Ouverture_Marge

/*! \defgroup Volet_Angle_Marge
    Regroupe les fonctions de validation des capteurs d'angle des volets
    Ces fonctions évaluent si les valeurs des deux capteurs de l'angle des volets sont cohérents
    (les valeurs ne sont pas trop éloignées l'une de l'autre).
    @{
 */
bool volet_angle_marge_v1(float angle1, float angle2);
bool volet_angle_marge_v2(float angle1, float angle2);
bool volet_angle_marge_v3(float angle1, float angle2);
/*! @}*/ // Fin groupe Volet_Angle_Marge

/*! \defgroup Volet_Angle_Conforme
    Regroupe les fonctions de validation de l'angle des volets
    Ces fonctions valident si l'angle des volets est sécuritaire
    @{
 */
//attention todo
//bool volet_angle_conforme_v1(float angle);
//bool volet_angle_conforme_v2(float angle);
//bool volet_angle_conforme_v3(float angle);
/*! @}*/ // Fin groupe Volet_Angle_Conforme

/*! \defgroup Stabilisateur_Horizontal_Marge
    Regroupe les fonctions de validation des valeurs des capteurs du stabilisateur horizontal
    Ces fonctions évaluent si les valeurs des deux capteurs du stabilisateur horizontal sont cohérents
    (les valeurs ne sont pas trop éloignées l'une de l'autre).
    @{
 */
bool stabilisateur_horizontal_marge_v1(float gauche, float droite);
bool stabilisateur_horizontal_marge_v2(float gauche, float droite);
bool stabilisateur_horizontal_marge_v3(float gauche, float droite);
/*! @}*/ // Fin groupe Stabilisateurs_Hor_Marge

/*! \defgroup Stabilisateur_Horizontal_Conforme
    Regroupe les fonctions de validation de l'angle du stabilisateur horizontal
    Ces fonctions valident si l'angle du stabilisateur horizontal est sous le seuil critique.
    @{
 */
bool stabilisateur_horizontal_conforme_v1(float angle);
bool stabilisateur_horizontal_conforme_v2(float angle);
bool stabilisateur_horizontal_conforme_v3(float angle);
/*! @}*/ // Fin groupe Stabilisateurs_Hor_Conforme

#endif // __FLOP_H__
