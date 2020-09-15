#include "uefi.h"

static wchar_t alpha[] = L"0123456789ABCDEF";

wchar_t *UInt2Hex(uint64_t x, wchar_t *const buffer, const int size) {
    int i;
    uint_fast8_t nibble;

    buffer[size - 1] = L'\0';

    for (i = size - 2; i >= 0 && x != 0; i--) {
        nibble = x & 0xFu;
        buffer[i] = alpha[nibble];

        x >>= 4u; //Eats away a nibble
    }

    return buffer + i + 1;
}

wchar_t *UInt2Dec(uint64_t x, wchar_t *const buffer, const int size) {
    int i;
    uint_fast8_t digit;

    buffer[size - 1] = L'\0';

    for (i = size - 2; i >= 0 && x != 0; i--) {
        digit = x % 10;
        buffer[i] = alpha[digit];

        x /= 10;
    }

    return buffer + i + 1;
}