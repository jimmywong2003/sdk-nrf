/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <zephyr.h>
#include "tkc/mem.h"
#include "tkc/mutex.h"

struct _tk_mutex_t {
	struct k_mutex mutex;
};

tk_mutex_t* tk_mutex_create(void)
{
	tk_mutex_t* mutex;

	mutex = TKMEM_ZALLOC(tk_mutex_t);
	return_value_if_fail(mutex != NULL, NULL);

	int err;

	err = k_mutex_init(&mutex->mutex);
	return (!err) ? mutex : NULL;
}

ret_t tk_mutex_lock(tk_mutex_t* mutex)
{
	return_value_if_fail(mutex != NULL, RET_BAD_PARAMS);

	int err;

	err = k_mutex_lock(&mutex->mutex, K_FOREVER);
	return (!err) ? RET_OK : RET_FAIL;
}

ret_t tk_mutex_unlock(tk_mutex_t* mutex)
{
	return_value_if_fail(mutex != NULL, RET_BAD_PARAMS);

	int err;

	err = k_mutex_unlock(&mutex->mutex);
	return (!err) ? RET_OK : RET_FAIL;
}

ret_t tk_mutex_destroy(tk_mutex_t* mutex)
{
	return_value_if_fail(mutex != NULL, RET_BAD_PARAMS);

	TKMEM_FREE(mutex);

	return RET_OK;
}
