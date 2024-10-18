#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "NodoLibro.h"
#include "NodoUsuario.h"
#include "Libro.h"
#include "Usuario.h"

///Zara4@gmail.com
///sKtzqppz


///pasaje de archivo a nuestras listas
nodoUsuario * archivoToListaUsuario(char nombre[], nodoUsuario * listaUsuario);
nodoLibro * archivoToListaLibro(char nombre[], nodoLibro * listaLibro);

///pasaje de las listas a los archivos
void listaToArchivoUsuarios(char nombre[], nodoUsuario * listaUsuario);
void listaToArchivoLibros(char nombre[], nodoLibro * listaLibro);

///funciones de verificacion
int esValidoEmail(char *email);
int esValidoPass(char *password);
int verificacionAtras(char *atras);
int esValidoValor(int valor, int maximo);

///menus
nodoUsuario * menuUsuario(nodoUsuario * user, nodoLibro * listaLibro, nodoUsuario * listaUsuarios, int idUsuarioActual,int idLibroActual);
void menuLogin(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro, int idLibroActual);
void menuAltaYBaja(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro, int idLibroActual);

int main()
{

    nodoUsuario * listaUsuarios = inicLista();
    nodoLibro * listaLibro = inicLista();
    ///PASAJE DEL ARCHIVO A LA LISTA
    listaUsuarios = archivoToListaUsuario("usuarios.dat",listaUsuarios);
    listaLibro = archivoToListaLibro("libros.dat",listaLibro);

    nodoUsuario * auxUsuario = buscarUltimoUsuario(listaUsuarios);
    nodoLibro * auxLibro = buscarUltimoLibro(listaLibro);
    int idUsuarioActual = auxUsuario->usuario.idUsuario, idLibroActual = auxLibro->libro.idLibro;
    menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual); ///paso la lista de usuarios al menu y el numero de ID actual de usuario y libro, y la lista de libros

    ///PASAJE DE LISTA AL ARCHIVO
    listaToArchivoLibros("libros.dat",listaLibro);
    listaToArchivoUsuarios("usuarios.dat",listaUsuarios);
    return 0;
}

