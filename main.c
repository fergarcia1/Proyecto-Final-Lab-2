#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

///Carolina_6664@yahoo.com
///3c0NoqBrjZ
///Juan_0434@hotmail.com
///C5OLcY94Y
#include "NodoLibro.h"
#include "NodoUsuario.h"
#include "Libro.h"
#include "Usuario.h"
#include "comentario.h"

typedef struct{
    char titulo[100];
    char editorial[50];
    char autor[50];
    char categoria[50];
    float valoracion;
    int idComentario;  /// único, autoincremental
    int idLibro;
    int idUsuario;
    char tituloComentario[100];
    char descripcion[500];
    int puntaje; /// de 0 a 5 "estrellas"
    char fechaComentario[20]; /// o se puede hacer con dia, mes, anio.
    int eliminado; /// 0 si está activo - 1 si está eliminado
} stRegistro;


///pasaje de archivo a nuestra lista/arbol
stLibro refactorizacionLibro(stRegistro reg);
stComentario refactorizacionComentario(stRegistro reg);
nodoUsuario *archivoToArbolUsuarios(char nombre[], nodoUsuario *arbolUsuarios);
nodoLibro *  archivoToLDL(char nombreArchivo[], nodoLibro * ldl);
nodoLibro * alta(nodoLibro * ldl, stLibro libro, stComentario comentario);

///pasaje de la lista/arbol a los archivos
void listaToArchivoUsuarios(char nombre[], nodoUsuario * listaUsuario);
void listaToArchivoLibros(char nombre[], nodoLibro * listaLibro);

///funciones de verificacion
int esValidoEmail(char *email);
int esValidoPass(char *password);
int verificacionAtras(char *atras);
int esValidoValor(int valor, int maximo);
int compararCadenasIgnorandoMayusculas(const char *str1, const char *str2);

///menus
nodoUsuario * menuUsuario(nodoUsuario * user, nodoLibro * listaLibro, nodoUsuario * arbolUsuarios, int idUsuarioActual,int idLibroActual);
void menuLogin(nodoUsuario * arbolUsuarios, int idUsuarioActual, nodoLibro * listaLibro, int idLibroActual);
void menuAltaYBaja(nodoUsuario * arbolUsuarios, int idUsuarioActual, nodoLibro * listaLibro, int idLibroActual);
void menuLibros(nodoLibro * listaLibro, int idLibroActual,int idUsuarioActual);

