/*
 * This file is part of the sigrok-cli project.
 *
 * Copyright (C) 2013 Bert Vermeulen <bert@biot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sigrok-cli.h"
#include <glib.h>

gboolean opt_version = FALSE;
gint opt_loglevel = SR_LOG_WARN; /* Show errors+warnings by default. */
gboolean opt_scan_devs = FALSE;
gboolean opt_wait_trigger = FALSE;
gchar *opt_input_file = NULL;
gchar *opt_output_file = NULL;
gchar *opt_drv = NULL;
gchar *opt_config = NULL;
gchar *opt_channels = NULL;
gchar *opt_channel_group = NULL;
gchar *opt_triggers = NULL;
gchar *opt_pds = NULL;
#ifdef HAVE_SRD
gchar *opt_pd_stack = NULL;
gchar *opt_pd_annotations = NULL;
gchar *opt_pd_meta = NULL;
gchar *opt_pd_binary = NULL;
#endif
gchar *opt_input_format = NULL;
gchar *opt_output_format = NULL;
gchar *opt_show = NULL;
gchar *opt_time = NULL;
gchar *opt_samples = NULL;
gchar *opt_frames = NULL;
gchar *opt_continuous = NULL;
gchar *opt_set = NULL;

static const GOptionEntry optargs[] = {
	{"version", 'V', 0, G_OPTION_ARG_NONE, &opt_version,
			"Show version and support list", NULL},
	{"loglevel", 'l', 0, G_OPTION_ARG_INT, &opt_loglevel,
			"Set loglevel (5 is most verbose)", NULL},
	{"driver", 'd', 0, G_OPTION_ARG_STRING, &opt_drv,
			"The driver to use", NULL},
	{"config", 'c', 0, G_OPTION_ARG_STRING, &opt_config,
			"Specify device configuration options", NULL},
	{"input-file", 'i', 0, G_OPTION_ARG_FILENAME, &opt_input_file,
			"Load input from file", NULL},
	{"input-format", 'I', 0, G_OPTION_ARG_STRING, &opt_input_format,
			"Input format", NULL},
	{"output-file", 'o', 0, G_OPTION_ARG_FILENAME, &opt_output_file,
			"Save output to file", NULL},
	{"output-format", 'O', 0, G_OPTION_ARG_STRING, &opt_output_format,
			"Output format", NULL},
	{"channels", 'C', 0, G_OPTION_ARG_STRING, &opt_channels,
			"Channels to use", NULL},
	{"channel-group", 'g', 0, G_OPTION_ARG_STRING, &opt_channel_group,
			"Channel groups", NULL},
	{"triggers", 't', 0, G_OPTION_ARG_STRING, &opt_triggers,
			"Trigger configuration", NULL},
	{"wait-trigger", 'w', 0, G_OPTION_ARG_NONE, &opt_wait_trigger,
			"Wait for trigger", NULL},
#ifdef HAVE_SRD
	{"protocol-decoders", 'P', 0, G_OPTION_ARG_STRING, &opt_pds,
			"Protocol decoders to run", NULL},
	{"protocol-decoder-stack", 'S', 0, G_OPTION_ARG_STRING, &opt_pd_stack,
			"Protocol decoder stack", NULL},
	{"protocol-decoder-annotations", 'A', 0, G_OPTION_ARG_STRING, &opt_pd_annotations,
			"Protocol decoder annotation(s) to show", NULL},
	{"protocol-decoder-meta", 'M', 0, G_OPTION_ARG_STRING, &opt_pd_meta,
			"Protocol decoder meta output to show", NULL},
	{"protocol-decoder-binary", 'B', 0, G_OPTION_ARG_STRING, &opt_pd_binary,
			"Protocol decoder binary output to show", NULL},
#endif
	{"scan", 0, 0, G_OPTION_ARG_NONE, &opt_scan_devs,
			"Scan for devices", NULL},
	{"show", 0, 0, G_OPTION_ARG_NONE, &opt_show,
			"Show device detail", NULL},
	{"time", 0, 0, G_OPTION_ARG_STRING, &opt_time,
			"How long to sample (ms)", NULL},
	{"samples", 0, 0, G_OPTION_ARG_STRING, &opt_samples,
			"Number of samples to acquire", NULL},
	{"frames", 0, 0, G_OPTION_ARG_STRING, &opt_frames,
			"Number of frames to acquire", NULL},
	{"continuous", 0, 0, G_OPTION_ARG_NONE, &opt_continuous,
			"Sample continuously", NULL},
	{"set", 0, 0, G_OPTION_ARG_NONE, &opt_set, "Set device options only", NULL},
	{NULL, 0, 0, 0, NULL, NULL, NULL}
};

/* Parses the command line and sets all the 'opt_...' variables.
   Returns zero on success, non-zero otherwise. */
int parse_options(int argc, char **argv)
{
	GError *error = NULL;
	GOptionContext *context = g_option_context_new(NULL);
	int ret = 1;

	g_option_context_add_main_entries(context, optargs, NULL);

	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_critical("%s", error->message);
		goto done;
	}

	ret = 0;

done:
	g_option_context_free(context);

	return ret;
}

void show_help(void)
{
	GOptionContext *context = g_option_context_new(NULL);
	g_option_context_add_main_entries(context, optargs, NULL);

	char *help = g_option_context_get_help(context, TRUE, NULL);
	printf("%s", help);
	g_free(help);

	g_option_context_free(context);
}