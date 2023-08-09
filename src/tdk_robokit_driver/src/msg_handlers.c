/*
*
* Copyright (c) 2014-2022 InvenSense Inc.  All rights reserved.
*
* INVENSENSE, INC. ("LICENSOR") SOFTWARE LICENSE AGREEMENT ("Agreement")
* BY DOWNLOADING, INSTALLING, COPYING OR OTHERWISE USING THE ENCLOSED SOFTWARE AND OTHER AVAILABLE MATERIALS ("LICENSED
* MATERIALS"), YOU ("LICENSEE") AGREE TO BE BOUND BY THE FOLLOWING TERMS AND CONDITIONS OF THIS AGREEMENT.  IF LICENSEE DOES NOT
* AGREE TO THE TERMS AND CONDITION OF THIS AGREEMENT, THEN DO NOT DOWNLOAD, INSTALL, COPY OR OTHERWISE USE THE ENCLOSED SOFTWARE
* AND MATERIALS.
*
* The Licensed Materials may include open source and proprietary software in both source code ("Source Code") and object code
* ("Object Code") versions, documentation and other materials.  Except as expressly indicated herein, all terms and conditions of
* this Agreement apply to all of the Licensed Materials.  In the event that any file contained within the Licensed Materials
* incorporates a different software license, such other license shall apply to such file.
* Except as expressly set forth herein, LICENSOR owns all of the Licensed Materials and makes them available to Licensee only
* under the terms and conditions set forth in this Agreement.
*
* 1. License:  Subject to the terms of this Agreement, LICENSOR hereby grants to Licensee a royalty-free, non-exclusive license to
* possess and to use the Licensed Materials in a secure location in accordance with the applicable terms herein.  Licensee may
* make back-up copies and install and use multiple copies of the Licensed Materials on a shared computer or concurrently on
* different computers, solely for Licensee's use within Licensee's Enterprise. "Enterprise" shall mean individual use by Licensee
* or any legal entity (such as a corporation or university) and the subsidiaries it owns by more than 50 percent.  The following
* terms apply to the specified type of Licensed Material:
*
* 1.1 Source Code:  Licensee shall have the right to use, copy, modify and prepare and have prepared derivative works of the
* Source Code for internal development and testing purposes only.  Licensee shall own any modification it makes directly to the
* Source Code that optimizes quality or performance with Licensee's product ("Modification(s)") subject to LICENSOR's ownership of
* the underlying Source Code and all intellectual property rights therein.
*
* 1.2 Object Code:  Licensee may distribute the Object Code (in object code form only) and compiled Source Code (in object code
* form only) with Modifications solely for execution or operation with applicable LICENSOR products for which Source Code and
* Object Code was designed and as incorporated in Licensee's software products. Licensee agrees not to disassemble, decompile or
* reverse engineer the Object Code.
*
* 2. Notices:  Licensee agrees to comply with and reproduce any and all copyright and other attribution notices/instructions of
* LICENSOR as included in the Licensed Materials in connection with Licensee's distribution rights pursuant to the Agreement.
*
* 3. Subcontractors:  Licensee may engage subcontractors to exercise Licensee's rights hereunder. Licensee is responsible to
* ensure that Licensee subcontractors comply with the terms and conditions of this Agreement.  Any act by a subcontractor that
* would be a breach of this Agreement by Licensee if Licensee performed the act will be deemed a breach of this Agreement by
* Licensee.
*
* 4. License Grant Back: Licensee hereby grants to LICENSOR and its Affiliates an exclusive, worldwide, irrevocable, perpetual,
* sublicenseable (through multiple tiers of sublicensees), royalty-free and fully paid-up right and license to the Modification(s)
* (in object code form) created by or on behalf of Licensee so that LICENSOR may copy, modify, create derivatives works thereof,
* to use, have used, import, make, have made, sell, offer to sell, sublicense (through multiple tiers of sublicensees), distribute
* (through multiple tiers of distributors) such derivative work(s) on a stand-alone basis or as incorporated into the Licensed
* Materials or other related technologies.  For the sake of clarity, LICENSOR is not prohibited or otherwise restricted from
* independently developing new features or functionality with respect to the Licensed Materials.
*
* 5. No Other License: No rights or licenses with respect to any proprietary information or patent, copyright, trade secret or
* other intellectual property right owned or controlled by LICENSOR are granted by LICENSOR to Licensee under this Agreement,
* expressly or by implication, except as expressly provided in this Agreement.
* 6. Intellectual Property Ownership: Except as expressly licensed to Licensee under this Agreement, LICENSOR reserves all right,
* title and interest, including but not limited to all intellectual property rights, in and to the Licensed Materials and any
* derivative work(s) made thereto.
*
* 7. Term of Agreement:  This Agreement is effective until (i) automatically terminated if Licensee fails to comply with any of
* the terms and conditions of this Agreement; or (ii) terminated by LICENSOR.  LICENSOR may terminate this Agreement (and with it,
* all of Licensee's right to the Licensed Materials) immediately upon written notice (which may include email) to Licensee, with
* or without cause; provided however, that sublicenses of Derivatives, to the extent validly granted to its customers prior to
* termination of this Agreement, shall survive such termination.
*
* 8. Confidential Information. "Confidential Information" means (i) the Licensed Materials; (ii) the structure, sequence and
* organization of the Licensed Materials and the concepts, methods of operations and ideas disclosed therein; and (iii) any trade
* secrets of LICENSOR or its affiliates or its or their suppliers relating to the Licensed Materials. Licensee will not disclose
* any Confidential Information to any third party (except subcontractors, as permitted herein) or use Confidential Information
* except as expressly permitted in this Agreement.  Licensee agrees to take all reasonable measures to protect Confidential
* Information and prevent its unauthorized disclosure, including measures at least as stringent as those measures Licensee takes
* to protect Licensee's own most sensitive confidential information.  Licensee agrees to restrict access to Confidential
* Information to Licensee employees and subcontractors who are under obligations to protect Confidential Information in accordance
* with this Agreement and who have a "need to know" the Confidential Information to exercise Licensee license rights in this
* Agreement.  All Confidential Information, and any documents and other tangible objects containing or representing Confidential
* Information, and all copies of Confidential Information, are and will remain the exclusive property of LICENSOR.
*
* 9. Defensive Suspension: If Licensee commences or participates in any legal proceeding against LICENSOR, then LICENSOR may, in
* its sole discretion, suspend or terminate all license grants and any other rights provided under this Agreement during the
* pendency of such legal proceedings.
*
* 10. No Support:  LICENSOR has no obligation to support or to continue providing or updating any of the Licensed Materials.
*
* 11. No Warranty:  THE LICENSED MATERIALS PROVIDED BY LICENSOR TO LICENSEE HEREUNDER ARE PROVIDED "AS IS."  LICENSOR DISCLAIMS
* ALL WARRANTIES, EXPRESS, IMPLIED OR STATUTORY, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*
* 12. Limitation of Liability: LICENSOR SHALL NOT BE LIABLE TO LICENSEE, LICENSEE'S CUSTOMERS, OR ANY OTHER PERSON OR ENTITY
* CLAIMING THROUGH OR UNDER LICENSEE FOR ANY LOSS OF PROFITS, INCOME, SAVINGS, OR ANY OTHER CONSEQUENTIAL, INCIDENTAL, SPECIAL,
* PUNITIVE, DIRECT OR INDIRECT DAMAGES (WHETHER IN AN ACTION IN CONTRACT, TORT OR BASED ON A WARRANTY), EVEN IF LICENSOR HAS BEEN
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING ANY FAILURE OF THE ESSENTIAL PURPOSE
* OF ANY LIMITED REMEDY.  IN NO EVENT SHALL LICENSOR'S AGGREGATE LIABILITY TO LICENSEE OR ANY OTHER PERSON OR ENTITY CLAIMING
* THROUGH OR UNDER LICENSEE EXCEED THE AMOUNT OF MONEY ACTUALLY PAID BY LICENSEE TO LICENSOR FOR THE LICENSED MATERIALS.
*
* 13. Applicable Law and Jurisdiction: This Agreement shall be deemed to have been made in, and shall be construed pursuant to,
* the laws of the State of California. The state and/or federal courts residing in Santa Clara County, California shall have
* exclusive jurisdiction over any dispute or claim arising out of this Agreement. The United Nations Convention on Contracts for
* the International Sale of Goods is specifically disclaimed.
*
* 14. Feedback: Licensee may, but is not obligated to, provide to LICENSOR any suggestions, comments and feedback regarding the
* Licensed Materials that are delivered by LICENSOR to Licensee under this Agreement (collectively, "Licensee Feedback").
* LICENSOR may use and include any Licensee Feedback that Licensee voluntarily provides to improve the Licensed Materials or other
* related LICENSOR technologies.  Accordingly, if Licensee provides Licensee Feedback, Licensee grants LICENSOR and its licensees
* a perpetual, irrevocable, worldwide, royalty-free, fully paid-up license grant to freely use, have used, sell, modify,
* reproduce, transmit, license, sublicense (through multiple tiers of sublicensees), distribute (through multiple tiers of
* distributors), and otherwise commercialize the Licensee Feedback in the Licensed Materials or other related technologies.
*
* 15. RESTRICTED RIGHTS NOTICE: Licensed Materials has been developed entirely at private expense and is commercial computer
* software provided with RESTRICTED RIGHTS. Use, duplication or disclosure by the U.S. Government or a U.S. Government
* subcontractor is subject to the restrictions set forth in the license agreement under which Licensed Materials was obtained
* pursuant to DFARS 227.7202-3(a) or as set forth in subparagraphs (c)(1) and (2) of the Commercial Computer Software - Restricted
* Rights clause at FAR 52.227-19, as applicable.
*
* 16. Miscellaneous: If any provision of this Agreement is inconsistent with, or cannot be fully enforced under, the law, such
* provision will be construed as limited to the extent necessary to be consistent with and fully enforceable under the law. This
* Agreement is the final, complete and exclusive agreement between the parties relating to the subject matter hereof, and
* supersedes all prior or contemporaneous understandings and agreements relating to such subject matter, whether oral or written.
* This Agreement is solely between LICENSOR and Licensee.  There are no third party beneficiaries, express or implied, to this
* Agreement. This Agreement may only be modified in writing signed by an authorized officer of LICENSOR.  Licensee agrees that it
* will not ship, transfer or export the Licensed Materials into any country, or use the Licensed Materials in any manner,
* prohibited by the United States Bureau of Industry and Security or any export laws, restrictions or regulations. This Agreement,
* and Licensee's rights and obligations herein, may not be assigned, subcontracted, delegated, or otherwise transferred by
* Licensee without LICENSOR's prior written consent, and any attempted assignment, subcontract, delegation, or transfer in
* violation of the foregoing will be null and void.   The terms of this Agreement shall be binding upon assignees.
*
*
*/


