#include <windows.h>
#include <tchar.h>
//#include <system_error.h>
//#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>


int crear(char* );
HANDLE abrir(char* );
int escribir(HANDLE);


int main(int argc, char const *argv[]) {

  //crear("hola.txt");
  HANDLE hFile = abrir("hola.txt");

  escribir(hFile);

  

  return 0;
}

int crear(char* dir){
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

    //int fd = _open_osfhandle(h, 0);

    //printf("fd %d\n", fd);

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
