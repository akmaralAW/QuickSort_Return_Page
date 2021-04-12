#include <algorithm>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "resultat.hpp"
#include "page.hpp"

unsigned int temoin_mise_a_zero_des_compteurs = 0;

bool testSimple(unsigned int nombre_resultats,
		unsigned int nombre_resultats_par_page,
		unsigned int numero_page) {
  assert(nombre_resultats > 0);
  assert(nombre_resultats_par_page > 0);
  const unsigned int nombre_pages = ((nombre_resultats + nombre_resultats_par_page - 1) / nombre_resultats_par_page);
  assert(numero_page < nombre_pages);

  // Generates random results
  std::vector<Resultat> resultats;
  resultats.reserve(nombre_resultats);
  for (unsigned int i = 0; i < nombre_resultats; i++){
      resultats.push_back(Resultat());
  }

  std::vector<Resultat> page; // Empty page (it's up to you to fill it)
  assert(Resultat::miseAZeroDesCompteurs() == ++temoin_mise_a_zero_des_compteurs); // Check that only the tests.cpp file resets the counters to zero
  retournePage(resultats, nombre_resultats_par_page, numero_page, page); // Call to your function
  const unsigned int nombre_comparaisons = Resultat::compteurComparaison();
  const unsigned int nombre_copies = Resultat::compteurCopie();
  std::sort(resultats.begin(), resultats.end());
//  std::cout << "Sorted original" << std::endl;
//  for (int p = 0; p < resultats.size(); p++){
//        resultats[p].print();
//  }
  const unsigned int nombre_resultats_sur_la_page = (numero_page < nombre_pages - 1 || (nombre_resultats % nombre_resultats_par_page == 0))
    ? nombre_resultats_par_page
    : nombre_resultats % nombre_resultats_par_page;

  const bool test = (page.size() == nombre_resultats_sur_la_page)
        && std::equal(resultats.begin() + numero_page * nombre_resultats_par_page,
		      resultats.begin() + numero_page * nombre_resultats_par_page + nombre_resultats_sur_la_page,
		      page.begin());
  std::cout << "testSimple(" << nombre_resultats << ", " << nombre_resultats_par_page << ", " << numero_page << ")" << std::endl;
  std::cout << "  Nombre de comparaisons: " << nombre_comparaisons << std::endl;
  std::cout << "  Nombre de copies: " << nombre_copies << std::endl;
  if (test) {
    std::cout << "+1 point: testSimple a passe" << std::endl;
  } else {
    std::cout << "Nombre de resultats sur la page: " << page.size() << std::endl;
    std::cout << "Nombre de resultats attendus sur la page: " << nombre_resultats_sur_la_page << std::endl;
    std::cout << "+0 point: testSimple a echoue" << std::endl;
  }
  return test;
}

bool testEfficacite(unsigned int nombre_resultats,
		    unsigned int nombre_resultats_par_page,
		    unsigned int numero_page) {
  assert(nombre_resultats > 0);
  assert(nombre_resultats_par_page > 0);
  const unsigned int nombre_pages = ((nombre_resultats + nombre_resultats_par_page - 1) / nombre_resultats_par_page);
  assert(numero_page < nombre_pages);

  std::vector<Resultat> resultats; //
  resultats.reserve(nombre_resultats); // Generates random results
  for (unsigned int i = 0; i < nombre_resultats; i++)
    resultats.push_back(Resultat());

  std::vector<Resultat> page;			     // Empty page (it's your function to fill it)
  // Check that only the tests.cpp file resets the counters to zero
  if (Resultat::miseAZeroDesCompteurs() != ++temoin_mise_a_zero_des_compteurs) {
    std::cout << "+0 point: Le code a joue avec les compteurs de comparaison. C'est mal!" << std::endl;
    return false;
  }
  retournePage(resultats, nombre_resultats_par_page, numero_page, page); // Call to your function
  const unsigned int nombre_comparaisons_retourne_page = Resultat::compteurComparaison();
  const unsigned int nombre_copies_retourne_page = Resultat::compteurCopie();

  // Check that only the tests.cpp file resets the counters to zero
  if (Resultat::miseAZeroDesCompteurs() != ++temoin_mise_a_zero_des_compteurs) {
    std::cout << "+0 point: Le code a joue avec les compteurs de comparaison. C'est mal!" << std::endl;
    return false;
  }
  std::vector<Resultat> copie(resultats);
  std::sort(copie.begin(), copie.end());
  const unsigned int nombre_comparaisons_tri = Resultat::compteurComparaison(); // comparison counter sorted
  const unsigned int nombre_copies_tri = Resultat::compteurCopie(); // copying counter
  const unsigned int nombre_resultats_sur_la_page = (numero_page < nombre_pages - 1 || (nombre_resultats % nombre_resultats_par_page == 0))
    ? nombre_resultats_par_page
    : nombre_resultats % nombre_resultats_par_page;
  const bool test = (page.size() == nombre_resultats_sur_la_page)
    && std::equal(copie.begin() + numero_page * nombre_resultats_par_page,
		  copie.begin() + numero_page * nombre_resultats_par_page + nombre_resultats_sur_la_page,
		  page.begin())
    && (nombre_comparaisons_retourne_page < nombre_comparaisons_tri);

  std::cout << "testEfficacite(" << nombre_resultats << ", " << nombre_resultats_par_page << ", " << numero_page << ")" << std::endl;
  std::cout << "  Nombre de comparaisons" << std::endl;
  std::cout << "    retourne_page: " << nombre_comparaisons_retourne_page << std::endl;
  std::cout << "    tri: " << nombre_comparaisons_tri << std::endl;
  if (nombre_comparaisons_retourne_page > 0) {
    std::cout << "    ratio: " << (float)nombre_comparaisons_tri / nombre_comparaisons_retourne_page << std::endl;
  }
  if (test) {
    std::cout << "+1 point: testEfficacite a passe" << std::endl;
  } else {
    std::cout << "Nombre de resultats sur la page: " << page.size() << std::endl;
    std::cout << "Nombre de resultats attendus sur la page: " << nombre_resultats_sur_la_page << std::endl;
    std::cout << "+0 point: testEfficacite a echoue" << std::endl;
  }
  return test;

}

int main(void) {
  srand(time(NULL));		// Initialise le germe du generateur de nombres pseudo-aleatoires
   testSimple(10, 3, 0);
  testSimple(20, 5, 0);		// First page
  testSimple(21, 5, 4);		// Last page with only one result
  testSimple(25, 5, 4);		// Complete last page
  testSimple(20, 5, 1);		// Page which is neither the first nor the lastPage which is neither the first nor the last
  testEfficacite(1000000, 10, 50); // If this test is too slow, comment on it during the development of your function

  return 0;
}
