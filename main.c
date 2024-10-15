#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "NodoLibro.h"
#include "NodoUsuario.h"
#include "Libro.h"
#include "Usuario.h"

///funcion modificar libros no se si esta bien

nodoUsuario * archivoToListaUsuario(char nombre[], nodoUsuario * listaUsuario);
nodoLibro * archivoToListaLibro(char nombre[], nodoLibro * listaLibro);
void listaToArchivoUsuarios(char nombre[], nodoUsuario * listaUsuario);
void listaToArchivoLibros(char nombre[], nodoLibro * listaLibro);
int esValidoEmail(char *email);
int esValidoPass(char *password);
nodoUsuario * menuUsuario(nodoUsuario * user, nodoLibro * listaLibro, nodoUsuario * listaUsuarios, int idUsuarioActual);
void menuLogin(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro);

int main()
{
    nodoUsuario * listaUsuarios = inicLista();
    nodoLibro * listaLibro = inicLista();

    ///PASAJE DEL ARCHIVO A LA LISTA
    listaUsuarios = archivoToListaUsuario("usuarios.dat",listaUsuarios);
    listaLibro = archivoToListaLibro("libros.dat",listaLibro);

    nodoUsuario* aux = buscarUltimo(listaUsuarios);
    int idUsuarioActual = aux->usuario.idUsuario;

    menuLogin(listaUsuarios, idUsuarioActual,listaLibro); ///paso la lista al menu y el numero de ID actual, en caso de que deba crear un nuevo user
    ///PASAJE DE LISTA AL ARCHIVO
    listaToArchivoLibros("libros.dat",listaLibro);
    listaToArchivoUsuarios("usuarios.dat",listaUsuarios);
    return 0;
}

void menuLogin(nodoUsuario * listaUsuarios, int idUsuarioActual, nodoLibro * listaLibro)
{
    system("cls");
    int valor = 0, flag = 0; ///Valor es para el switch del menu, flag es para el log in
    char mail[20], pass[20]; /// Mail y contraseña para verificar el log in
    nodoUsuario * userAux = inicLista();
    printf("-----------------------\n");
    printf("1. Ingrese con su cuenta.");
    printf("\n-----------------------\n");
    printf("\n2. Cree una cuenta nueva.");
    printf("\n-----------------------\n");
    printf("\n3. Salir del programa.");
    printf("\n-----------------------\n");
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);
    system("cls");
    switch(valor)   ///Menu de logeo y creacion de cuenta
    {
    case 1: /// Log con cuenta ya registrada
        printf("-----------------------\n");
        printf("Ingrese su email: ");
        printf("\n-----------------------\n");
        printf("\n>");
        fflush(stdin);
        gets(mail);
        if (!esValidoEmail(mail))
        {
            printf("\nEmail invalido. Debe contener un '@' y '.com'.\n");
            system("pause");
            menuLogin(listaUsuarios,idUsuarioActual,listaLibro);
        }
        else
        {
            userAux = buscarMailUsuario(listaUsuarios, &mail);
            if(userAux)  ///Si lo encontro en la funcion buscarMailUsuario no deberia ser null, asi que pido la pass
            {
                while(flag < 3)
                {
                    printf("-----------------------\n");
                    printf("\nIngrese su contrasenia: ");
                    printf("\n-----------------------\n");
                    printf("\n>");
                    fflush(stdin);
                    gets(pass);
                    if(strcmp(userAux->usuario.password, pass) == 0)
                    {
                        ///Ya comprobado el mail, si introduce bien la pass, al menu de usuarios(en proceso)
                        menuUsuario(userAux,listaLibro,listaUsuarios,idUsuarioActual);
                    }
                    else
                    {
                        flag = flag+1;
                        printf("\nContraseña incorrecta, vuelva a intentar. Intentos: %i/3", flag);
                    }
                }
            }
            else
            {
                printf("\nEmail incorrecto, intente una vez mas o cree una cuenta nueva.\n");
                menuLogin(listaUsuarios,idUsuarioActual,listaLibro); ///en caso de que no sea valido el mail, lo mando devuelta al principio
            }
        }
        break;
    case 2: /// Crear cuenta
        printf("\n-----------------------\n");
        printf("Ingrese su email: ");
        printf("\n-----------------------\n");
        printf("\n>");
        fflush(stdin);
        gets(mail);
        if (!esValidoEmail(mail))
        {
            printf("\nEmail inválido. Debe contener un '@' y '.com'.\n");
            system("pause");
            menuLogin(listaUsuarios,idUsuarioActual,listaLibro);
        }
        else
        {
            userAux = buscarMailUsuario(listaUsuarios, mail); ///busco que el mail no se encuentre registrado previamente, funcion retorna el nodo si coincide y NULL si no encuentra el mail

            if(!userAux)  ///si la funcion anterior retorno null, significa que el mail no esta utilizado, y se prosigue con la creacion de usuario
            {
                stUsuario usuarioAux = cargarUsuario(idUsuarioActual,mail); ///carga manual de usuario

                nodoUsuario * nuevoNodoUsuario = crearNodoUsuario(usuarioAux); ///creacion de nodo con usuario anterior

                listaUsuarios = agregarAlFinalUsuario(listaUsuarios, nuevoNodoUsuario); ///agrego al final de la lista el nodoNuevo

                userAux = menuUsuario(nuevoNodoUsuario,listaLibro,listaUsuarios,idUsuarioActual); /// se rompe aca hay que ver porque
            }
            else
            {
                printf("\nEl mail ya se encuentra registrado, intente nuevamente.\n");
                system("pause");
                menuLogin(listaUsuarios,idUsuarioActual,listaLibro);
            }
        }
        break;
    case 3:
        return 0;
        break;
    }
}

