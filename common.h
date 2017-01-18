#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>

#include "iopcdefine.h"
#include "iopcops_mq.h"

void _getQName(uint8_t* name, uint16_t name_len);
void _initReqData(struct msg_t* req, uint8_t group, uint8_t cmd, uint8_t* qname, uint16_t data_len);
void _setAndGetData(struct msg_t* req, struct msg_t* res, uint8_t* qname);

#define DEFINE_DATA_PTR(REQ_T, RES_T)	\
	struct msg_t req;				\
	struct msg_t res;				\
	REQ_T* req_data = (REQ_T*)&req.data;	\
	RES_T* res_data = (RES_T*)&res.data;	\
	memset(req_data, 0, MAX_MSG_DATA_SIZE);	\
	memset(res_data, 0, MAX_MSG_DATA_SIZE);	

#endif
