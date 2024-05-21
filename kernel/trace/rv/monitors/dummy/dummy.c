// SPDX-License-Identifier: GPL-2.0
#include <linux/ftrace.h>
#include <linux/tracepoint.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/rv.h>
#include <rv/instrumentation.h>
#include <rv/da_monitor.h>

#define MODULE_NAME "dummy"

#include <rv/dummy_monitor.h>
#include <trace/events/rv.h>

#include "dummy.h"

#define MAX_VALUE 100

static struct rv_monitor rv_dummy;
DECLARE_DA_MON_GLOBAL(dummy, unsigned char);

void handle_dummy_close(void)
{
	da_handle_event_dummy(dummy_close_dummy);
}

void handle_dummy_open(void)
{
	da_handle_start_run_event_dummy(dummy_open_dummy);
}

void handle_dummy_write(unsigned long long value)
{
	if (value < MAX_VALUE)
		da_handle_event_dummy(dummy_write_dummy);
	else
		da_handle_event_dummy(dummy_invalid_dummy);
}

static int enable_dummy(void)
{
	int retval;

	retval = da_monitor_init_dummy();
	if (retval)
		return retval;

	return 0;
}

static void disable_dummy(void)
{
	rv_dummy.enabled = 0;
	da_monitor_destroy_dummy();
}

/*
 * This is the monitor register section.
 */
static struct rv_monitor rv_dummy = {
	.name = "dummy",
	.description = "auto-generated dummy",
	.enable = enable_dummy,
	.disable = disable_dummy,
	.reset = da_monitor_reset_all_dummy,
	.enabled = 0,
};

static int __init register_dummy(void)
{
	rv_register_monitor(&rv_dummy);
	return 0;
}

static void __exit unregister_dummy(void)
{
	rv_unregister_monitor(&rv_dummy);
}

module_init(register_dummy);
module_exit(unregister_dummy);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dot2k: auto-generated");
MODULE_DESCRIPTION("dummy");