void menuLogin(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro,int idLibroActual)
{
    system("cls");
    int valor = 0, flag = 0; ///Valor es para el switch del menu, flag es para el log in
    char mail[20], pass[20]; /// Mail y contraseña para verificar el log in
    nodoUsuario * userAux = inicLista();
    printf("--------------------------\n");
    printf("|1| Ingrese con su cuenta");
    printf("\n--------------------------\n");
    printf("|2| Cree una cuenta nueva");
    printf("\n--------------------------\n");
    printf("|3| Salir del programa");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    system("cls");
    if(esValidoValor(valor,3) == 0)
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
    }

    switch(valor)   ///Menu de logeo y creacion de cuenta
    {
    case 1: /// Log con cuenta ya registrada
        printf("-----------------------\n");
        printf("Ingrese su email ");
        printf("\n-----------------------\n");
        printf("\n>");
        fflush(stdin);
        gets(mail);
        if (!esValidoEmail(mail)) ///comprobacion de mail
        {
            printf("\nEmail invalido. Debe contener un '@' y '.com'.\n");
            system("pause");
            menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
        }
        else
        {
            userAux = buscarMailUsuario(listaUsuarios, &mail);
            if(userAux->usuario.eliminado == 0) /// verifico que no este eliminado
            {
                if(userAux)  ///Si lo encontro en la funcion buscarMailUsuario no deberia ser null, asi que pido la pass
                {
                    while(flag < 3)
                    {
                        printf("\n-----------------------\n");
                        printf("Ingrese su contrasenia ");
                        printf("\n-----------------------\n");
                        printf("\n>");
                        fflush(stdin);
                        gets(pass);
                        if(strcmp(userAux->usuario.password, pass) == 0)
                        {
                            ///Ya comprobado el mail, si introduce bien la pass, al menu de usuarios(en proceso)
                            userAux = menuUsuario(userAux,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
                            flag = 4;
                        }
                        else
                        {
                            flag = flag+1;
                            printf("\nContraseña incorrecta, vuelva a intentar. Intentos: %i/3", flag);
                            printf("\n");
                        }
                    }
                }
                else
                {
                    printf("\nEmail incorrecto, intente una vez mas o cree una cuenta nueva.\n");
                    menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual); ///en caso de que no sea valido el mail, lo mando devuelta al principio
                }
            }
            else
            {
                printf("\nEl usuario  se encuentra dado de baja, comuniquese con el soporte.\n");
                system("pause");
            }

        }
        break;
    case 2: /// Crear cuenta
        printf("-----------------------\n");
        printf("Ingrese su email ");
        printf("\n-----------------------\n");
        printf("\n>");
        fflush(stdin);
        gets(mail);
        if (!esValidoEmail(mail))
        {
            printf("\nEmail inválido. Debe contener un '@' y '.com'.\n");
            system("pause");
            menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
        }
        else
        {
            userAux = buscarMailUsuario(listaUsuarios, mail); ///busco que el mail no se encuentre registrado previamente, funcion retorna el nodo si coincide y NULL si no encuentra el mail

            if(!userAux)  ///si la funcion anterior retorno null, significa que el mail no esta utilizado, y se prosigue con la creacion de usuario
            {
                stUsuario usuarioAux = cargarUsuario(idUsuarioActual,mail); ///carga manual de usuario

                nodoUsuario * nuevoNodoUsuario = crearNodoUsuario(usuarioAux); ///creacion de nodo con usuario anterior

                listaUsuarios = agregarAlFinalUsuario(listaUsuarios, nuevoNodoUsuario); ///agrego al final de la lista el nodoNuevo

                userAux = menuUsuario(nuevoNodoUsuario,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual); /// se rompe aca hay que ver porque
            }
            else
            {
                printf("\nEl mail ya se encuentra registrado, intente nuevamente.\n");
                system("pause");
                menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
            }
        }
        break;
    case 3:
        return 0;
        break;
    }
    menuLogin(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
}