int main()
{
    srand(time(NULL));
    nodoUsuario * arbolUsuarios = inicArbol();
    nodoLibro * ldl = inicArbol();

    ///PASAJE DEL ARCHIVO A LA LISTA

    arbolUsuarios = archivoToArbolUsuarios("usuarios.dat",arbolUsuarios);
    ldl = archivoToLDL("libros.dat",ldl);

    ///MENU Y BUSQUEDA DE ID

    nodoUsuario * auxUsuario = buscarUltimoUsuario(arbolUsuarios);
    nodoLibro * auxLibro = buscarUltimoLibro(ldl);
    int idUsuarioActual = auxUsuario->usuario.idUsuario, idLibroActual = auxLibro->libro.idLibro; ///id del ultimo libro y usuario
    menuLogin(arbolUsuarios,idUsuarioActual,ldl,idLibroActual); ///paso la lista de usuarios al menu y el numero de ID actual de usuario y libro, y la lista de libros

    ///PASAJE DE LISTA AL ARCHIVO
    guardarCambiosEnArchivo(ldl);
    arbolToArchivoUsuarios("usuarios.dat",arbolUsuarios);
    return 0;
}
///MENU INICIAL CON SIGN IN & REGISTRATION
void menuLogin(nodoUsuario * arbolUsuarios, int idUsuarioActual, nodoLibro * listaLibro,int idLibroActual)
{
    system("cls");
    int valor = 0, flag = 0; ///Valor es para el switch del menu, flag es para el log in
    char mail[20], pass[20]; /// Mail y contraseña para verificar el log in
    nodoUsuario * userAux = inicArbol();
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
        menuLogin(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual);
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
            menuLogin(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual);
        }
        else
        {
            userAux = buscarMailUsuario(arbolUsuarios, &mail);
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
                            userAux = menuUsuario(userAux,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual);
                            flag = 4;
                        }
                        else /// contraseña incorrecta
                        {
                            flag = flag+1;
                            printf("\nContraseña incorrecta, vuelva a intentar. Intentos: %i/3", flag);
                            printf("\n");
                        }
                    }
                }
                else /// la funcion devolvio NULL
                {
                    printf("\nEmail incorrecto, intente una vez mas o cree una cuenta nueva.\n");
                    menuLogin(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual); ///en caso de que no sea valido el mail, lo mando devuelta al principio
                }
            }
            else ///el usuario se encuentra dado de baja
            {
                printf("\nEl usuario se encuentra dado de baja, comuniquese con el soporte.\n");
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
            menuLogin(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual);
        }
        else
        {
            userAux = buscarMailUsuario(arbolUsuarios, mail); ///busco que el mail no se encuentre registrado previamente, funcion retorna el nodo si coincide y NULL si no encuentra el mail

            if(!userAux)  ///si la funcion anterior retorno null, significa que el mail no esta utilizado, y se prosigue con la creacion de usuario
            {
                stUsuario usuarioAux = cargarUsuario(&idUsuarioActual,mail); ///carga manual de usuario

                nodoUsuario * nuevoNodoUsuario = CrearNodoArbol(usuarioAux); ///creacion de nodo con usuario anterior

                arbolUsuarios = InsertarNodoArbol(arbolUsuarios, usuarioAux); ///agrego al final de la lista el nodoNuevo

                userAux = menuUsuario(nuevoNodoUsuario,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual); /// se rompe aca hay que ver porque
            }
            else
            {
                printf("\nEl mail ya se encuentra registrado, intente nuevamente.\n");
                system("pause");
                menuLogin(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual);
            }
        }
        break;
    case 3:
        return 0;
        break;
    }
    menuLogin(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual);
}
///MENU LOGGED USER
nodoUsuario * menuUsuario(nodoUsuario * usuarioLoged, nodoLibro * listaLibro, nodoUsuario * arbolUsuarios, int idUsuarioActual, int idLibroActual)
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
        printf("|5| Dar de baja o de alta un usuario/libro/comentario");
        printf("\n------------------------------------------\n");
    }
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    if(esValidoValor(valor,5) == 0)///Verificamos que la opcion ingresada sea valida
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual);
    }
    switch(valor)
    {
    case 1: ///modificar datos
        usuarioLoged->usuario = modificarUsuario(usuarioLoged->usuario,listaLibro);///Modificamos datos del usuario y se actualiza el archivo al finalizar
        menuUsuario(usuarioLoged,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 2: /// consultar libros por autor
        menuLibros(listaLibro,idLibroActual,usuarioLoged->usuario.idUsuario);///Ingresamos al menu de libros
        menuUsuario(usuarioLoged,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual);
        break;

    case 3: /// cerrar sesion
        return usuarioLoged;
        break;

    /// FUNCIONES DE ADMIN
    case 4:/// lista de usuarios
        mostrarArbolInOrder(arbolUsuarios); ///Ver data de usuarios
        printf("\n-----------------------\n");
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual);
        break;
    case 5: /// menu alta y baja usuarios y libros
        menuAltaYBaja(arbolUsuarios,idUsuarioActual,listaLibro,idLibroActual);///Funcion para dar de baja y alta un usuario o libro
        system("pause");
        menuUsuario(usuarioLoged,listaLibro,arbolUsuarios,idUsuarioActual,idLibroActual);
        break;
    }
    return usuarioLoged;
}

