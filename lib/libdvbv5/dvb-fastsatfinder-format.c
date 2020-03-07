/*
 * Copyright (c) 2011-2012 - Mauro Carvalho Chehab
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation version 2.1 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * Or, point your browser to http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libdvbv5/dvb-file.h>
#include <libdvbv5/dvb-v5-std.h>

#define PTABLE(a) .table = a, .size=ARRAY_SIZE(a)

/*
 * FastSatFinder *.ini format for DVB-S, DVB-S2
 */
static const char *fsf_parse_modulation[] = {
	[APSK_16] =  "16APSK",
	[APSK_32] =  "32APSK",
	[DQPSK] =    "DQPSK",
	[PSK_8] =    "8PSK",
	[QAM_AUTO] = "AUTO",
	[QPSK] =     "QPSK",
	[VSB_8] =    "8VSB",
	[VSB_16] =   "16VSB",
};

static const char *fsf_parse_code_rate[12] = {
	[FEC_1_2] =  "12",
	[FEC_2_3] =  "23",
	[FEC_3_4] =  "34",
	[FEC_3_5] =  "35",
	[FEC_4_5] =  "45",
	[FEC_5_6] =  "56",
	[FEC_6_7] =  "67",
	[FEC_7_8] =  "78",
	[FEC_8_9] =  "89",
	[FEC_9_10] = "910",
	[FEC_AUTO] = "AUTO",
	[FEC_NONE] = "NONE",
};

static const char *fsf_parse_polarization[] = {
	[POLARIZATION_OFF] = "-",
	[POLARIZATION_H] = "H",
	[POLARIZATION_V] = "V",
	[POLARIZATION_L] = "L",
	[POLARIZATION_R] = "R",
};

static const char *fsf_parse_rolloff[] = {
	[ROLLOFF_20] = "20",
	[ROLLOFF_25] = "25",
	[ROLLOFF_35] = "35",
	[ROLLOFF_AUTO] = "AUTO",
};

static const struct dvb_parse_table sys_atsc_table[] = {
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_MODULATION, PTABLE(fsf_parse_modulation) },
};

static const struct dvb_parse_table sys_dvbc_table[] = {
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_SYMBOL_RATE, NULL, 0 },
	{ DTV_INNER_FEC, PTABLE(fsf_parse_code_rate) },
	{ DTV_MODULATION, PTABLE(fsf_parse_modulation) },
};

/* Note: On DVB-S, frequency is divided by 1000 */
static const struct dvb_parse_table sys_dvbs_table[] = {
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_POLARIZATION, PTABLE(fsf_parse_polarization) },
	{ DTV_SYMBOL_RATE, NULL, 0 },
	{ DTV_INNER_FEC, PTABLE(fsf_parse_code_rate) },
};

static const struct dvb_parse_table sys_dvbs2_table[] = {
	{ DTV_FREQUENCY, NULL, 0 },
	{ DTV_POLARIZATION, PTABLE(fsf_parse_polarization) },
	{ DTV_SYMBOL_RATE, NULL, 0 },
	{ DTV_INNER_FEC, PTABLE(fsf_parse_code_rate) },
	{ DTV_ROLLOFF, PTABLE(fsf_parse_rolloff) },
	{ DTV_MODULATION, PTABLE(fsf_parse_modulation) },
	{ DTV_STREAM_ID, NULL, 0, 0, 1, 0 },
	{ DTV_PLS_CODE, NULL, 0, 0, 1, -1 },
	{ DTV_PLS_MODE, NULL, 0, 0, 1, -1 },
};

const struct dvb_parse_file channel_file_format = {
	.has_delsys_id = 1,
	.delimiter = " \n\t",
	.formats = {
	 {
			.id		= "S",
			.delsys		= SYS_DVBS,
			PTABLE(sys_dvbs_table),
		}, {
			.id		= "S2",
			.delsys		= SYS_DVBS2,
			PTABLE(sys_dvbs2_table),
		}, {
			NULL, 0, NULL, 0,
		}
	}
};
