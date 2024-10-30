#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int nr = 3;
    FILE *in = fopen(argv[1], "rb");
    FILE *fout = fopen(argv[2], "w");
   
     if (in == NULL) {
        perror("Eroare la deschiderea fișierului");
        return 1;
    }

    // Citeste valorile de pe prima linie
    int numarFrunze, radacina;
    fscanf(in, "%d %d", &numarFrunze, &radacina);

    // Citeste liniile ulterioare
    char *valoriPorti[3000];
    //char *numePorti[400];
   // int indexNumePorti = 0;
    int indexVector = 0;

    char linie[200];
    while (fgets(linie, sizeof(linie), in) != NULL) {
        valoriPorti[indexVector] =malloc(strlen(linie) + 1);
        strcpy(valoriPorti[indexVector], linie);
        indexVector++;
    }


   
    int indexPortiOr = 0, indexPortiAnd = 0, indexPortiNot = 0;
    int numarContor = 2000;
    char *valoriParantezeSeparate[100000];
    int indexParantezeSeparate = 0;


    for(int j = 1; j < indexVector; j++) {
        printf("%s", valoriPorti[j]);

        //in cazul in care avem o poarta OR
        if(strstr(valoriPorti[j], "OR")) {
            indexPortiOr = 0; 
            int numerePortiOr[100000];
            char *token = strtok(valoriPorti[j], " ");
            while (token != NULL) {
                printf("Cuvant: %s\n", token);
                
                if(strcmp(token, "OR") != 0) {
                    int numar = atoi(token);
                    numerePortiOr[indexPortiOr] = numar;
                    indexPortiOr ++;
                }
                token = strtok(NULL, " ");
            }
            char str[100];
            strcpy(str, "");
            for(int i = 0; i < indexPortiOr - 1; i++) {
                sprintf(str + strlen(str), " %d", numerePortiOr[i]);
            }
            int numarNegativ = -numerePortiOr[indexPortiOr-1];
            int zero = 0;
            sprintf(str + strlen(str), " %d", numarNegativ);
            sprintf(str + strlen(str), " %d", zero);
            printf("Alexa:%s\n", str);
            memmove(str, str + 1, strlen(str));
            valoriParantezeSeparate[indexParantezeSeparate] =strdup(str);
            indexParantezeSeparate++;
            for(int i = 0; i < indexPortiOr - 1; i++) {
                printf("99");
                char var[100];
                memset(var, 0, sizeof(var));
                sprintf(var + strlen(var), " %d", -numerePortiOr[i]);
                sprintf(var + strlen(var), " %d", numerePortiOr[indexPortiOr-1]);
                sprintf(var + strlen(var), " %d", zero);
                 memmove(var, var + 1, strlen(str));
                valoriParantezeSeparate[indexParantezeSeparate] = strdup(var);
                printf(" maami%d", indexParantezeSeparate);
                indexParantezeSeparate++;
            }
        }
         //in cazul in care avem o poarta AND
        if(strstr(valoriPorti[j], "AND")) {
            char *token = strtok(valoriPorti[j], " ");
            int numerePortiAnd[100000];
            indexPortiAnd = 0;
            while (token != NULL) {
                printf("Cuvant: %s\n", token);
                
                if(strcmp(token, "AND") != 0) {
                    int numar = atoi(token);
                    numerePortiAnd[indexPortiAnd] = numar;
                    indexPortiAnd ++;
                }
                token = strtok(NULL, " ");
            }
            char str[100];
            strcpy(str, "");
            for(int i = 0; i < indexPortiAnd - 1; i++) {
                sprintf(str + strlen(str), " %d", -numerePortiAnd[i]);
            }
            int zero = 0;
            sprintf(str + strlen(str), " %d", numerePortiAnd[indexPortiAnd-1]);
            sprintf(str + strlen(str), " %d", zero);
            printf("Alexa:%s\n", str);
            memmove(str, str + 1, strlen(str));
            valoriParantezeSeparate[indexParantezeSeparate] =strdup(str);
            indexParantezeSeparate++;
            for(int i = 0; i < indexPortiAnd - 1; i++) {
                printf("100");
                char var[100];
                memset(var, 0, sizeof(var));
                sprintf(var + strlen(var), " %d", numerePortiAnd[i]);
                sprintf(var + strlen(var), " %d", -numerePortiAnd[indexPortiAnd-1]);
                sprintf(var + strlen(var), " %d", zero);
                valoriParantezeSeparate[indexParantezeSeparate] = strdup(var);
                indexParantezeSeparate++;
            }
        }
          //in cazul in care avem o poarta NOT
        if(strstr(valoriPorti[j], "NOT")) {
            int numerePortiNot[100000];
            indexPortiNot = 0;
            char *token = strtok(valoriPorti[j], " ");
            while (token != NULL) {
                printf("Cuvant: %s\n", token);
                
                if(strcmp(token, "NOT") != 0) {
                    int numar = atoi(token);
                    numerePortiNot[indexPortiNot] = numar;
                    indexPortiNot ++;
                }
                token = strtok(NULL, " ");
            }
            char str[100];
            strcpy(str, "");
            sprintf(str + strlen(str), " %d", numerePortiNot[indexPortiNot-1]);
            sprintf(str + strlen(str), " %d", numerePortiNot[0]);
            sprintf(str + strlen(str), " %d", 0);
            memmove(str, str + 1, strlen(str));
            valoriParantezeSeparate[indexParantezeSeparate] =strdup(str);
            indexParantezeSeparate++;
            memset(str, 0, sizeof(str));
            strcpy(str, "");
            sprintf(str + strlen(str), " %d", -numerePortiNot[indexPortiNot-1]);
            sprintf(str + strlen(str), " %d", -numerePortiNot[0]);
            sprintf(str + strlen(str), " %d", 0);
            memmove(str, str + 1, strlen(str));
            valoriParantezeSeparate[indexParantezeSeparate] =strdup(str);
            indexParantezeSeparate++;

        }
        printf("%s\n", valoriPorti[j]);
    }
    fprintf(fout, "%s", "p cnf ");
    fprintf(fout, "%d", radacina);
    fprintf(fout, " %d\n", indexParantezeSeparate+1);
    printf("%d\n", indexParantezeSeparate-1);
    for(int i = 0; i < indexParantezeSeparate; i ++) {
        printf("%s\n", valoriParantezeSeparate[i]);
        fprintf(fout, "%s\n", valoriParantezeSeparate[i]);
    }
        fprintf(fout, "%d %d\n", radacina,0);

    // fprintf(fout, "p cnf 3 2\n");
    // fprintf(fout, "1 2 -3 0\n");
    // fprintf(fout, "1 2 0");

    

    // Închide fișierul
    fclose(in);

    
    
    
    return 0; 
}