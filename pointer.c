#include <stdio.h>

int main()
{
    char nombre[]="Gustavo A. Chavarria"; //declaramos un array de caracteres
    char *puntero=nombre;//Asignamos al puntero el comienzo del array
    printf("%s \nIngrese otro nombre: ",puntero);//Escribimos en pantalla nombre...
    gets(puntero); //leemos otro nombre
    printf("%s",puntero); //escribimos el nuevo nombre..
    return 0;
}