///MENU DE LIBROS
void menuLibros(nodoLibro * ldl, int idLibroActual,int idUsuarioActual)
{
    system("cls");
    int valor = 0, idComentario = 0;
    printf("-----------------------------------\n");
    printf("|1| Consulta libros por autor");
    printf("\n-----------------------------------\n");
    printf("|2| Consulta libros por categoria");
    printf("\n-----------------------------------\n");
    printf("|3| Ver todos los libros disponibles");
    printf("\n-----------------------------------\n");
    printf("|4| Agregar un comentario a un libro");
    printf("\n-----------------------------------\n");
    printf("|5| Ver comentarios de un libro");
    printf("\n-----------------------------------\n");
    printf("|6| Modificar un comentario propio");
    printf("\n-----------------------------------\n");
    printf("|7| Eliminar un comentario propio");
    printf("\n-----------------------------------\n");
    printf("|8| Volver al menu de usuario");
    printf("\n-----------------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    if(esValidoValor(valor,8) == 0)
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuLibros(ldl,idLibroActual, idUsuarioActual);
    }
    switch(valor)
    {
    case 1:
        muestraLibroPorAutor(ldl);/// Se verifica que el autor se encuentre dentro del archivo y muestra libros
        system("pause");
        menuLibros(ldl,idLibroActual,idUsuarioActual);
        break;
    case 2:
        muestraLibroPorCategoria(ldl);///Se verifica que se encuentre la categoria y libros, luego se muestra
        system("pause");
        menuLibros(ldl,idLibroActual,idUsuarioActual);
        break;
    case 3:
        system("cls");
        muestraListaLibro(ldl); ///mostramos todos los libros (que esten dados de alta)
        printf("\n-----------------------\n");
        system("pause");
        menuLibros(ldl,idLibroActual,idUsuarioActual);
        break;
    case 4:
        system("cls");
        printf("Id del libro que desea comentar");
        printf("\n>");
        fflush(stdin);
        scanf("%i", &idComentario);
        if (idComentario <= 0 || idComentario > idLibroActual)  ///verifico que la id este entre 0 y las id validas
        {
            printf("\nLa id no existe!\n");
            system("pause");
            menuLibros(ldl,idLibroActual,idUsuarioActual);
        }
        nodoLibro * libroABuscar = buscarIdLibro(ldl, idComentario);
        stComentario comentario = crearComentario(idComentario,idUsuarioActual);
        ldl = alta(ldl,libroABuscar->libro,comentario);
        break;
    case 5:
        system("cls");
        printf("Id del libro que desea ver comentarios");
        printf("\n>");
        fflush(stdin);
        scanf("%i", &idComentario);
        if (idComentario <= 0 || idComentario > idLibroActual)  ///verifico que la id este entre 0 y las id validas
        {
            printf("\nLa id no existe!\n");
            system("pause");
            menuLibros(ldl,idLibroActual,idUsuarioActual);
        }
        nodoLibro * libroAMostrar = buscarIdLibro(ldl, idComentario);
        mostrarListaComentarios(libroAMostrar->coment);
        system("pause");
        break;
    case 6:
        modificarComentariosPropios(ldl,idUsuarioActual,idLibroActual);
        system("pause");
        break;
    case 7:
        eliminarComentariosPropios(ldl,idUsuarioActual,idLibroActual);
        system("pause");
        break;
    case 8:
        return 0;
        break;
    }
}
///MENU DAR DE BAJA / ALTA USUARIO / LIBRO
void menuAltaYBaja(nodoUsuario * arbolUsuarios, int idUsuarioActual, nodoLibro * ldl, int idLibroActual)
{
    int valor = 0;
    int idBuscar =0;
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
    printf("|5| Dar de baja un comentario");
    printf("\n--------------------------\n");
    printf("|6| Dar de alta un comentario");
    printf("\n--------------------------\n");
    printf("|7| Volver al menu de usuario");
    printf("\n--------------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);

    if(esValidoValor(valor,7) == 0)
    {
        printf("\nPor favor introduzca un valor valido!\n");
        system("pause");
        menuAltaYBaja(arbolUsuarios,idUsuarioActual,ldl,idLibroActual);
    }
    switch(valor)
    {
    case 1:
        arbolUsuarios = darDeBajaUsuario(arbolUsuarios,idUsuarioActual);
        break;

    case 2:
        arbolUsuarios = darDeAltaUsuario(arbolUsuarios,idUsuarioActual);
        break;
    case 3:
        ldl = darDeBajaLibro(ldl,idLibroActual);
        break;
    case 4:
        ldl = darDeAltaLibro(ldl,idLibroActual);
        break;
    case 5:
        system("cls");
        printf("Id del libro al que desea borrar un comentario (-1 para volver atras!)");
        printf("\n>");
        fflush(stdin);
        scanf("%i", &idBuscar);
        if(idBuscar == -1 && idBuscar < idLibroActual)
        {
            printf("\nId Invalido!\n");
            system("pause");
            menuAltaYBaja(arbolUsuarios,idUsuarioActual,ldl,idLibroActual);
        }
        nodoLibro * libro = buscarIdLibro(ldl,idBuscar);
        libro->coment = darDeBajaComentario(libro->coment);
        break;
    case 6:
        system("cls");
        printf("Id del libro al que desea restaurar un comentario (-1 para volver atras!)");
        printf("\n>");
        fflush(stdin);
        scanf("%i", &idBuscar);
        if(idBuscar == -1 && idBuscar < idLibroActual)
        {
            printf("\nId Invalido!\n");
            system("pause");
            menuAltaYBaja(arbolUsuarios,idUsuarioActual,ldl,idLibroActual);
        }
        nodoLibro * libroABuscar = buscarIdLibro(ldl,idBuscar);
        libroABuscar->coment = darDeAltaComentario(libroABuscar->coment);
        break;
    case 7:
        return 0;
        break;
    }
}
///PASAJE ENTRE LISTAS Y ARCHIVOS
stLibro refactorizacionLibro(stRegistro reg)
{
    stLibro aux;

    strcpy(aux.autor, reg.autor);
    strcpy(aux.categoria, reg.categoria);
    strcpy(aux.editorial, reg.editorial);
    strcpy(aux.titulo, reg.titulo);
    aux.eliminado = reg.eliminado;
    aux.idLibro = reg.idLibro;
    aux.valoracion = reg.valoracion;
    return aux;
}

stComentario refactorizacionComentario(stRegistro reg)
{
    stComentario aux;

    strcpy(aux.descripcion, reg.descripcion);
    strcpy(aux.fechaComentario, reg.fechaComentario);
    strcpy(aux.tituloComentario, reg.tituloComentario);
    aux.idComentario = reg.idComentario;
    aux.puntaje = reg.puntaje;
    aux.idUsuario = reg.idUsuario;
    aux.eliminado = reg.eliminado;

    return aux;
}
void guardarCambiosEnArchivo(nodoLibro *ldl) {
    FILE *archivo = fopen("libros.dat", "wb");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para guardar los cambios.\n");
        return;
    }
    nodoLibro *currentLibro = ldl;

    while (currentLibro != NULL) {
        ///stRegistro para guardar la información del libro y sus comentarios
        stRegistro registro;

        /// Guardar la información del libro
        strcpy(registro.titulo, currentLibro->libro.titulo);
        strcpy(registro.editorial, currentLibro->libro.editorial);
        strcpy(registro.autor, currentLibro->libro.autor);
        strcpy(registro.categoria, currentLibro->libro.categoria);
        registro.valoracion = currentLibro->libro.valoracion;
        registro.idLibro = currentLibro->libro.idLibro;
        registro.eliminado = currentLibro->libro.eliminado;
        registro.idComentario = 0;  // Inicializamos idComentario en 0, se actualizará en el siguiente paso

        /// Inicializar los campos de comentarios como nulos
        registro.idUsuario = 0;
        registro.tituloComentario[0] = '\0';
        registro.descripcion[0] = '\0';
        registro.puntaje = 0;
        registro.fechaComentario[0] = '\0';

        // Guardar el libro en el archivo
        fwrite(&registro, sizeof(stRegistro), 1, archivo);

        // Recorrer los comentarios asociados al libro
        nodoComentario *currentComentario = currentLibro->coment;
        while (currentComentario != NULL) {
            // Actualizamos el idComentario y otros detalles
            registro.idComentario = currentComentario->coment.idComentario;
            registro.idUsuario = currentComentario->coment.idUsuario;
            strcpy(registro.tituloComentario, currentComentario->coment.tituloComentario);
            strcpy(registro.descripcion, currentComentario->coment.descripcion);
            registro.puntaje = currentComentario->coment.puntaje;
            strcpy(registro.fechaComentario, currentComentario->coment.fechaComentario);
            registro.eliminado = currentComentario->coment.eliminado;

            // Guardar el comentario en el archivo
            fwrite(&registro, sizeof(stRegistro), 1, archivo);

            // Mover al siguiente comentario
            currentComentario = currentComentario->sig;
        }

        // Mover al siguiente libro
        currentLibro = currentLibro->sig;
    }

    fclose(archivo);
}