#include <stdio.h>   /* Standard input/output definitions */
#include <stdint.h>  /* standard integer types */
#include <string.h>  /* String function definitions */
#include <stdbool.h>

#include "messages.h"
#include "serial_interface.h"
#include "sensor_node.h"


#define HEADER_SIZE  (unsigned)2
#define HEADER_BYTE0 ((uint8_t)0x55)
#define HEADER_BYTE1 ((uint8_t)0xAA)
#define FOOTER_SIZE  (unsigned)2
#define FOOTER_BYTE0 ((uint8_t)0xBE)
#define FOOTER_BYTE1 ((uint8_t)0xEF)
#define PAYLOAD_SIZE  (unsigned)2

#define FRAME_MIN_SIZE (HEADER_SIZE + FOOTER_SIZE + PAYLOAD_SIZE)
#define IS_FRAME_SIZE_GOOD(frame_size, min_payload_size) ((frame_size < min_payload_size) ? true : false )

static const char *PROTOCOL_TAG = "PROTOCOL_TASK";
static cmd_param_t cmd_payload = {0};

uint8_t prot_input_buf[128];
uint16_t g_output_size = 128;

/** @brief Commend handler descriptor. Hander + associated ID.
 */
struct CommandHandler {
	enum PacketType cmd;
	int (*handler)(const uint8_t * payload, unsigned frameSize);
};

