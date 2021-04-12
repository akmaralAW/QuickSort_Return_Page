#include "page.hpp"
#include <algorithm>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int partition2(vector<Resultat> &values, int left, int right) { //Lomuto
    Resultat pivotValue = values[left];
    Resultat temp;
    int s = left;
    for (int j = left+1; j <=right; j++){
        if(values[j] < pivotValue){
            s=s+1;
            temp = values[s];
            values[s] = values[j];
            values[j] = temp;
        }
    }

    temp = values[left];
    values[left] = values[s];
    values[s] = temp;
    return s;
}
void quicksort(vector<Resultat> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = partition2(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex+1, right);
    }
}

void retournePage(const std::vector<Resultat>& resultats_non_tries, unsigned int nombre_resultats_par_page, unsigned int numero_page, std::vector<Resultat>& page) {
    assert(!resultats_non_tries.empty());
    assert(page.empty());
    assert(nombre_resultats_par_page > 0);
    assert(numero_page < (resultats_non_tries.size() + nombre_resultats_par_page - 1) / nombre_resultats_par_page); //
    unsigned int nombre_resultats = resultats_non_tries.size();
    const unsigned int nombre_pages = ((nombre_resultats + nombre_resultats_par_page - 1) / nombre_resultats_par_page);
    assert(numero_page < nombre_pages);
    const unsigned int nombre_resultats_sur_la_page = (numero_page < nombre_pages - 1 || (nombre_resultats % nombre_resultats_par_page == 0))
                                                      ? nombre_resultats_par_page
                                                      : nombre_resultats % nombre_resultats_par_page;

    vector<Resultat> copy_result(resultats_non_tries), res;
    quicksort(copy_result, 0, copy_result.size() - 1);
    for (int k = numero_page*nombre_resultats_par_page; k < numero_page*nombre_resultats_par_page + nombre_resultats_sur_la_page; k++ ){
        page.push_back(copy_result[k]);
    }

}
