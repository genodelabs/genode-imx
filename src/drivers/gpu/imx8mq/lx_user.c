/*
 * \brief  Post kernel userland activity
 * \author Josef Soentgen
 * \date   2024-01-12
 */

/*
 * Copyright (C) 2024 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* DDE Linux */
#include <lx_emul/task.h>
#include <lx_user/init.h>
#include <lx_user/io.h>

/* Linux */
#include <linux/sched/task.h>

/* local includes */
#include "lx_user.h"


struct task_struct * lx_user_task;
void               * lx_user_task_args;

extern int lx_user_task_func(void *p);


void lx_user_handle_io(void) { }


static int _startup_finished = 0;

int lx_user_startup_complete(void *) { return _startup_finished; }


void lx_user_init(void)
{
	int pid = kernel_thread(lx_user_task_func, lx_user_task_args,
	                        CLONE_FS | CLONE_FILES);
	lx_user_task = find_task_by_pid_ns(pid, NULL);

	_startup_finished = 1;
}


struct task_struct *lx_user_new_gpu_task(int (*func)(void*), void *args)
{
	int pid = kernel_thread(func, args, CLONE_FS | CLONE_FILES);
	return find_task_by_pid_ns(pid, NULL);
}


void lx_user_destroy_gpu_task(struct task_struct *task)
{
	if (task != current) {
		printk("%s: task: %px is not current: %px\n", __func__,
		       task, current);
		return;
	}

	do_exit(0);
}
