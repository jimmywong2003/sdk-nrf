/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef __WCHAR_H__
#define __WCHAR_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t wcslen(const wchar_t* s);

int wcscmp(const wchar_t* s1, const wchar_t* s2);

wchar_t* wcscpy(wchar_t* s1, const wchar_t* s2);

wchar_t* wcschr(const wchar_t* s, wchar_t c);

wchar_t* wcsdup(const wchar_t* s);

#ifdef __cplusplus
}
#endif

#endif
