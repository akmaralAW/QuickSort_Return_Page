#ifndef RESULTAT
#define RESULTAT

#include <string>

class Resultat {
private:
  static unsigned int compteur_copie; // counter
  static unsigned int compteur_comparaison;
  static unsigned int compteur_mise_a_zero; // counter reset
  
  std::string m_url;

public:
  Resultat();	 // Default constructor (generate a random url)
  Resultat(const std::string& url); // Constructor where the url is specified
  Resultat(const Resultat& un_resultat); // Copy builder

  void print() const;		// to debug

  static unsigned int miseAZeroDesCompteurs();
  static unsigned int compteurComparaison();
  static unsigned int compteurCopie();
  
  bool operator<(const Resultat& un_resultat) const;
  bool operator<=(const Resultat& un_resultat) const;
  bool operator==(const Resultat& un_resultat) const;
};

#endif
