//tp1.c
#include "Basic.h"       // mode de base
#include "flop.h"         // declaration de mes fonctions
#include <stdio.h>       // printf

/*****  LES fonctions qui initialise et detruit la "Suite de test" ******/

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/********************* NOS fonctions de tests *********************/
/*
void test_case_exemple(void)
{
   // Les types d'assertions disponibles
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}
*/

EtatAppareil_t tarmac = ETAT_TARMAC;
EtatAppareil_t decollage = ETAT_DECOLLAGE;
EtatAppareil_t vol = ETAT_VOL;
EtatAppareil_t atterrissage = ETAT_ATTERRISSAGE;
EtatAppareil_t eteint = ETAT_ETEINT;

void test_validation_etat_appareil_v1(void) {
  CU_ASSERT( validation_etat_appareil_v1(tarmac));
  CU_ASSERT( validation_etat_appareil_v1(decollage));
  CU_ASSERT( validation_etat_appareil_v1(vol));
  CU_ASSERT( validation_etat_appareil_v1(atterrissage));
  CU_ASSERT( validation_etat_appareil_v1(eteint));
}

void test_validation_etat_appareil_v2(void) {
  CU_ASSERT( validation_etat_appareil_v1(tarmac));
  CU_ASSERT( validation_etat_appareil_v1(decollage));
  CU_ASSERT( validation_etat_appareil_v1(vol));
  CU_ASSERT( validation_etat_appareil_v1(atterrissage));
  CU_ASSERT( validation_etat_appareil_v1(eteint));
}

void test_validation_etat_appareil_v3(void) {
  CU_ASSERT( validation_etat_appareil_v1(tarmac));
  CU_ASSERT( validation_etat_appareil_v1(decollage));
  CU_ASSERT( validation_etat_appareil_v1(vol));
  CU_ASSERT( validation_etat_appareil_v1(atterrissage));
  CU_ASSERT( validation_etat_appareil_v1(eteint));
}

void test_angle_incidence_marge_v1(void) {
  CU_ASSERT( angle_incidence_marge_v1( 0.2, 0.1));
  CU_ASSERT( angle_incidence_marge_v1(-0.2, 0.0));
  CU_ASSERT( !angle_incidence_marge_v1(-0.5, 0.0));
  CU_ASSERT( !angle_incidence_marge_v1(-0.1, 0.4));
}

void test_angle_incidence_marge_v2(void) {
  CU_ASSERT( angle_incidence_marge_v2( 0.2, 0.1));
  CU_ASSERT( angle_incidence_marge_v2(-0.2, 0.0));
  CU_ASSERT( !angle_incidence_marge_v2(-0.5, 0.0));
  CU_ASSERT( !angle_incidence_marge_v2(-0.1, 0.4));
}

void test_angle_incidence_marge_v3(void) {
  CU_ASSERT( angle_incidence_marge_v3( 0.2, 0.1));
  CU_ASSERT( angle_incidence_marge_v3(-0.2, 0.0));
  CU_ASSERT( !angle_incidence_marge_v3(-0.5, 0.0));
  CU_ASSERT( !angle_incidence_marge_v3(-0.1, 0.4));
}

void test_tarmac_angle_conforme_v1(void) {
  CU_ASSERT( tarmac_angle_conforme_v1( 0.2));
  CU_ASSERT( !tarmac_angle_conforme_v1( 0.4));
  CU_ASSERT( tarmac_angle_conforme_v1( 0.0));
  CU_ASSERT( tarmac_angle_conforme_v1( -0.2));
}

void test_tarmac_angle_conforme_v2(void) {
  CU_ASSERT( tarmac_angle_conforme_v2( 0.2));
  CU_ASSERT( !tarmac_angle_conforme_v2( 0.4));
  CU_ASSERT( tarmac_angle_conforme_v2( 0.0));
  CU_ASSERT( tarmac_angle_conforme_v2( -0.2));
}

void test_tarmac_angle_conforme_v3(void) {
  CU_ASSERT( tarmac_angle_conforme_v3( 0.2));
  CU_ASSERT( !tarmac_angle_conforme_v3( 0.4));
  CU_ASSERT( tarmac_angle_conforme_v3( 0.0));
  CU_ASSERT( tarmac_angle_conforme_v3( -0.2));
}

void test_volet_ouvert_v1(void) {
  CU_ASSERT( volet_ouvert_v1(-9.0));
  CU_ASSERT( volet_ouvert_v1(-0.3));
  CU_ASSERT( volet_ouvert_v1(0.2));
  CU_ASSERT( volet_ouvert_v1(8.4));
  CU_ASSERT( volet_ouvert_v1(9.1));
  CU_ASSERT( volet_ouvert_v1(10.0));
}

