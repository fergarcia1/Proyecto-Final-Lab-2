#include "Usuario.h"
#include "NodoLibro.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

stUsuario cargarUsuario(int *idUsuarioActual, char mail[])
{
    stUsuario aux;
    int flag = 0;
    aux.idUsuario = (*idUsuarioActual) + 1;
    (*idUsuarioActual)++;
    aux.esAdmin = 0;
    while(flag == 0)
    {
        printf("\n--------------------------");
        printf("\nIngrese su contrasenia ");
        printf("\n--------------------------\n");
        printf("\n>");
        fflush(stdin);
        gets(aux.password);

        if(!esValidoPass(aux.password))
        {
            printf("La contraseña debe contener al menos 1 mayuscula y 1 minuscula.\n");
            system("pause");
            system("cls");
        }
        else
        {
            flag = 1;
        }
    }
    strcpy(aux.email,mail);
    printf("\n--------------------------");
    printf("\nIngrese un nombre de Usuario ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.username);

    printf("\n--------------------------");
    printf("\nIngrese un genero ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%c", &aux.genero);

    printf("\n--------------------------");
    printf("\nIngrese un fecha de nacimiento ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.fechaNacimiento);

    printf("\n--------------------------");
    printf("\nIngrese un DNI ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.dni);

    printf("\n--------------------------");
    printf("\nIngrese su pais ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.domicilio.pais);

    printf("\n--------------------------");
    printf("\nIngrese su localidad ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.domicilio.localidad);

    printf("\n--------------------------");
    printf("\nIngrese su ciudad ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.domicilio.ciudad);

    printf("\n--------------------------");
    printf("\nIngrese su calle ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    gets(aux.domicilio.calle);

    printf("\n--------------------------");
    printf("\nIngrese la altura ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%d", &aux.domicilio.altura);

    printf("\n--------------------------");
    printf("\nIngrese su codigo postal ");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%d", &aux.domicilio.cp);

    return aux;
}

void muestraUnUsuario(stUsuario a)
{
        printf("-----------------------\n");
        printf("Usuario: %s\n",a.username);
        printf("Email: %s\n",a.email);
        printf("Contrasenia: %s\n",a.password);
        printf("Id: %i\n",a.idUsuario);
        printf("Es admin: %i\n",a.esAdmin);
        printf("-----------------------\n");

}


stUsuario modificarUsuario(stUsuario usuario, nodoLibro * listaLibro)
{
    system("cls");
    stUsuario auxUser = usuario;
    int valor = 0, idAux = 0;
    char aux[20];
    printf("------------------------------\n");
    printf("1| Modificar nombre de usuario");
    printf("\n------------------------------\n");
    printf("2| Modificar contrasenia");
    printf("\n------------------------------\n");
    printf("3| Modificar email");
    printf("\n------------------------------\n");
    printf("4| Modificar libros favoritos");
    printf("\n------------------------------\n");
    printf("5| Volver al menu");
    printf("\n------------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    system("cls");
    if(esValidoValor(valor,5) == 0)
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        modificarUsuario(usuario,listaLibro);
    }

    switch(valor)
    {
    case 1: /// cambio username

        printf("\nSu usuario actual: %s ", auxUser.username);
        printf("(Introduzca su nuevo usuario o escriba 'atras' para volver atras!)\n");
        printf("\n> ");
        fflush(stdin);
        gets(aux);
        if(verificacionAtras(aux) == 1){ ///verifico si el usuario desea volver atras para no generar el cambio
            return auxUser; ///regreso al usuario sin cambios
        }
        else
        {
            strcpy(auxUser.username, aux);
            printf("\nNombre de usuario cambiado correctamente.\n");
            system("pause");
            return auxUser;
        }
        break;
    case 2: /// cambio pass
        printf("\nSu contrasenia actual: %s ", auxUser.password);
        printf("(Introduzca su nueva contraseña o 'atras' para volver atras!)\n");
        printf("\n> ");
        fflush(stdin);
        gets(aux);
        if(verificacionAtras(aux) == 1)
        {
            return auxUser; ///regreso al usuario sin cambios
        }
        else
        {
            if(!esValidoPass(auxUser.password))
            {
                printf("\nLa contraseña debe contener al menos 1 mayuscula y 1 minuscula.\n");
                system("pause");
                modificarUsuario(usuario,listaLibro);
            }
            else
            {
                strcpy(auxUser.password, aux);
                printf("\nContrasenia cambiada correctamente.\n");
                system("pause");
                return auxUser;
            }
        }
        break;
    case 3:  ///cambio email
        printf("\nSu email actual: %s ", auxUser.email);
        printf("(Introduzca su nuevo email o 'atras' para volver atras!)\n");
        printf("\n> ");
        fflush(stdin);
        gets(aux);
        if(verificacionAtras(aux) == 1)
        {
            return auxUser; ///regreso al usuario sin cambios
        }
        else
        {
            if (!esValidoEmail(aux))
            {
                printf("\nEmail invalido. Debe contener un '@' y '.com'.\n");
                system("pause");
                modificarUsuario(usuario,listaLibro);
            }
            else
            {
                strcpy(auxUser.email, aux);
                printf("Email cambiado correctamente.\n");
                system("pause");
                return auxUser;
            }
        }
        break;
    case 4: ///cambio libros
        printf("\nEstos son tus libros favoritos ");
        librosFavoritosUsuario(auxUser,listaLibro);
        printf("\nIntroduzca la Id de los libros a agregar/quitar, si la id se encuentra en su lista, sera eliminada, si no se agregara el libro (-1 para volver atras!)\n");
        printf("\n>");
        fflush(stdin);
        scanf("%i", &idAux);
        if(idAux == -1)
        {
            return auxUser;
        }
        auxUser = modificarLibrosFavoritos(auxUser,idAux,listaLibro);
        return auxUser;
        break;
    case 5:
        return auxUser;
        break;
    }
    return auxUser;
}

void librosFavoritosUsuario(stUsuario usuario, nodoLibro * listaLibro)
{
    printf("(%d):\n", usuario.validosLibrosFavs);
    for (int i = 0; i < usuario.validosLibrosFavs; i++)
    {
        muestraUnLibroPorId(listaLibro,usuario.librosFavoritos[i]);
    }
}

stUsuario modificarLibrosFavoritos(stUsuario usuario,int idBorrar,nodoLibro * listaLibro)
{
    int flag = 0;
    for (int i = 0; i < usuario.validosLibrosFavs; i++) /// quitar
    {
        if(usuario.librosFavoritos[i] == idBorrar)
        {
            flag = 1;
            for (int j = i; j < usuario.validosLibrosFavs - 1; j++)   ///mover a la izq los datos del arreglo para no dejar huecos
            {
                usuario.librosFavoritos[j] = usuario.librosFavoritos[j + 1];
            }
            printf("\nLibro eliminado con exito.\n");
            system("pause");
            usuario.validosLibrosFavs--;
            return usuario;
        }
    }
    if (flag == 0) /// agregar
    {
        if (usuario.validosLibrosFavs < 50)
        {
            usuario.librosFavoritos[usuario.validosLibrosFavs] = idBorrar;
            usuario.validosLibrosFavs++;
            printf("\nLibro agregado con exito.\n");
            system("pause");
        }
        else
        {
            printf("No se pueden agregar más libros favoritos.\n");
        }
        return usuario;
    }
}
