#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <rv/dummy_monitor.h>

#define MODULE_NAME "dummy_driver"

unsigned long long parameter = 0;
static struct dentry *debugfs_dummy;

static ssize_t
dummy_parameter_write(struct file *filp, const char __user *ubuf,
                                size_t cnt, loff_t *ppos)
{
	unsigned long long value;
	size_t err;

	err = kstrtoull_from_user(ubuf, cnt, 10, &value);
	if (err)
		return err;

	handle_dummy_write(value);

	parameter = value;

	*ppos += cnt;
	return cnt;
}

static int dummy_parameter_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%llu\n", parameter);
        return 0;
}

static int dummy_parameter_open(struct inode *inode, struct file *filp)
{
	int retval;

	retval = single_open(filp, dummy_parameter_show, inode->i_private);
	if (retval)
		printk("Error opening dummy driver\n");
	else
		handle_dummy_open();

	return retval;
}

static int dummy_parameter_release(struct inode *inode, struct file *file)
{
	int retval;

	retval = single_release(inode, file);
	if (retval)
		printk("Error relasing dummy driver\n");
	else
		handle_dummy_close();

	return retval;
}

static const struct file_operations dummy_parameter_fops = {
        .open           = dummy_parameter_open,
        .write          = dummy_parameter_write,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = dummy_parameter_release,
};


static int __init dummy_driver_init(void)
{
	static struct dentry *tmp;

	printk(KERN_INFO "Initializing " MODULE_NAME);

	debugfs_dummy = debugfs_create_dir("dummy_driver", NULL);
	if (!debugfs_dummy)
		goto out;

	tmp = debugfs_create_file("parameter", 0644, debugfs_dummy, NULL, &dummy_parameter_fops);
	if (!tmp)
		goto out;

	return 0;
out:
	printk(KERN_ERR "Error Initializing " MODULE_NAME);
	if (debugfs_dummy) {
		debugfs_remove(debugfs_dummy);
		debugfs_dummy = NULL;
	}
	return -EINVAL;
}

static void __exit dummy_driver_exit(void)
{
	debugfs_remove(debugfs_dummy);
	return;
}

module_init(dummy_driver_init);
module_exit(dummy_driver_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Daniel Bristot de Oliveira");
MODULE_DESCRIPTION("Why so dummy?");
