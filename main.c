#include <stdio.h>
#include <stdlib.h>

#include "include/internal_sort.h"
#include "include/partitions_util.h"

#define MAX_SIZE_PARTITION 100
#define size(a) sizeof(a)/sizeof(a[0])

int main()
{
    int numbersAmt = 35;
    int numbersPerFile = 5;
    int partitionsAmount = (numbersAmt/numbersPerFile) + ((numbersAmt % numbersPerFile != 0) ? 1 : 0);

    //gera arquivo com numbersAmt numeros aleatorios
    generate_file("file", numbersAmt);

    //gera partições com numbersPerFile numeros
    generate_partitions("file", numbersPerFile);

    //ordena todos os arquivos
    for (int i = 0; i < partitionsAmount; i++) {
        char* name = generate_file_name("file", i);
        sort_file(name, numbersPerFile);
        free(name);
    }

    //da merge nos arquivos
    merge_sorted_partitions("file", 0, partitionsAmount);
    return 0;
}
