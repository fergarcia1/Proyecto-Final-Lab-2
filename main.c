#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "NodoLibro.h"
#include "NodoUsuario.h"
#include "Libro.h"
#include "Usuario.h"

///Carolina_6664@yahoo.com
///3c0NoqBrjZ


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
int compararCadenasIgnorandoMayusculas(const char *str1, const char *str2);

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

///MENU INICIAL CON SIGN IN & REGISTRATION
void menuLogin(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro,int idLibroActual)
{
    system("cls");
    int valor = 0, flag = 0; ///Valor es para el switch del menu, flag es para el log in
    char mail[20], pass[20]; /// Mail y contrase�a para verificar el log in
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
                            printf("\nContrase�a incorrecta, vuelva a intentar. Intentos: %i/3", flag);
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
            printf("\nEmail inv�lido. Debe contener un '@' y '.com'.\n");
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

///MENU LOGGED USER
nodoUsuario * menuUsuario(nodoUsuario * usuarioLoged, nodoLibro * listaLibro, nodoUsuario * listaUsuarios, int idUsuarioActual, int idLibroActual)
{
    system("cls");
    int valor = 0, idBorrar = 0;
    printf("------------------------------------------\n");
    printf("          |Bienvenido/a %s!|",usuarioLoged->usuario.username);
    printf("\n------------------------------------------\n");
    printf("|1| Modificar datos");
    printf("\n------------------------------------------\n");
    printf("|2| Menu libros");
    printf("\n------------------------------------------\n");
    printf("|3| Cerrar sesion");
    printf("\n------------------------------------------\n");
    if(usuarioLoged->usuario.esAdmin == 1) ///solo se muestran estas opciones si el usuario es un admin
    {
        printf("\n--------|Funciones Adm|--------\n");
        printf("\n------------------------------------------\n");
        printf("|4| Ver Usuarios registrados");
        printf("\n------------------------------------------\n");
        printf("|5| Dar de baja o de alta un usuario/libro");
        printf("\n------------------------------------------\n");
    }
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    if(esValidoValor(valor,5) == 0)///Verificamos que la opcion ingresada sea valida
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
    }
    switch(valor)
    {
    case 1: ///modificar datos
        usuarioLoged->usuario = modificarUsuario(usuarioLoged->usuario,listaLibro);///Modificamos datos del usuario y se actualiza el archivo al finalizar
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 2: /// consultar libros por autor
        menuLibros(listaLibro);///Ingresamos al menu de libros
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 3: /// cerrar sesion
        return usuarioLoged;
        break;

    /// FUNCIONES DE ADMIN
    case 4:/// lista de usuarios
        muestraListaUsuario(listaUsuarios); ///Ver data de usuarios
        printf("\n-----------------------\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;
    case 5: /// menu alta y baja usuarios y libros
        menuAltaYBaja(listaUsuarios,idUsuarioActual,listaLibro,idLibroActual);///Funcion para dar de baja y alta un usuario o libro
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual,idLibroActual);
        break;
    }
    return usuarioLoged;
}

///MENU DE LIBROS
void menuLibros(nodoLibro * listaLibro){
    system("cls");
    int valor = 0;
    printf("-----------------------------------\n");
    printf("|1| Consulta libros por autor");
    printf("\n-----------------------------------\n");
    printf("|2| Consulta libros por categoria");
    printf("\n-----------------------------------\n");
    printf("|3| Ver todos los libros disponibles");
    printf("\n-----------------------------------\n");
    printf("|4| Volver al menu de Usuario");
    printf("\n-----------------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    switch(valor){
    case 1:
        muestraLibroPorAutor(listaLibro);/// Se verifica que el autor se encuentre dentro del archivo y muestra libros
        system("pause");
        menuLibros(listaLibro);
        break;
    case 2:
        muestraLibroPorCategoria(listaLibro);///Se verifica que se encuentre la categoria y libros, luego se muestra
        system("pause");
        menuLibros(listaLibro);
        break;
    case 3:
        system("cls");
        muestraListaLibro(listaLibro); ///mostramos todos los libros (que esten dados de alta)
        printf("\n-----------------------\n");
        system("pause");
        menuLibros(listaLibro);
        break;
    case 4:
        return 0;
        break;
    }
}

///MENU DAR DE BAJA / ALTA USUARIO
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
    if(esValidoValor(valor,4) == 0) ///verifiacion de la seleccion
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

///PASAJE ENTRE LISTAS Y ARCHIVOS
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


///VERIFICACIONES MODULARIZADAS
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

int compararCadenasIgnorandoMayusculas(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower(*str1) != tolower(*str2)) {
            return 0; // No son iguales
        }
        str1++;
        str2++;
    }
    return *str1 == *str2; // Verifica si ambas cadenas terminan
}
