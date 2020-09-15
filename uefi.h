#include <stdint.h>
#include <wchar.h>

#define EFIAPI __attribute__((ms_abi))

typedef void *EFI_HANDLE;
typedef uint64_t UINTN;
typedef UINTN EFI_STATUS;
typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING)(
        void *This,
        const wchar_t *String
);

typedef struct {
    EFI_HANDLE Reset;
    EFI_TEXT_STRING OutputString;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

//-------------------------------------------------------------

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
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef EFI_STATUS (EFIAPI *EFI_ALLOCATE_PAGES)(
        EFI_ALLOCATE_TYPE Type,
        EFI_MEMORY_TYPE MemoryType,
        UINTN Pages,
        EFI_PHYSICAL_ADDRESS *Memory
);

typedef struct {
    uint32_t Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;


typedef EFI_STATUS (EFIAPI *EFI_GET_MEMORY_MAP)(
        UINTN *MemoryMapSize,
        EFI_MEMORY_DESCRIPTOR *MemoryMap,
        UINTN *MapKey,
        UINTN *DescriptorSize,
        uint32_t *DescriptorVersion
);

typedef struct {
    uint8_t Padding1[40];
    EFI_ALLOCATE_PAGES AllocatePages;
    uint8_t Padding2[8];
    EFI_GET_MEMORY_MAP GetMemoryMap;
} EFI_BOOT_SERVICES;

//-------------------------------------------------------------

typedef struct {
    uint8_t Padding1[52];
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    uint8_t Padding2[24];
    EFI_BOOT_SERVICES *BootServices;
} EFI_SYSTEM_TABLE;

wchar_t *UInt2Hex(uint64_t x, wchar_t *buffer, int size);
wchar_t *UInt2Dec(uint64_t x, wchar_t *buffer, int size);

#define Print(X) (SystemTable->ConOut->OutputString(SystemTable->ConOut, (X)))