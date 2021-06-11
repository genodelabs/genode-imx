
#include <linux/sched.h>
#include <lx_emul/task.h>

void __set_task_comm(struct task_struct * tsk,const char * buf,bool exec)
{
	strlcpy(tsk->comm, buf, sizeof(tsk->comm));
	lx_emul_task_name(tsk, tsk->comm);
}
