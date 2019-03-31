
#include <types.h>
#include <efi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, struct efi_system_table *SystemTable){

    /* quiet unused warning */
    ImageHandle = (EFI_HANDLE) (ImageHandle);

    SystemTable->conOut->outputString(
            SystemTable->conOut, L"Hello world from uefi!\n");
    
    __asm__ __volatile__ ("cli;");

    for(;;){
        __asm__ __volatile__ ("hlt;");
    }

    return 0;
}