nodoUsuario * menuUsuario(nodoUsuario * usuarioLoged, nodoLibro * listaLibro, nodoUsuario * listaUsuarios, int idUsuarioActual)
{
    system("cls");
    int valor = 0;
    printf("-----------------------\n");
    printf("Bienvenido %s",usuarioLoged->usuario.username);
    printf("\n-----------------------\n");
    printf("\n1. Modificar datos.");
    printf("\n-----------------------\n");
    printf("\n2. Cerrar sesion.");
    printf("\n-----------------------\n");
    if(usuarioLoged->usuario.esAdmin == 1) ///solo se muestran estas opciones si el usuario es un admin
    {
        printf("\n3. Ver Usuarios registrados.");
        printf("\n-----------------------\n");
        printf("\n4. Dar de baja usuario.");
        printf("\n-----------------------\n");
    }
    printf("\n>");
    fflush(stdin);
    scanf("%i", &valor);

    switch(valor)
    {
    case 1:
        usuarioLoged->usuario = modificarUsuario(usuarioLoged->usuario,listaLibro);
        menuUsuario(usuarioLoged,listaLibro,listaUsuarios,idUsuarioActual);
        break;
    case 2:
        menuLogin(listaUsuarios,idUsuarioActual,listaLibro);
        break;
    case 3:
        muestraLista(listaUsuarios);
        break;
    case 4:
        break;
    }
    system("pause");
    return usuarioLoged;
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
    FILE * f = fopen(nombre, "rb");
    stLibro aux;
    nodoLibro * nuevo;
    if(f)
    {
        while(fread(&aux,sizeof(nodoLibro),1,f) > 0)
        {
            nuevo = crearNodoLibro(aux);
            listaLibro = agregarAlFinalLibro(listaLibro,nuevo);
        }
    }
    fclose(f);
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

int esValidoEmail(char *email)
{
    /// Verifica que contenga un @ y un .com
    const char *at = strchr(email, '@');
    if (at == NULL || strstr(at, ".com") == NULL)
    {
        return 0; /// 0 si es no valido
    }
    return 1; /// 1 si es valido
}

int esValidoPass(char *password)
{
    int has_upper = 0, has_lower = 0;
    for (int i = 0; password[i] != '\0'; i++)
    {
        if (isupper(password[i]))
        {
            has_upper = 1;
        }
        if (islower(password[i]))
        {
            has_lower = 1;
        }
    }
    return has_upper && has_lower;
}


/// MOSTRAR LIBROS

void mostrarLibrosDesdeArchivo()
{

    FILE *archivo = fopen("libros.dat", "rb");  // Abrir archivo en modo binario
    printf("aca estoy");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
    }
    else
    {

        stLibro libro;
        while (fread(&libro, sizeof(stLibro), 1, archivo) == 1)
        {
            // Mostrar datos del libro
            printf("ID Libro: %d\n", libro.idLibro);
            printf("Título: %s\n", libro.titulo);
            printf("Editorial: %s\n", libro.editorial);
            printf("Autor: %s\n", libro.autor);
            printf("Categoría: %s\n", libro.categoria);
            printf("Valoración: %.2f\n", libro.valoracion);
            printf("Eliminado: %d\n", libro.eliminado ? 1 : 0);  // Mostrar 1 si está eliminado, 0 si está activo

            printf("\n--------------------------------\n");
        }
    }

    fclose(archivo);
}

/// MOSTRAR USUARIOS


void mostrarUsuariosDesdeArchivo()
{
    FILE *archivo = fopen("usuarios.dat", "rb");  // Abrir archivo en modo binario
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    stUsuario usuario;
    while (fread(&usuario, sizeof(stUsuario), 1, archivo) == 1)
    {
        // Mostrar datos del usuario
        printf("ID Usuario: %d\n", usuario.idUsuario);
        printf("Email: %s\n", usuario.email);
        printf("Username: %s\n", usuario.username);
        printf("Es Admin: %d\n", usuario.esAdmin);
        printf("Genero: %c\n", usuario.genero);
        printf("Fecha de Nacimiento: %s\n", usuario.fechaNacimiento);
        printf("DNI: %s\n", usuario.dni);
        printf("Eliminado: %d\n", usuario.eliminado);

        // Mostrar libros favoritos
        printf("Libros Favoritos (%d):\n", usuario.validosLibrosFavs);
        for (int i = 0; i < usuario.validosLibrosFavs; i++)
        {
            printf("  Libro ID: %d\n", usuario.librosFavoritos[i]);
        }

        // Mostrar domicilio
        printf("Domicilio:\n");
        printf("  Calle: %s\n", usuario.domicilio.calle);
        printf("  Altura: %d\n", usuario.domicilio.altura);
        printf("  Código Postal: %d\n", usuario.domicilio.cp);
        printf("  Ciudad: %s\n", usuario.domicilio.ciudad);
        printf("  Localidad: %s\n", usuario.domicilio.localidad);
        printf("  País: %s\n", usuario.domicilio.pais);

        printf("\n--------------------------------\n");
    }
    fclose(archivo);
}