/** @brief Descriptor of one buffer of the ping pong buffer.
 */
struct BufferDescriptor {
	uint8_t * data;
	uint16_t max_size;
	uint16_t size;
};

/** @brief The four buffers and active idx.
 */
static struct ProtocolPingPongBuffers {
	struct BufferDescriptor input_buffer;
} protbuf = {0};

int handle_temp_sensor(int enable);
int handle_mag_sensor(int enable);
int handle_imu_sensor(int enable);
int handle_pres_sensor(int enable);
int handle_asic_sensor(int enable);
int handle_audio_sensor(int enable);

static inline void protbuf_reset_output_buffer_par(struct BufferDescriptor * output_buffer)
{
	output_buffer->data[0] = HEADER_BYTE0;
	output_buffer->data[1] = HEADER_BYTE1;
	output_buffer->data[2] = 0;
	output_buffer->data[3] = 0;
	output_buffer->size = 4;
}

/** @brief Packet descriptor.
 */
struct Pkt {
	uint8_t * buf;
	unsigned idx;
	unsigned maxSize;
	bool overflow;
};


static void protpkt_prepare_packet(struct Pkt * pkt, enum PacketType pktType)
{
	struct BufferDescriptor * output_buffer = &(protbuf.input_buffer);

	const int remSize = output_buffer->max_size - output_buffer->size - FOOTER_SIZE - 1;
	if (g_output_size > remSize)
		g_output_size = remSize;

	if(remSize <= 0) {
		pkt->maxSize = 0;
		pkt->idx = 0;
	}
	else {
		/* add packet type */
		output_buffer->data[output_buffer->size] = (uint8_t)pktType;

		pkt->buf = &output_buffer->data[output_buffer->size+1];
		pkt->idx = 0;
		pkt->maxSize = remSize;
		pkt->overflow = false;
	}
}

