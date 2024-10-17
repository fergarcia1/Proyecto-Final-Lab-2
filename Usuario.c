#include "Usuario.h"
#include "NodoLibro.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

stUsuario cargarUsuario(int idUsuarioActual, char mail[])
{
    stUsuario aux;
    int flag = 0;
    aux.idUsuario = idUsuarioActual + 1;
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
    if(a.eliminado == 0)
    {
        printf("\n-----------------------\n");
        printf("Usuario: %s\n",a.username);
        printf("Email: %s\n",a.email);
        printf("Contrasenia: %s\n",a.password);
        printf("Id: %i\n",a.idUsuario);
        printf("Es admin: %i\n",a.esAdmin);
        printf("\n-----------------------\n");
    }
}

stUsuario modificarUsuario(stUsuario usuario, nodoLibro * listaLibro)
{
    system("cls");
    stUsuario auxUser = usuario;
    int valor = 0, idAux = 0;
    printf("------------------------------\n");
    printf("1| Modificar nombre de usuario.");
    printf("\n------------------------------\n");
    printf("2| Modificar contrasenia.");
    printf("\n------------------------------\n");
    printf("3| Modificar email.");
    printf("\n------------------------------\n");
    printf("4| Modificar libros favoritos.");
    printf("\n------------------------------\n");
    printf("5| Modificar dni.");
    printf("\n------------------------------\n");
    printf("6| Volver al menu.");
    printf("\n------------------------------\n");

    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);

    switch(valor)
    {
    case 1:
        printf("\nNuevo nombre de usuario: ");
        fflush(stdin);
        gets(auxUser.username);
        printf("\nNombre de usuario cambiado correctamente.\n");
        system("pause");
        return auxUser;
        break;
    case 2:
        printf("\nNueva contrasenia: ");
        fflush(stdin);
        gets(auxUser.password);
        if(!esValidoPass(auxUser.password))
        {
            printf("La contraseña debe contener al menos 1 mayuscula y 1 minuscula.\n");
            system("pause");
            modificarUsuario(usuario,listaLibro);
        }
        else
        {
            printf("\nContraseña cambiada correctamente.\n");
            system("pause");
            return auxUser;
        }
        break;
    case 3:
        printf("\nNuevo email: ");
        fflush(stdin);
        gets(auxUser.email);
        if (!esValidoEmail(auxUser.email))
        {
            printf("\nEmail inválido. Debe contener un '@' y '.com'.\n");
            system("pause");
            modificarUsuario(usuario,listaLibro);
        }
        else
        {
            printf("Email cambiado correctamente.\n");
            system("pause");
            return auxUser;
        }
        break;
    case 4:
        printf("\nEstos son tus libros favoritos ");
        librosFavoritosUsuario(auxUser,listaLibro);
        printf("\nIntroduzca la id de los libros a agregar/quitar: ");
        printf("\n>");
        fflush(stdin);
        scanf("%i", &idAux);
        auxUser = modificarLibrosFavoritos(auxUser,idAux,listaLibro);
        return auxUser;
        break;
    case 5:
        printf("\nNuevo dni: ");
        fflush(stdin);
        gets(auxUser.dni);
        printf("\Dni cambiado correctamente.\n");
        system("pause");
        return auxUser;
        break;
    case 6:
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
        //printf("  Libro ID: %d\n", usuario.librosFavoritos[i]);
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
