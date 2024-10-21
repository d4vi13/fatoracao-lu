#include "common.h"
#include "utils.h"
#include "init.h"
#include "calc.h"
#include <fenv.h>


int main(){
    double tempo;
    LU ls;
   
    likwid_markerInit();

    init_LU(&ls);

    printf("%d\n", ls.order);


    likwid_markerStartRegion("Calculo da inversa");
    tempo = timestamp();
    find_inverse(&ls);
    tempo = timestamp() - tempo;
    likwid_markerStopRegion("Calculo da inversa");

    calculate_error(&ls);

    print_matrix(ls.solution, ls.order);
    printf("%.15e\n",ls.error);
    printf("%.8e\n", tempo);

    free_dependencies(&ls); 
    return 0;
}