static bool protpkt_finalize_packet(struct Pkt * pkt)
{
	if(pkt->overflow) {
		return false;
	}
	else {
		struct BufferDescriptor * output_buffer = &(protbuf.input_buffer);
		const unsigned packetSize = pkt->idx + 1;
		unsigned frameSize = (((unsigned)output_buffer->data[3] << 8) | output_buffer->data[2]) + packetSize;

		/* update frame size */
		output_buffer->data[2] = (uint8_t)((frameSize) & 0xFF);
		output_buffer->data[3] = (uint8_t)(((frameSize) & 0xFF00) >> 8);

		/* update buffer index */
		output_buffer->size += packetSize;
		return true;
	}
}

static inline void protpkt_put_byte(struct Pkt * pkt, uint8_t byte)
{
	if((pkt->idx < pkt->maxSize) && (pkt->buf != NULL)) {
		pkt->buf[pkt->idx] = byte;
		pkt->idx++;
	}
	else {
		pkt->overflow = true;
	}
}

static inline void protpkt_put_buffer(struct Pkt * pkt, const void * data, unsigned len)
{
	if(len) {
		if((pkt->idx + len <= pkt->maxSize) && (pkt->buf != NULL)) {
			memcpy(&pkt->buf[pkt->idx], data, len);
			pkt->idx += len;
		}
		else {
			pkt->overflow = true;
		}
	}
}

static void protcore_finalize_output_buffer_par(struct BufferDescriptor * output_buffer)
{
	output_buffer->data[output_buffer->size]   = FOOTER_BYTE0;
	output_buffer->data[output_buffer->size+1] = FOOTER_BYTE1;
	output_buffer->size += 2;
}

static void protcore_send_output_buffer(uint32_t length)
{
	struct BufferDescriptor * output_buffer = &(protbuf.input_buffer);
	uint32_t total_len = length + 4 + 2 ;  /*2 bytes of header and 2 bytes of footer and 2 bytes of length*/

	protcore_finalize_output_buffer_par(output_buffer);

	/* only if buffer actually contains something */
	if (output_buffer->size > FRAME_MIN_SIZE) {
		sendData(output_buffer->data,total_len);
	}
	protbuf_reset_output_buffer_par(output_buffer);
}


static int protcmd_get_protocol_version_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_soft_reset_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_reset_sensor_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_reset_pdalgo_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_enable_pdalgo_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_enable_iqstream_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_start_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	/**/
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1  ;

	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_START);
	protpkt_finalize_packet(&pkt);
	protcore_send_output_buffer(len);

	return 0;
}

static int protcmd_stop_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	/**/
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1  ;

	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_STOP);
	protpkt_finalize_packet(&pkt);
	protcore_send_output_buffer(len);

	return 0;
}

static int protcmd_enable_asic_data_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	// printf("protcmd_enable_asic_cmd_handler framesize: %d\n", frameSize);
	return 0;
}

static int protcmd_enable_imu_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	printf("protcmd_enable_imu_cmd_handler framesize: %d\n", frameSize);
	return 0;
}

static int protcmd_enable_mag_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	printf("protcmd_enable_mag_cmd_handler framesize: %d\n", frameSize);
	return 0;
}

static int protcmd_enable_pres_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	return 0;
}

static int protcmd_enable_temp_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
   printf("protcmd_enable_temp_cmd_handler framesize: %d\n", frameSize);
   return 0;
}

