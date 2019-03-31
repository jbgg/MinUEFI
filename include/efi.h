
#ifndef __EFI_H__
#define __EFI_H__

#include <types.h>

/* data types for UEFI */

typedef uint8_t BOOLEAN;

/* system is 64 bits */
typedef int64_t INTN;
typedef uint64_t UINTN;
typedef int8_t INT8;
typedef uint8_t UINT8;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
/* XXX: INT128 and UINT128 not implemented */

typedef uint8_t CHAR8;
typedef uint16_t CHAR16;

typedef void VOID;

/* XXX: EFI_GUID not implemented */

typedef UINTN EFI_STATUS;
typedef VOID* EFI_HANDLE;
typedef VOID* EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;

/* TPL's definitions */
#define TPL_APPLICATION 4
#define TPL_CALLBACK 8
#define TPL_NOTIFY 16
#define TPL_HIGH_LEVEL 31

/* Memory's typedef and definitions */
typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;
typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;


/* XXX: EFI_MAC_ADDRESS, EFI_IPv4_ADDRESS, EFI_IPv6_ADDRESS, EFI_IP_ADDRESS
 * not implemented
*/

/* EFI_SYSTEM_TABLE */
struct efi_system_table;

/* EFI_TABLE_HEADER */
struct efi_table_header;

/* EFI_RUNTIME_SERVICES */
struct efi_runtime_services;

/* EFI_BOOT_SERVICES */
struct efi_boot_services;
typedef EFI_TPL (*EFI_RAISE_TPL)(
        EFI_TPL);
typedef VOID (*EFI_RESTORE_TPL)(
        EFI_TPL);
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(
        EFI_ALLOCATE_TYPE, EFI_MEMORY_TYPE, UINTN, EFI_PHYSICAL_ADDRESS);
struct efi_memory_descriptor;
typedef EFI_STATUS (*EFI_FREE_PAGES)(
        EFI_PHYSICAL_ADDRESS, UINTN);
typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(
        UINTN*, struct efi_memory_descriptor*, UINTN*, UINTN*, UINT32*);
typedef EFI_STATUS (*EFI_ALLOCATE_POOL)(
        EFI_MEMORY_TYPE, UINTN, VOID**);
typedef EFI_STATUS (*EFI_FREE_POOL)(
        VOID*);

/* EFI_CONFIGURATION_TABLE */
struct efi_configuration_table;

/* EFI_SIMPLE_TEXT_INPUT_PROTOCOL */
struct efi_simple_text_input_protocol;

/* EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL */
struct efi_simple_text_output_protocol;
struct simple_text_output_mode;
typedef EFI_STATUS (*EFI_TEXT_RESET)(
        struct efi_simple_text_output_protocol*, BOOLEAN);
typedef EFI_STATUS (*EFI_TEXT_STRING)(
        struct efi_simple_text_output_protocol*, CHAR16*);
typedef EFI_STATUS (*EFI_TEXT_TEST_STRING)(
        struct efi_simple_text_output_protocol*, CHAR16*);
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE)(
        struct efi_simple_text_output_protocol*, UINTN, UINTN, UINTN);
typedef EFI_STATUS (*EFI_TEXT_SET_MODE)(
        struct efi_simple_text_output_protocol*, UINTN);
typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE)(
        struct efi_simple_text_output_protocol*, UINTN);
typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN)(
    struct efi_simple_text_output_protocol*);
typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION)(
    struct efi_simple_text_output_protocol*, UINTN, UINTN);
typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR)(
    struct efi_simple_text_output_protocol*, BOOLEAN);


struct efi_table_header {
    UINT64 sig;
    UINT32 rev;
    UINT32 hdrsize;
    UINT32 crc32;
    UINT32 rsv;
};

/* XXX: not implemented */
struct efi_simple_text_input_protocol {

};

struct simple_text_output_mode {
    INT32 maxMode;
    INT32 mode;
    INT32 attr;
    INT32 cursorCol;
    INT32 cursorRow;
    BOOLEAN cursorVis;
};

struct efi_simple_text_output_protocol {
    EFI_TEXT_RESET reset;
    EFI_TEXT_STRING outputString;
    EFI_TEXT_TEST_STRING testString;
    EFI_TEXT_QUERY_MODE queryMode;
    EFI_TEXT_SET_MODE setMode;
    EFI_TEXT_SET_ATTRIBUTE setAttr;
    EFI_TEXT_CLEAR_SCREEN clearScreen;
    EFI_TEXT_SET_CURSOR_POSITION setCursorPos;
    EFI_TEXT_ENABLE_CURSOR enableCursor;
    struct simple_text_output_mode *mode;
};

/* XXX: not implemented */
struct efi_runtime_services {

};

struct efi_memory_descriptor {
    UINT32 type;
    EFI_PHYSICAL_ADDRESS physicalStart;
    EFI_VIRTUAL_ADDRESS virtualStart;
    UINT64 nPages;
    UINT64 attr;
};

/* XXX: not implemented */
struct efi_boot_services {
    struct efi_table_header hdr;
    EFI_RAISE_TPL raiseTPL;
    EFI_RESTORE_TPL restoreTPL;
    EFI_ALLOCATE_PAGES allocatePages;
    EFI_FREE_PAGES freePages;
    EFI_GET_MEMORY_MAP getMemoryMap;
    EFI_ALLOCATE_POOL allocatePool;
    EFI_FREE_POOL freePool;
    /* TODO: finish it */
};

/* XXX: not implemented */
struct efi_configuration_table {

};

struct efi_system_table {
    struct efi_table_header hdr;
    CHAR16 *firmwareVendor;
    UINT32 firmwareRev;
    EFI_HANDLE consoleInHndl;
    struct efi_simple_text_input_protocol *conIn;
    EFI_HANDLE consoleOutHndl;
    struct efi_simple_text_output_protocol *conOut;
    EFI_HANDLE stdErrorHandle;
    struct efi_simple_text_output_protocol *stdErr;
    struct efi_runtime_services *runtimeSrv;
    struct efi_boot_services *bootSrv;
    UINTN nEntries;
    struct efi_configuration_table *configTable;
};


#endif /* __EFI_H__ */