/*stRegistro refactorizacionRegistro(nodoLibro * ldl)
{
    stRegistro aux;

    strcpy(aux.autor, ldl->libro.autor);
    strcpy(aux.categoria, ldl->libro.categoria);
    strcpy(aux.editorial, ldl->libro.editorial);
    strcpy(aux.titulo, ldl->libro.titulo);
    aux.valoracion = ldl->libro.valoracion;

    strcpy(aux.descripcion, ldl->coment->coment.descripcion);
    strcpy(aux.fechaComentario, ldl->coment->coment.fechaComentario);
    strcpy(aux.tituloComentario, ldl->coment->coment.tituloComentario);
    aux.eliminado = ldl->coment->coment.eliminado;
    aux.idLibro = ldl->coment->coment.idLibro;
    aux.idComentario = ldl->coment->coment.idComentario;
    aux.puntaje = ldl->coment->coment.puntaje;
    aux.idUsuario = ldl->coment->coment.idUsuario;

    return aux;
}*/
nodoUsuario *archivoToArbolUsuarios(char nombre[], nodoUsuario *arbolUsuarios)
{
    FILE *f = fopen(nombre, "rb");
    stUsuario aux;

    if (f)
    {
        while (fread(&aux, sizeof(stUsuario), 1, f) > 0)
        {
            arbolUsuarios = InsertarNodoArbol(arbolUsuarios, aux); // Insertamos en el árbol
        }
        fclose(f);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }

    return arbolUsuarios;
}