static int protcmd_enable_audio_cmd_handler(const uint8_t * payload, unsigned frameSize)
{
	return 0;
}


static int protcmd_enable_floor_algo_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_enable_cliff_algo_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_enable_robo_start_stop_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_ctrl_motor_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_sensor_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_sensor_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_sensor_param_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_version_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_sensors_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_algo_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_status_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_floor_algo_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_cliff_algo_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_get_sensors_trigger_mode_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_algo_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_odr_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_range_mm_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_sample_range_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_pusle_length_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_low_gain_rxlen_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_floor_algo_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_enable_rx_pre_trigger_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_cliff_algo_config_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_set_debug_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_async_grv_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   grv_data_cmd_handler(payload);
   return 0;
}

static int protcmd_async_robovac_stop_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_async_audio_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   audio_data_cmd_handler(payload, frameSize);
   return 0;
}

static int protcmd_async_temp_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   temp_data_cmd_handler(payload);
   return 0;
}

static int protcmd_async_mag_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   mag_data_cmd_handler(payload);
   return 0;
}

static int protcmd_async_pres_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   pres_data_cmd_handler(payload);
   return 0;
}

static int protcmd_async_cliff_algo_out_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_async_floor_algo_out_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_async_imu_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   imu_data_cmd_handler(payload);
   return 0;
}

static int protcmd_async_ch_data_cmd_handler (const uint8_t * payload, unsigned frameSize)
{  
   chirp_data_cmd_handler(payload);
   return 0;
}

static int protcmd_async_pd_out_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_async_status_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_async_debug_message_cmd_handler (const uint8_t * payload, unsigned frameSize)
{
   return 0;
}

static int protcmd_reset_device_cmd_handler()
{
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1  ;

	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_SOFT_RESET);
	protpkt_finalize_packet(&pkt);
	protcore_send_output_buffer(len);
	return 0;
}

int handle_temp_sensor(int enable){
	printf("Enter handle_temp_sensor\n");
	cmd_param_t cmd_pyload;

	cmd_pyload.enable_disable.enable_flag = enable;
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1;

	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_ENABLE_TEMP);
	protpkt_put_byte(&pkt, cmd_pyload.enable_disable.enable_flag);
	protpkt_finalize_packet(&pkt);
	len = (pkt.idx) + 1  ;
	protcore_send_output_buffer(len);
	printf("Exit handle_temp_sensor\n");
	return 0;
}

int handle_imu_sensor(int enable){
	printf("Enter handle_imu_sensor\n");
	cmd_param_t cmd_pyload;
	cmd_pyload.enable_disable.enable_flag = enable;
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1;

	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_ENABLE_IMU);
	protpkt_put_byte(&pkt, cmd_pyload.enable_disable.enable_flag);
	protpkt_finalize_packet(&pkt);
	len = (pkt.idx) + 1  ;
	protcore_send_output_buffer(len);
	printf("Exit handle_imu_sensor\n");

	return 0;
}

int handle_mag_sensor(int enable){
	printf("Enter handle_mag_sensor\n");
	cmd_param_t cmd_pyload;

	cmd_pyload.enable_disable.enable_flag = enable;
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1;

	// printf("protcmd_enable_mag_cmd_handler--> %d\n", cmd_pyload.enable_disable.enable_flag);
	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_ENABLE_MAG);
	protpkt_put_byte(&pkt, cmd_pyload.enable_disable.enable_flag);
	protpkt_finalize_packet(&pkt);
	len = (pkt.idx) + 1  ;
	protcore_send_output_buffer(len);
	printf("Exit handle_mag_sensor\n");
	return 0;
}

int handle_pres_sensor(int enable){
	printf("Enter handle_pres_sensor\n");
	cmd_param_t cmd_pyload;
	cmd_pyload.enable_disable.enable_flag = enable;
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1;

	// printf("protcmd_enable_pres_cmd_handler-->%d\n", cmd_pyload.enable_disable.enable_flag);
	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_ENABLE_PRES);
	protpkt_put_byte(&pkt, cmd_pyload.enable_disable.enable_flag);
	protpkt_finalize_packet(&pkt);
	len = (pkt.idx) + 1  ;
	protcore_send_output_buffer(len);
	printf("Exit handle_pres_sensor\n");
	return 0;
}

