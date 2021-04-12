#include "resultat.hpp"

#include <algorithm>
#include <iostream>
#include <stdlib.h>

// Initialisation des membres statiques
unsigned int Resultat::compteur_copie = 0;
unsigned int Resultat::compteur_comparaison = 0;
unsigned int Resultat::compteur_mise_a_zero = 0;

// Default constructor (generates a random url)
Resultat::Resultat() {
  const unsigned int longueur = 5 + rand() % 40; //  [5, 45) Generate an integer in
  const std::string prefix = "http://";
  const std::string suffix = ".com";
  
  m_url.resize(longueur + prefix.size() + suffix.size());
  for (unsigned int i = 0; i < longueur; i++){
      m_url[prefix.size() + i] = 'a' + rand() % 26;
  }

  std::copy(prefix.begin(), prefix.end(), m_url.begin()); // copy prefix
  std::copy(suffix.begin(), suffix.end(), m_url.begin() + prefix.size() + longueur); // copy suffix
  // std::cout << m_url << std::endl; // creates nombre_results links
}

// Constructor where the url is specified
Resultat::Resultat(const std::string& url)
  : m_url(url)
{
}

// Constructeur de copie
Resultat::Resultat(const Resultat& un_resultat)
  : m_url(un_resultat.m_url)
{
  compteur_copie++;
}

void Resultat::print() const {
  std::cout << m_url << std::endl;
}

unsigned int Resultat::miseAZeroDesCompteurs() {
  compteur_copie = 0;
  compteur_comparaison = 0;
  return ++compteur_mise_a_zero;
}

unsigned int Resultat::compteurComparaison() {
  return compteur_comparaison;
}

unsigned int Resultat::compteurCopie() {
  return compteur_copie;
}

bool Resultat::operator<(const Resultat& un_resultat) const {
  // Normally, it is the relevance of the URL rather than its alphabetical order that would be tested.
  compteur_comparaison++;
  return m_url < un_resultat.m_url; 
}

bool Resultat::operator<=(const Resultat& un_resultat) const {
  // Normally, it is the relevance of the URL rather than its alphabetical order that would be tested.
  compteur_comparaison++;
  return m_url <= un_resultat.m_url; 
}

bool Resultat::operator==(const Resultat& un_resultat) const {
  // Normally, it is the relevance of the URL rather than its alphabetical order that would be tested.
  compteur_comparaison++;
  return m_url == un_resultat.m_url;
}
