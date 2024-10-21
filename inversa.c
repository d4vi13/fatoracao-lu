#include "common.h"
#include "utils.h"
#include "init.h"
#include "calc.h"
#include <fenv.h>


int main(){
    double tempo;
    LU ls;
   
    LIKWID_MARKER_INIT;

    init_LU(&ls);
    printf("/begin-output\n");
    printf("%d\n", ls.order);

    LIKWID_MARKER_START("likwid");
    tempo = timestamp();
    find_inverse(&ls);
    tempo = timestamp() - tempo;
    LIKWID_MARKER_STOP("likwid");

    LIKWID_MARKER_CLOSE;

    calculate_error(&ls);

    print_matrix(ls.solution, ls.order);
    printf("%.15e\n",ls.error);
    printf("%.8e\n", tempo);

    printf("/end-output\n");
    free_dependencies(&ls); 
    return 0;
}
