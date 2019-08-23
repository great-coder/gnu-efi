/*
 * ctors.c
 * Copyright 2019 Peter Jones <pjones@redhat.com>
 *
 */

#include <efi.h>
#include <efilib.h>

extern UINTN _init_array, _init_array_end;
extern UINTN __CTOR_LIST__, __CTOR_END__;
extern UINTN _fini_array, _fini_array_end;
extern UINTN __DTOR_LIST__, __DTOR_END__;

typedef void (*funcp)(void);

void _ctors(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
	InitializeLib(image, systab);

	for (funcp *location = (void *)&_init_array; location < (funcp *)&_init_array_end; location++) {
		funcp func = *location;
		func();
	}

	for (funcp *location = (void *)&__CTOR_LIST__; location < (funcp *)&__CTOR_END__; location++) {
		funcp func = *location;
		func();
	}
}

void _dtors(EFI_HANDLE image EFI_UNUSED, EFI_SYSTEM_TABLE *systab EFI_UNUSED)
{
	for (funcp *location = (void *)&__DTOR_LIST__; location < (funcp *)&__DTOR_END__; location++) {
		funcp func = *location;
		func();
	}

	for (funcp *location = (void *)&_fini_array; location < (funcp *)&_fini_array_end; location++) {
		funcp func = *location;
		func();
	}
}

// vim:fenc=utf-8:tw=75:noet