int handle_asic_sensor(int enable){
	printf("Enter handle_asic_sensor\n");
	cmd_param_t cmd_pyload;
	cmd_pyload.enable_disable.enable_flag = enable;
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1  ;

	// printf("protcmd_enable_aisc_cmd_handler-->%d\n", cmd_pyload.enable_disable.enable_flag);
	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_ENABLE_ASIC_DATA);
	protpkt_put_byte(&pkt, cmd_pyload.enable_disable.enable_flag);
	protpkt_finalize_packet(&pkt);
	len = (pkt.idx) + 1  ;
	protcore_send_output_buffer(len);
	printf("Exit handle_asic_sensor\n");
	return 0;
}

int handle_audio_sensor(int enable){
	printf("Enter handle_audio_sensor\n");
	cmd_param_t cmd_pyload;
	cmd_pyload.enable_disable.enable_flag = enable;
	struct Pkt pkt = {0};
	uint32_t len = (pkt.idx) + 1  ;

	// printf("protcmd_enable_audio_cmd_handler-->%d\n", cmd_pyload.enable_disable.enable_flag);
	protpkt_prepare_packet(&pkt, PKT_TYPE_CMD_ENABLE_AUDIO);
	protpkt_put_byte(&pkt, cmd_pyload.enable_disable.enable_flag);
	protpkt_finalize_packet(&pkt);
	len = (pkt.idx) + 1  ;
	protcore_send_output_buffer(len);
	printf("Exit handle_audio_sensor\n");
	return 0;
}

static const struct CommandHandler protcmd_handler_array[] = {	
	{ PKT_TYPE_RESP_GET_PROTOCOL_VERSION,      protcmd_get_protocol_version_cmd_handler },
	{ PKT_TYPE_RESP_SOFT_RESET,                protcmd_soft_reset_cmd_handler },
	{ PKT_TYPE_RESP_RESET_SENSOR,              protcmd_reset_sensor_cmd_handler },
	{ PKT_TYPE_RESP_RESET_PDALGO,              protcmd_reset_pdalgo_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_PDALGO,             protcmd_enable_pdalgo_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_IQSTREAM,           protcmd_enable_iqstream_cmd_handler },
	{ PKT_TYPE_RESP_START,                     protcmd_start_cmd_handler },
	{ PKT_TYPE_RESP_STOP,                      protcmd_stop_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_ASIC_DATA,          protcmd_enable_asic_data_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_IMU,                protcmd_enable_imu_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_FLOOR_ALGO,         protcmd_enable_floor_algo_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_CLIFF_ALGO,         protcmd_enable_cliff_algo_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_MAG,                protcmd_enable_mag_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_PRES,               protcmd_enable_pres_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_TEMP ,              protcmd_enable_temp_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_AUDIO,              protcmd_enable_audio_cmd_handler },
	{ PKT_TYPE_RESP_ENABLE_ROBO_START_STOP,    protcmd_enable_robo_start_stop_cmd_handler },
	{ PKT_TYPE_RESP_CTRL_MOTOR,                protcmd_ctrl_motor_cmd_handler },
	{ PKT_TYPE_RESP_SET_SENSOR_CONFIG,         protcmd_set_sensor_config_cmd_handler },
	{ PKT_TYPE_RESP_GET_SENSOR_CONFIG ,        protcmd_get_sensor_config_cmd_handler },
	{ PKT_TYPE_RESP_GET_SENSOR_PARAM,          protcmd_get_sensor_param_cmd_handler },
	{ PKT_TYPE_RESP_GET_VERSION,               protcmd_get_version_cmd_handler },
	{ PKT_TYPE_RESP_GET_SENSORS,               protcmd_get_sensors_cmd_handler },
	{ PKT_TYPE_RESP_GET_ALGO_CONFIG,           protcmd_get_algo_config_cmd_handler },
	{ PKT_TYPE_RESP_GET_STATUS,                protcmd_get_status_cmd_handler },
	{ PKT_TYPE_RESP_GET_FLOOR_ALGO_CONFIG,     protcmd_get_floor_algo_config_cmd_handler },
	{ PKT_TYPE_RESP_GET_CLIFF_ALGO_CONFIG,     protcmd_get_cliff_algo_config_cmd_handler },
	{ PKT_TYPE_RESP_GET_SENSORS_TRIGGER_MODE,  protcmd_get_sensors_trigger_mode_cmd_handler },
	{ PKT_TYPE_RESP_SET_ALGO_CONFIG,           protcmd_set_algo_config_cmd_handler },
	{ PKT_TYPE_RESP_SET_ODR,                   protcmd_set_odr_cmd_handler },
	{ PKT_TYPE_RESP_SET_RANGE_MM,              protcmd_set_range_mm_cmd_handler },
	{ PKT_TYPE_RESP_SET_SAMPLE_RANGE,          protcmd_set_sample_range_cmd_handler },
	{ PKT_TYPE_RESP_SET_PUSLE_LENGTH,          protcmd_set_pusle_length_cmd_handler },
	{ PKT_TYPE_RESP_SET_LOW_GAIN_RXLEN,        protcmd_set_low_gain_rxlen_cmd_handler },
	{ PKT_TYPE_RESP_SET_FLOOR_ALGO_CONFIG,     protcmd_set_floor_algo_config_cmd_handler },
	{ PKT_TYPE_RESP_SET_ENABLE_RX_PRE_TRIGGER, protcmd_set_enable_rx_pre_trigger_cmd_handler },
	{ PKT_TYPE_RESP_SET_CLIFF_ALGO_CONFIG,     protcmd_set_cliff_algo_config_cmd_handler },
	{ PKT_TYPE_RESP_SET_DEBUG,                 protcmd_set_debug_cmd_handler },
	{ PKT_TYPE_ASYNC_GRV_DATA,                 protcmd_async_grv_data_cmd_handler },
	{ PKT_TYPE_ASYNC_ROBOVAC_STOP,             protcmd_async_robovac_stop_cmd_handler },
	{ PKT_TYPE_ASYNC_AUDIO_DATA,               protcmd_async_audio_data_cmd_handler },
	{ PKT_TYPE_ASYNC_TEMP_DATA,                protcmd_async_temp_data_cmd_handler },
	{ PKT_TYPE_ASYNC_MAG_DATA,                 protcmd_async_mag_data_cmd_handler },
	{ PKT_TYPE_ASYNC_PRES_DATA,                protcmd_async_pres_data_cmd_handler },
	{ PKT_TYPE_ASYNC_CLIFF_ALGO_OUT,           protcmd_async_cliff_algo_out_cmd_handler },
	{ PKT_TYPE_ASYNC_FLOOR_ALGO_OUT,           protcmd_async_floor_algo_out_cmd_handler },
	{ PKT_TYPE_ASYNC_IMU_DATA,                 protcmd_async_imu_data_cmd_handler },
	{ PKT_TYPE_ASYNC_CH_DATA,                  protcmd_async_ch_data_cmd_handler },
	{ PKT_TYPE_ASYNC_PD_OUT,                   protcmd_async_pd_out_cmd_handler },
	{ PKT_TYPE_ASYNC_STATUS,                   protcmd_async_status_cmd_handler },
	{ PKT_TYPE_ASYNC_DEBUG_MESSAGE,            protcmd_async_debug_message_cmd_handler },
};

