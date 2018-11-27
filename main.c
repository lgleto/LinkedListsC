#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char brand[20];
    char model[20];
    int year;
    float consumption;
    struct car *next;
} car;

car *head = NULL;

void listCars(){
    car *ptr =  head;
    printf ("Brand\t\tModel \t Year \tComsumption\n");
    while (ptr != NULL) {

        printf("%s \t%s \t%d \t%f\n",
               ptr->brand,
               ptr->model,
               ptr->year,
               ptr->consumption);
        ptr = ptr->next;
    }
}


void sortConsumption(){

    int nao_houve_mais_trocas = 1;


    while (nao_houve_mais_trocas == 1) {

        nao_houve_mais_trocas = 0;

        car *ptr = head;
        car *prev = NULL;

        while (ptr != NULL) {
            car *nextCar = ptr->next;
            if (nextCar == NULL) break;
            if (ptr->consumption > nextCar->consumption) {
                nao_houve_mais_trocas = 1;
                ptr->next = nextCar->next;
                if (prev != NULL)
                    prev->next = nextCar;
                else
                    head = nextCar;
                nextCar->next = ptr;
            }
            prev = ptr;


            ptr = ptr->next;
        }
    }
    listCars();
}

void sortYear(){

    int nao_houve_mais_trocas = 1;


    while (nao_houve_mais_trocas == 1) {

        nao_houve_mais_trocas = 0;

        car *ptr = head;
        car *prev = NULL;

        while (ptr != NULL) {
            car *nextCar = ptr->next;
            if (nextCar == NULL) break;
            if (ptr->year > nextCar->year) {
                nao_houve_mais_trocas = 1;
                ptr->next = nextCar->next;
                if (prev != NULL)
                    prev->next = nextCar;
                else
                    head = nextCar;
                nextCar->next = ptr;
            }
            prev = ptr;


            ptr = ptr->next;
        }
    }
    listCars();
}


void addCarFormUser (){
    car *newcar =malloc(sizeof(car));
    printf("Introduza a marca do carro:\n");
    scanf("%s", newcar->brand );
    printf("Introduza o modelo do carro:\n");
    scanf("%s", newcar->model );
    printf("Introduza o ano do carro:\n");
    scanf("%d", &newcar->year );
    printf("Introduza o comsumo do carro:\n");
    scanf("%f", &newcar->consumption );

    newcar->next = head;
    head = newcar;
}

void write(){
    FILE *fptr;
    fptr = fopen ("cars.b","wb");

    if(fptr == NULL){
        printf("Erro ao abrir ficheiro");
        return;
    }

    car *ptr = head;

    while (ptr != NULL){
        fwrite(ptr, sizeof(car),1,fptr);
        ptr = ptr->next;
    }
    fclose(fptr);

}

void read(){
    FILE *fptr;
    fptr = fopen ("cars.b","rb");

    if(fptr == NULL){
        printf("Erro ao abrir ficheiro");
        return;
    }

    while (1){
        car *newcar = malloc(sizeof(car));
        if (fread(newcar, sizeof(car),1,fptr)==0 ){
            fclose(fptr);
            return;
        }
        newcar->next = head;
        head = newcar;
    }

    fclose(fptr);

}



int main() {
    read();

    int opcao = -1;


    while (opcao != 0){
        printf ("Escolha uma opção\n");
        printf ("1 - Inserir carro\n");
        printf ("2 - Listar carros\n");
        printf ("3 - Carro com o maior consumo\n");
        printf ("4 - Ordernar Carros por consumo\n");
        printf ("5 - Ordernar Carros por ano\n");
        printf ("0 - Sair da aplicação\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                // inserir carro
                addCarFormUser();
                break;
            case 2:
                listCars();
                break;
            case 3:
                // imprimir carro com maior
                // fazer em casa
                break;

            case 4:
                // imprimir carro com maior
                // fazer em casa
                sortConsumption();
                break;
            case 5:
                // imprimir carro com maior
                // fazer em casa
                sortYear();
                break;
            case 0:
                write();
                exit(0);
                break;
            default:
                printf ("Opção inválida\n");
        }
    }
    return 0;
}