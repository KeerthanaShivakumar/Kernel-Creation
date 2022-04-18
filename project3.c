//Code includes test cases created
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/printk.h>
#include<linux/sched.h>
void dfs(struct task_struct *task){
	struct task_struct *task_next;
	struct list_head *list;
	list_for_each(list, &task->children) {
    		task_next = list_entry(list, struct task_struct, sibling);
		if(task->pid==0)//child process
    		printk(KERN_INFO "\t\tChild:- pid: %d | pname: %s | state: %ld\n", task_next->pid, task_next->comm, task_next->state);
		else if(task->pid>0)//parent process
    		printk(KERN_INFO "Parent:- pid: %d | pname: %s | state: %ld\n", task_next->pid, task_next->comm, task_next->state);
		dfs(task_next);
		
  		}  
}
int tasks_lister_dfs_init(void)
{
  printk(KERN_INFO "Loading module...\n");
  dfs(&init_task);
  printk(KERN_INFO "Module loaded.\n");
  return 0;
}
void tasks_lister_dfs_exit(void)
{
  printk(KERN_INFO "Module removed.\n");
}

module_init(tasks_lister_dfs_init);
module_exit(tasks_lister_dfs_exit);

