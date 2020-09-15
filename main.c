#include "uefi.h"

EFI_STATUS EFIAPI EfiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    Print(L"EFI entry point\n\n");

    EFI_STATUS status;
    UINTN memory_map_size = 0;
    EFI_MEMORY_DESCRIPTOR *memory_map = NULL;
    UINTN map_key = 0;
    UINTN descriptor_size = 0;
    uint32_t version = 0;

    SystemTable->BootServices->GetMemoryMap(&memory_map_size, memory_map, &map_key, &descriptor_size, &version);

    wchar_t strbuffer[50];


    UINTN newSize = memory_map_size + (2 * descriptor_size);
    void *buffer = NULL;
    status = SystemTable->BootServices->AllocatePages(AllocateAnyPages, EfiLoaderData, newSize, &buffer);


    memory_map = (EFI_MEMORY_DESCRIPTOR *) buffer;
    memory_map_size = newSize;

    status = SystemTable->BootServices->GetMemoryMap(&memory_map_size, memory_map, &map_key, &descriptor_size,
                                                     &version);

    uint64_t totMem = 0;

    if (status != 0) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Failed1\n");
    } else {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Succ1\n");
        uint8_t *mem = (uint8_t *) memory_map;

        for (int i = 0; i < (memory_map_size / descriptor_size); ++i) {
            EFI_MEMORY_DESCRIPTOR desc = *((EFI_MEMORY_DESCRIPTOR *) mem);
            Print(L"Physical start: ");
            Print(UInt2Hex(desc.PhysicalStart, strbuffer, 50));
            Print(L"\nVirtual start: ");
            Print(UInt2Hex(desc.VirtualStart, strbuffer, 50));
            Print(L"\nType: ");
            Print(UInt2Hex(desc.Type, buffer, 50));
            Print(L"\nNumber of pages: ");
            Print(UInt2Hex(desc.NumberOfPages, strbuffer, 50));
            Print(L" (4KB)\n\n");

            totMem += desc.NumberOfPages << 2u;

            mem += descriptor_size;
        }

        Print(L"Total RAM: ");
        Print(UInt2Dec(totMem, strbuffer, 50));
        Print(L" KB\n");

    }


    while (1);
    return 0;
}
