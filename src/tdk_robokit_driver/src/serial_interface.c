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
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <mqueue.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <linux/serial.h>
#include <asm/ioctls.h>

#include "messages.h"
#include "serial_interface.h"

// DEBUG
#if DEBUG
struct timeval tv;
unsigned long long microsecondsSinceEpoch;
#endif // Debug

#define HEADER_SIZE   ((unsigned)2)
#define HEADER_BYTE0  ((uint8_t)0x55)
#define HEADER_BYTE1  ((uint8_t)0xAA)
#define FOOTER_BYTE0  ((uint8_t)0xBE)
#define FOOTER_BYTE1  ((uint8_t)0xEF)
#define FOOTER_SIZE   ((unsigned)2)
#define PAYLOAD_SIZE  ((unsigned)2)

typedef enum {
   HDR1,
   HDR2,
   LEN1,
   LEN2,
   PL,
   FTR1,
   FTR2
} t_state;

void *proc_pl_func( void *ptr );
void *proc_serial_read_func(void *p);

static mqd_t mqdes;

/*
 * 'open_port()' - Open serial port.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int open_port(void)
{
   int fd; /* File descriptor for the port */ 
   struct termios tty;
   struct serial_struct ser_info; 

   fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);  /*TODO remove hardcoding of port name */
   if (fd == -1)
   {
      /* Could not open the port. */
      printf("open_port: Unable to open /dev/ttyUSB0 - ");
   }
   else
      fcntl(fd, F_SETFL, 0);

  int result = tcflush(fd, TCIOFLUSH);
  if (result)
  {
    printf("tcflush failed");
  }

   /* Get the current options for the port... */

   tcgetattr(fd, &tty);

   tty.c_cflag &= ~PARENB;  // Clear parity bit, disabling parity (most common)
   tty.c_cflag &= ~CSTOPB;  // Clear stop field, only one stop bit used in communication (most common)
   tty.c_cflag &= ~CSIZE;   // Clear all bits that set the data size 
   tty.c_cflag |= CS8;      // 8 bits per byte (most common)
   tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
   tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

   tty.c_lflag &= ~ICANON;
   tty.c_lflag &= ~ECHO;    // Disable echo
   tty.c_lflag &= ~ECHOE;   // Disable erasure
   tty.c_lflag &= ~ECHONL;  // Disable new-line echo
   tty.c_lflag &= ~ISIG;    // Disable interpretation of INTR, QUIT and SUSP
   tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
   tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
   
   tty.c_oflag &= ~(OPOST|ONLCR); // Disable NL to NL-CR conversion on output

   tty.c_cc[VTIME] = 1;    // Wait for up to 1/10 s (1 deciseconds), returning as soon as any data is received.
   tty.c_cc[VMIN] = 0;

   /* Set the baud rates to 1000000... */

   cfsetispeed(&tty, B1000000);
   cfsetospeed(&tty, B1000000);

   tcsetattr(fd, TCSANOW, &tty);


  // Set up low_latency flag to avoid delays from serial driver level
  if (0 != ioctl(fd, TIOCGSERIAL, &ser_info) < 0)
  {
    printf("Error getting serial info");
  }
  else
  {
    ser_info.flags |= ASYNC_LOW_LATENCY;
    if (ioctl(fd, TIOCSSERIAL, &ser_info) < 0) 
    {
      printf("Error setting low_latency flag");
    }
  }
  
  return (fd);
}