nodoUsuario * menuUsuario(nodoUsuario * usuarioLoged, nodoLibro * listaLibro, nodoUsuario * listaUsuarios, int idUsuarioActual, int idLibroActual)
{
    system("cls");
    int valor = 0, idBorrar = 0;
    printf("------------------------------------------\n");
    printf("             Bienvenido %s!",usuarioLoged->usuario.username);
    printf("\n------------------------------------------\n");
    printf("|1| Modificar datos");
    printf("\n------------------------------------------\n");
    printf("|2| Consulta libros por autor");
    printf("\n------------------------------------------\n");
    printf("|3| Consulta libros por categoria");
    printf("\n------------------------------------------\n");
    printf("|4| Ver Libros disponibles");
    printf("\n------------------------------------------\n");
    printf("|5| Cerrar sesion");
    printf("\n------------------------------------------\n");
    if(usuarioLoged->usuario.esAdmin == 1) ///solo se muestran estas opciones si el usuario es un admin
    {
        printf("|6| Ver Usuarios registrados");
        printf("\n------------------------------------------\n");
        printf("|7| Dar de baja o de alta un usuario/libro");
        printf("\n------------------------------------------\n");
    }
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    if(esValidoValor(valor,7) == 0)
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
    }

    switch(valor)
    {
    case 1: ///modificar datos
        usuarioLoged->usuario = modificarUsuario(usuarioLoged->usuario,listaLibro);
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 2: /// consultar libros por autor

        muestraLibroPorAutor(listaLibro);
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 3: /// consultar libros por categoria

        muestraLibroPorCategoria(listaLibro);
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 4: /// cerrar sesion
        system("cls");
        muestraListaLibro(listaLibro);
        printf("\n-----------------------\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        return usuarioLoged;
        break;

    /// FUNCIONES DE ADMIN
    case 5: /// lista de usuarios
        return usuarioLoged;
        break;

    case 6:
        muestraListaUsuario(listaUsuarios);
        printf("\n-----------------------\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;
    case 7:
        menuAltaYBaja(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;
    }
    return usuarioLoged;
}

void menuAltaYBaja(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro, int idLibroActual)
{
    int valor = 0;
    system("cls");
    printf("--------------------------\n");
    printf("|1| Dar de baja un usuario");
    printf("\n--------------------------\n");
    printf("|2| Dar de alta un usuario");
    printf("\n--------------------------\n");
    printf("|3| Dar de baja un libro");
    printf("\n--------------------------\n");
    printf("|4| Dar de alta un libro");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    if(esValidoValor(valor,4) == 0)
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuAltaYBaja(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);
    }
    switch(valor)
    {
    case 1:
        listaUsuarios = darDeBajaUsuario(listaUsuarios,idUsuarioActual);
        break;

    case 2:
        listaUsuarios = darDeAltaUsuario(listaUsuarios,idUsuarioActual);
        break;
    case 3:
        listaLibro = darDeBajaLibro(listaLibro,idLibroActual);
        break;
    case 4:
        listaLibro = darDeAltaLibro(listaLibro,idLibroActual);
        break;
    }
}

nodoUsuario * archivoToListaUsuario(char nombre[], nodoUsuario * listaUsuario)
{
    FILE * f = fopen(nombre, "rb");
    stUsuario aux;
    nodoUsuario * nuevo;
    if(f)
    {
        while(fread(&aux,sizeof(stUsuario),1,f) > 0)
        {
            nuevo = crearNodoUsuario(aux);
            listaUsuario = agregarAlFinalUsuario(listaUsuario,nuevo);
        }
    }
    fclose(f);
    return listaUsuario;
}

nodoLibro * archivoToListaLibro(char nombre[], nodoLibro * listaLibro)
{
    FILE * fl = fopen(nombre, "rb");
    stLibro aux;
    nodoLibro * nuevo;
    if(fl)
    {
        while(fread(&aux,sizeof(stLibro),1,fl) > 0)
        {
            nuevo = crearNodoLibro(aux);
            listaLibro = agregarAlFinalLibro(listaLibro,nuevo);
        }
    }
    fclose(fl);
    return listaLibro;
}

void listaToArchivoUsuarios(char nombre[], nodoUsuario * listaUsuario)  /// no se si funciona
{
    FILE * f = fopen(nombre, "wb");
    nodoUsuario * seg = listaUsuario;
    if(f)
    {
        while(fwrite(&seg->usuario,sizeof(stUsuario),1,f) > 0)
        {
            seg = seg->sig;
        }
    }
    fclose(f);
}

void listaToArchivoLibros(char nombre[], nodoLibro * listaLibro)  /// no se si funciona
{
    FILE * f = fopen(nombre, "wb");
    nodoLibro * seg = listaLibro;
    if(f)
    {
        while(fwrite(&seg->libro,sizeof(stLibro),1,f) > 0)
        {
            seg = seg->sig;
        }
    }
    fclose(f);
}

int esValidoValor(int valor, int maximo)
{
    if(valor <= 0 || valor > maximo)
    {
        return 0;
    }
    return 1;
}

int esValidoEmail(char *email)
{
    /// verifica que tenga una @ y un .com
    const char *at = strchr(email, '@');
    if (at == NULL || strstr(at, ".com") == NULL)
    {
        return 0; /// 0 si es no valido
    }
    return 1; /// 1 si es valido
}

int esValidoPass(char *password)
{
    int hasUpper = 0, hasLower = 0;

    for (int i = 0; password[i] != '\0'; i++)
    {
        if (isupper(password[i]))
        {
            hasUpper = 1;
        }
        if (islower(password[i]))
        {
            hasLower = 1;
        }
    }
    return hasUpper && hasLower;
}
int verificacionAtras(char *atras)
{
    if(strcmp(atras, "atras") == 0)
    {
        return 1;
    }
    return 0;
}