int protcore_decode_one_packet(const uint8_t * buffer, unsigned size)
{
  if(!size) 
  {
    return 0;
  }
  else {
    /* ensure input is an upstream command */
    if((buffer[0] & 0x80) != 0) 
    {
      /* find handler for this command */
      unsigned i;
      for(i = 0; i < sizeof(protcmd_handler_array)/sizeof(protcmd_handler_array[0]); ++i) 
      {
        if(protcmd_handler_array[i].cmd == (enum PacketType)buffer[0]) 
        {
          const int payload_len = protcmd_handler_array[i].handler(&buffer[1], size - 1);
          if(payload_len >= 0) 
          {
            // printf("len: %d, msg_id: %x\n",payload_len, buffer[0]);
            return payload_len + 1; /* account for CMD_ID byte */
          }
          else 
          {
            printf("PROTOCOL_ERROR Fail to decode command ID=0x%02x", buffer[0]);
            return -1;
          }
        }
      }
      
      /* no handler found */
      printf("PROTOCOL_ERROR No command handler for ID=0x%02x", buffer[0]);
      return -1;
    }
  }
}

void serial_protocol_init()
{
	memset(&protbuf, 0, sizeof(protbuf));

	protbuf.input_buffer.data = prot_input_buf;
	protbuf.input_buffer.size = 0;
	protbuf.input_buffer.max_size = sizeof(prot_input_buf);

	protbuf_reset_output_buffer_par(&(protbuf.input_buffer));
	protcmd_reset_device_cmd_handler();
}