nodoLibro *  archivoToLDL(char nombreArchivo[], nodoLibro * ldl)
{
    FILE * archi = fopen(nombreArchivo, "rb");
    stRegistro aux;

    if(archi)
    {
        while(fread(&aux, sizeof(stRegistro),1,archi)>0)
        {
            stLibro libro = refactorizacionLibro(aux);
            stComentario comentario = refactorizacionComentario(aux);
            ldl = alta(ldl,libro,comentario);
        }

        fclose(archi);
    }
    return ldl;
}
/*void LdlToArchivo(char nombreArchivo[], nodoLibro * ldl)
{
    FILE *archi = fopen(nombreArchivo, "wb");
    stRegistro aux;

    if(archi)
    {
        while(fwrite(&aux, sizeof(stRegistro),1,archi)>0)
        {
            aux = refactorizacionRegistro(aux);


        }
    }
}*/

/*nodoUsuario * archivoToListaUsuario(char nombre[], nodoUsuario * listaUsuario)
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
}*/

void arbolToArchivoUsuarios(char nombre[], nodoUsuario *arbolUsuarios)
{
    FILE *f = fopen(nombre, "wb");
    if (f)
    {
        guardarEnArchivo(arbolUsuarios, f); // Función recursiva para recorrer y guardar
        fclose(f);
    }
    else
    {
        printf("Error al abrir el archivo.\n");
    }
}
void guardarEnArchivo(nodoUsuario *arbol, FILE *f)
{
    if (arbol)
    {
        fwrite(&arbol->usuario, sizeof(stUsuario), 1, f); // Escribimos el usuario actual
        guardarEnArchivo(arbol->izq, f);
        guardarEnArchivo(arbol->der, f);
    }
}

/*void listaToArchivoUsuarios(char nombre[], nodoUsuario * listaUsuario)
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
void listaToArchivoLibros(char nombre[], nodoLibro * listaLibro)
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
*/
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
int compararCadenasIgnorandoMayusculas(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (tolower(*str1) != tolower(*str2))
        {
            return 0; // No son iguales
        }
        str1++;
        str2++;
    }
    return *str1 == *str2; // Verifica si ambas cadenas terminan
}

nodoLibro * alta(nodoLibro * ldl, stLibro libro, stComentario comentario)
{
    nodoLibro * libroABuscar = buscarIdLibro(ldl, libro.idLibro);
    if(!libroABuscar)
    {
        libroABuscar = crearNodoLibro(libro);
        ldl = agregarAlFinalLibro(ldl,libroABuscar);
    }
    libroABuscar->coment = agregarAlFinalComentario(libroABuscar->coment, crearNodoComentario(comentario));
    return ldl;
}
