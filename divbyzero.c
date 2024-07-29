#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Custom signal handler for divide-by-zero exception");
MODULE_VERSION("1.0");

static irqreturn_t custom_signal_handler(int irq, void *dev_id) {
    printk(KERN_INFO "Custom signal received: Divide-by-zero exception occurred in user mode.\n");
    return IRQ_HANDLED;
}

static int __init custom_signal_init(void) {
    printk(KERN_INFO "Custom signal handler loaded.\n");

    // Register custom signal handler for SIGUSR1
    if (request_irq(SIGUSR1, custom_signal_handler, IRQF_SHARED, "custom_signal_handler", NULL)) {
        printk(KERN_ERR "Failed to register custom signal handler.\n");
        return -EFAULT;
    }

    return 0;
}

static void __exit custom_signal_exit(void) {
    free_irq(SIGUSR1, NULL);
    printk(KERN_INFO "Custom signal handler unloaded.\n");
}

module_init(custom_signal_init);
module_exit(custom_signal_exit);