void test_volet_ouvert_v2(void) {
  CU_ASSERT( volet_ouvert_v2(-9.0));
  CU_ASSERT( volet_ouvert_v2(-0.3));
  CU_ASSERT( volet_ouvert_v2(0.2));
  CU_ASSERT( volet_ouvert_v2(8.4));
  CU_ASSERT( volet_ouvert_v2(9.1));
  CU_ASSERT( volet_ouvert_v2(10.0));
}

void test_volet_ouvert_v3(void) {
  CU_ASSERT( volet_ouvert_v3(-9.0));
  CU_ASSERT( volet_ouvert_v3(-0.3));
  CU_ASSERT( volet_ouvert_v3(0.2));
  CU_ASSERT( volet_ouvert_v3(8.4));
  CU_ASSERT( volet_ouvert_v3(9.1));
  CU_ASSERT( volet_ouvert_v3(10.0));
}

void test_stabilisateur_horizontal_conforme_v1(void) {
  CU_ASSERT( stabilisateur_horizontal_conforme_v1(0.1));
  CU_ASSERT( stabilisateur_horizontal_conforme_v1(0.2));
  CU_ASSERT( stabilisateur_horizontal_conforme_v1(0.3));
  CU_ASSERT( !stabilisateur_horizontal_conforme_v1(0.4));
}

void test_stabilisateur_horizontal_conforme_v2(void) {
  CU_ASSERT( stabilisateur_horizontal_conforme_v2(0.1));
  CU_ASSERT( stabilisateur_horizontal_conforme_v2(0.2));
  CU_ASSERT( stabilisateur_horizontal_conforme_v2(0.3));
  CU_ASSERT( !stabilisateur_horizontal_conforme_v2(0.4));
}

void test_stabilisateur_horizontal_conforme_v3(void) {
  CU_ASSERT( stabilisateur_horizontal_conforme_v3(0.1));
  CU_ASSERT( stabilisateur_horizontal_conforme_v3(0.2));
  CU_ASSERT( stabilisateur_horizontal_conforme_v3(0.3));
  CU_ASSERT( !stabilisateur_horizontal_conforme_v3(0.4));
}

/************* Nous debutons l'execution des tests **************/

int main ( void )
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite( "737_max_test_suite", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if ( 
	(NULL == CU_add_test(pSuite, "test_validation_etat_appareil_v1", test_validation_etat_appareil_v1)) ||
        (NULL == CU_add_test(pSuite, "test_validation_etat_appareil_v2", test_validation_etat_appareil_v2)) ||
        (NULL == CU_add_test(pSuite, "test_validation_etat_appareil_v3", test_validation_etat_appareil_v3)) ||
	(NULL == CU_add_test(pSuite, "test_angle_incidence_marge_v1", test_angle_incidence_marge_v1)) ||
	(NULL == CU_add_test(pSuite, "test_angle_incidence_marge_v2", test_angle_incidence_marge_v2)) ||
	(NULL == CU_add_test(pSuite, "test_angle_incidence_marge_v3", test_angle_incidence_marge_v3)) ||
	(NULL == CU_add_test(pSuite, "test_tarmac_angle_conforme_v1", test_tarmac_angle_conforme_v1)) ||
        (NULL == CU_add_test(pSuite, "test_tarmac_angle_conforme_v2", test_tarmac_angle_conforme_v2)) ||
	(NULL == CU_add_test(pSuite, "test_tarmac_angle_conforme_v3", test_tarmac_angle_conforme_v3)) ||
	(NULL == CU_add_test(pSuite, "test_volet_ouvert_v1", test_volet_ouvert_v1)) ||
	(NULL == CU_add_test(pSuite, "test_volet_ouvert_v2", test_volet_ouvert_v2)) ||
	(NULL == CU_add_test(pSuite, "test_volet_ouvert_v3", test_volet_ouvert_v3)) ||
	(NULL == CU_add_test(pSuite, "test_stabilisateur_horizontal_conforme_v1", test_stabilisateur_horizontal_conforme_v1)) ||
	(NULL == CU_add_test(pSuite, "test_stabilisateur_horizontal_conforme_v2", test_stabilisateur_horizontal_conforme_v2)) ||
	(NULL == CU_add_test(pSuite, "test_stabilisateur_horizontal_conforme_v3", test_stabilisateur_horizontal_conforme_v3))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the basic interface
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   printf("\n");
   CU_basic_show_failures(CU_get_failure_list());
   printf("\n\n");
/* 
   // LES modes interactifs
   // Run all tests using the automated interface
   CU_automated_run_tests();
   CU_list_tests_to_file();

   // Run all tests using the console interface
   CU_console_run_tests();
*/
   /* Clean up registry and return */
   CU_cleanup_registry();
   return CU_get_error();
}
