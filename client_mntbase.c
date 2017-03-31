#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "common.h"
#include "iopccmd_mntbaseadd.h"
#include "iopccmd_mntbasecount.h"
#include "iopccmd_mntbaseget.h"
#include "iopccmd_mntbaseset.h"
#include "iopcops_client_mntbase.h"

static uint32_t count()
{
    DEFINE_DATA_PTR(struct req_mntbasecount_t, struct res_mntbasecount_t)
    uint32_t count = 0;
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, MNTBASE_COUNT, &qname[0], sizeof(struct req_mntbasecount_t));
    _setAndGetData(&req, &res, &qname[0]);

    count = res_data->count;
    return count;
}

static int set(uint8_t index, struct mntbase_info_t* info)
{
    DEFINE_DATA_PTR(struct req_mntbaseset_t, struct res_mntbaseset_t)
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, MNTBASE_SET, &qname[0], sizeof(struct req_mntbaseset_t));

    req_data->index = index;
    req_data->enabled = info->enabled;
    //req_data->fixed = info->fixed;
    memcpy(req_data->name, info->name, strlen(info->name));
    memcpy(req_data->src, info->src, strlen(info->src));
    memcpy(req_data->dst, info->dst, strlen(info->dst));
    memcpy(req_data->type, info->type, strlen(info->type));

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static int get(uint8_t index, struct mntbase_info_t* info)
{
    DEFINE_DATA_PTR(struct req_mntbaseget_t, struct res_mntbaseget_t)
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, MNTBASE_GET, &qname[0], sizeof(struct req_mntbaseget_t));

    req_data->index = index;

    _setAndGetData(&req, &res, &qname[0]);

    if(res_data->status != 0)
        return res_data->status;

    memset(info, 0, sizeof(struct mntbase_info_t));
    info->enabled = res_data->enabled;
    info->fixed = res_data->fixed;
    strcpy(info->name, res_data->name);
    strcpy(info->src, res_data->src);
    strcpy(info->dst, res_data->dst);
    strcpy(info->type, res_data->type);

    return res_data->status;
}

//static struct client_mntbase_t* obj = NULL;

DEFINE_INSTANCE(client_mntbase, obj);
DEFINE_GET_INSTANCE(client_mntbase, obj)
{
    if(!obj) {
        obj = malloc(sizeof(struct ops_client_mntbase_t));
	obj->count = count;
//	obj->add = add;
	obj->set = set;
	obj->get = get;
    }
    return obj;
}

DEFINE_DEL_INSTANCE(client_mntbase, obj)
{
    if(obj)
        free(obj);
}

