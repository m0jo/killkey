#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/interrupt.h>

void kill_process(void){
    struct task_struct* task_list;
    struct task_struct* target_task = NULL;
    u64 max_utime = 0;

    for_each_process(task_list) {
        if(task_list->utime > max_utime){
            max_utime = task_list->utime;
            target_task = task_list;
        }
    }

    if(target_task){
        printk("EMERGENCY KILLING %s!\n", target_task->comm);
        send_sig(SIGKILL, target_task, 0);
    }

}

irq_handler_t irq_handler (int irq, void *dev_id, struct pt_regs *regs) {

    unsigned char scancode = inb (0x60);

    //PAUSE-Key
    if (scancode == 0xe1){
      printk ("EMERGENCY KEY PRESSED, ABOUT TO KILL A PROCESS\n");
      kill_process();
    }

    return (irq_handler_t) IRQ_HANDLED;
}

int init_module(void){
        printk(KERN_INFO "Initializing Emergency key\n");
        return request_irq (1, (irq_handler_t) irq_handler, IRQF_SHARED, "keyboard_stats_irq", (void *)(irq_handler));

}

void cleanup_module(void){
        printk(KERN_INFO "Emergency key shutdown\n");
        free_irq(1, (void *)(irq_handler));
}

MODULE_LICENSE("MIT");
