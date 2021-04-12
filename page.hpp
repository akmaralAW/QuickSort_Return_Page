#ifndef PAGE
#define PAGE

#include <vector>

#include "resultat.hpp"


// Returns the results of a page
// Entries:
// results_non_sorted: all search results not sorted
// number_resultats_per_page: the number of results per page (except possibly on the last page)
// page_number: the number of the page. The first page is page number 0.
// Exit:
// page: the search results found on the requested page
void retournePage(const std::vector<Resultat>& resultats_non_tries, unsigned int nombre_resultats_par_page, unsigned int numero_page, std::vector<Resultat>& page);
#endif