void parse_msg(uint8_t *data, uint16_t len)
{

  uint16_t i;
  static t_state state = HDR1;
  static uint16_t pl_len = 0;
  static uint16_t pl_ind = 0;
  static uint8_t  curr_pkt[512];   /* TODO remove the magic number */

//  printf("len: %d: \n",len);

  for ( i = 0; i < len; i++)
  {
    switch(state)
    {
      case HDR1:
           if( data[i] == HEADER_BYTE0 )
             state = HDR2;
           break;

      case HDR2:
           if( data[i] == HEADER_BYTE1 )
           {
             state = LEN1;
             pl_len = 0;
           }
           else 
           {
              /* report dropped bytes and set the state to starting state */
              printf("byte dropped; state: %d\n",state);
              state = HDR1;
           }
           break;

      case LEN1:
              pl_len = data[i];
              state  = LEN2;
           break;

      case LEN2:
              pl_len = (pl_len) + (data[i] << 8);
              state  = PL;
              pl_ind = 0;
           break;

      case PL:
             
             if( pl_ind < (pl_len - 1) )
             {
               curr_pkt[pl_ind++] = data[i];
             }
             else
             {
               curr_pkt[pl_ind++] = data[i];
               state = FTR1;
             }
           break;
      case FTR1:
           if(data[i] == FOOTER_BYTE0)
           {
             state = FTR2;
           }
           else
           {
             /* report dropped bytes and set the state to starting state */
             printf("bytes dropped; state: %d\n",state);
             state = HDR1;
           }
           break;

      case FTR2:
           if(data[i] == FOOTER_BYTE1)
           {
            /* post packet to a message queue for handling */
              mq_send(mqdes, curr_pkt, pl_len, 0);
              // printf("pkt Rcvd: %d\n", pl_len);

           }
           else
           {
             /* report dropped bytes and set the state to starting state */
             printf("bytes dropped; state: %d\n",state);
           }
           state = HDR1;
           break;
    }
  }
  fflush(stdout);
  
}

uint8_t        read_buf[64];  /* TODO remove the magic number */
int            num_bytes = 0;
int            serial_port;

int serial_data_parser()
{
  pthread_t      proc_pl_thread, proc_serial_read_thread;
  int            iret, iret2, ret = 0;
  struct mq_attr attr;  
  
  /* Fill in attributes for message queue */
  attr.mq_maxmsg  = 10;      /* TODO remove magic number */
  attr.mq_msgsize = 512;    /* TODO remove magic number */
  attr.mq_flags   = 0;
  attr.mq_curmsgs = 0;
  
  mqdes = mq_open("/serial_queue", O_CREAT | O_RDWR, 0644, &attr);
  
  if (mqdes == (mqd_t)-1) {
      printf("Error, cannot open the queue: %s.\n", strerror(errno));
  }

  serial_port = open_port();
  
  iret = pthread_create( &proc_pl_thread, NULL, proc_pl_func, &mqdes);
  iret2 = pthread_create( &proc_serial_read_thread, NULL, proc_serial_read_func, NULL);

  if(iret && iret2)
    ret = -1;

  serial_protocol_init();

  return ret;
}

void *proc_serial_read_func(void *p){
  
  /* TODO send messages to enable the sensors */
  memset(&read_buf, 0, sizeof(read_buf));

  // printf("proc_serial_read_func() started\n");
  
  while(1)
  {
    // num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    num_bytes = read(serial_port, &read_buf, 1);

    if(num_bytes > 0)
    {
#if DEBUG   
      gettimeofday(&tv, NULL);
      microsecondsSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000000 + (unsigned long long)(tv.tv_usec);
      printf("%llu, %d\n", microsecondsSinceEpoch, num_bytes);
#endif // DEBUG

      parse_msg(read_buf, num_bytes);
    }
  }
}

int sendData(const uint8_t* data, uint16_t data_len)
{
    const int txBytes = write(serial_port, data, data_len);
    // printf("txBytes sent by write(): %d\n", txBytes);
    return txBytes;
}

/* TODO remove extern declaration */

extern int protcore_decode_one_packet(const uint8_t * buffer, unsigned size);

void *proc_pl_func( void *ptr )
{
  uint8_t  rcvmsg[512];
  int      len;

  // printf("proc_pl_func() started\n");
  
  while (1)
  {
	  len = mq_receive(mqdes, rcvmsg, 512, 0);
	  if(len == -1)
	     printf("Error, cannot read the queue: %s.\n", strerror(errno));

	  protcore_decode_one_packet(rcvmsg, len);
  }
}

int main(){
  serial_data_parser();
}
