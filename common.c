#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "iopcops_mq.h"

static volatile uint32_t counter = 0;

void _getQName(uint8_t* name, uint16_t name_len)
{
    counter++;
    memset(name, 0, name_len);
    sprintf(name, "%015x", counter);
}

void _initReqData(struct msg_t* req, uint8_t group, uint8_t cmd, uint8_t* qname, uint16_t data_len)
{
    strcpy(req->hdr.src, qname);
    strcpy(req->hdr.dst, TASK_IOPCLAUNCHER);
    req->hdr.fn = group;
    req->hdr.cmd = cmd;

//    memset(req->data, 0, MAX_MSG_DATA_SIZE);

    req->hdr.data_size = data_len;
}

void _setAndGetData(struct msg_t* req, struct msg_t* res, uint8_t* qname)
{
//    memset(res->data, 0, MAX_MSG_DATA_SIZE);
    GET_INSTANCE(ops_mq)->set_to(TASK_IOPCLAUNCHER, req);
    GET_INSTANCE(ops_mq)->get_from(qname, res);
    GET_INSTANCE(ops_mq)->destroy(qname);
}
