#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int crear(char* );

void leer ();


int main(int argc, char const *argv[]) {

  crear("hola.txt");

  return 0;
}

int crear(char* dir){

  {
    HANDLE h = CreateFile(
        dir,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_TEMPORARY,
        NULL);

    if (h == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        printf("err %d\n", err);
        return 1;
    }
    printf("%p\n", h);

    int fd = _open_osfhandle(h, 0);

    printf("fd %d\n", fd);

    return 0;

}
