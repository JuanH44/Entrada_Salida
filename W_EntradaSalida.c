#include <windows.h>
#include <tchar.h>
//#include <system_error.h>
//#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>


int crear(char* );
HANDLE abrir(char* );
int escribir(HANDLE);
void menu(int *n);


int main(int argc, char const *argv[]) {
  int n;

  do{
    menu(&n);
  }while(n!=0);

  return 0;
}

void menu(int* n){
  system("cls");
  printf(
    "\n\tSeleccione una opcion:"
    "\n\t 1. Crear"
    "\n\t 2. Leer"
    "\n\t 3. Escribir"
    "\n\t 4. Renombrar"
    "\n\t 5. Agregar al final"
    "\n\t Eleccion: ");
    scanf("%d", n);
  switch (*n) {
    case 1:
      crear("hola3.txt");
    break;
    case 2:
      //abrir
    break;
    case 3:
      //leer
    break;
    case 4:
      //escribir
    break;
    case 5:
     //renombrar
    break;
    case 6:
     //agregar al final
    break;
    case 7:
     //cerrar
    break;
    default:
      printf("\n\tHasta luego!");

  }
  printf("\n\t");
  system("pause");
  fflush(stdin);
}

int crear(char* dir){
    char nombre[32];
    fflush(stdin);
    printf("\n\tIngrese el nombre del archivo:\n\t");
    scanf("%[^\n]",nombre);

    HANDLE h = CreateFile(
        nombre,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_TEMPORARY,
        NULL);

    if (h == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        printf("\n\t[!] A ocurrido un error al crear el archivo %lu\n", err);
        return 1;
    }
    printf("\n\t[+] Se ha creado el archivo satisfatoriamente\n");

    CloseHandle(h);
    return 0;
}


HANDLE abrir(char* dir){
    HANDLE h = CreateFile(
        dir,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_TEMPORARY,
        NULL);

    if (h == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        printf("err %d\n", err);
        return NULL;
    }
    printf("%p\n", h);

    //int fd = _open_osfhandle(h, 0);

    //printf("fd %d\n", fd);

    return h;
}


int escribir(HANDLE hFile){
  char DataBuffer[] = "This is some test data to write to the file.";
    DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
    DWORD dwBytesWritten = 0;
    BOOL bErrorFlag = FALSE;
  bErrorFlag = WriteFile(
                   hFile,           // open file handle
                   DataBuffer,      // start of data to write
                   dwBytesToWrite,  // number of bytes to write
                   &dwBytesWritten, // number of bytes that were written
                   NULL);            // no overlapped structure

   if (FALSE == bErrorFlag)
   {
       //DisplayError(TEXT("WriteFile"));
       printf("Terminal failure: Unable to write to file.\n");
   }
   else
   {
       if (dwBytesWritten != dwBytesToWrite)
       {
           // This is an error because a synchronous write that results in
           // success (WriteFile returns TRUE) should write all data as
           // requested. This would not necessarily be the case for
           // asynchronous writes.
           printf("Error: dwBytesWritten != dwBytesToWrite\n");
       }
       else
       {
           printf("Wrote %d bytes successfully.\n", dwBytesWritten);
       }
   }

   CloseHandle(hFile);
}



/*
int leer()
  BOOL ReadFile(
[in]                HANDLE       hFile,
[out]               LPVOID       lpBuffer,
[in]                DWORD        nNumberOfBytesToRead,
[out, optional]     LPDWORD      lpNumberOfBytesRead,
[in, out, optional] LPOVERLAPPED lpOverlapped
);
*/
