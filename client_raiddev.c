#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "common.h"
#include "iopccmd_raiddevcount.h"
#include "iopccmd_raiddevget.h"
#include "iopccmd_raiddevset.h"
#include "client_raiddev.h"

static uint32_t count()
{
    DEFINE_DATA_PTR(struct req_raiddevcount_t, struct res_raiddevcount_t)
    uint32_t count = 0;
    uint8_t qname[20];

    printf("Send to count\n");
    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, RAIDDEV_COUNT, &qname[0], sizeof(struct req_raiddevcount_t));
    _setAndGetData(&req, &res, &qname[0]);

    printf("Get from count %d\n", res_data->count);
    count = res_data->count;
    return count;
}

static int set(uint8_t index, struct raiddev_info_t* info)
{
    DEFINE_DATA_PTR(struct req_raiddevset_t, struct res_raiddevset_t)
    uint8_t qname[20];
    int i = 0;

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, RAIDDEV_SET, &qname[0], sizeof(struct req_raiddevset_t));

    req_data->index = index;
    req_data->enabled = info->enabled;
    memcpy(req_data->name, info->name, strlen(info->name));
    memcpy(req_data->type, info->type, strlen(info->type));
    for(i=0;i<info->dev_size;i++) {
        req_data->dev[i].enabled = info->dev[i].enabled;
	memcpy(req_data->dev[i].path, info->dev[i].path, strlen(info->dev[i].path));
    }

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static int get(uint8_t index, struct raiddev_info_t* info)
{
    DEFINE_DATA_PTR(struct req_raiddevget_t, struct res_raiddevget_t)
    uint8_t qname[20];
    int i = 0;

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, RAIDDEV_GET, &qname[0], sizeof(struct req_raiddevget_t));

    req_data->index = index;

    _setAndGetData(&req, &res, &qname[0]);

    if(res_data->status != 0)
        return res_data->status;

    info->enabled = res_data->enabled;
    strcpy(info->name, res_data->name);
    strcpy(info->type, res_data->type);
    info->dev_size = res_data->dev_size;
    for(i=0;i<res_data->dev_size;i++) {
        info->dev[i].enabled = res_data->dev[i].enabled;
	memcpy(info->dev[i].path, res_data->dev[i].path, strlen(res_data->dev[i].path));
    }

    return res_data->status;
}

//static struct client_raiddev_t* obj = NULL;

DEFINE_INSTANCE(client_raiddev);
DEFINE_GET_INSTANCE(client_raiddev)
{
    if(!obj) {
        obj = malloc(sizeof(struct client_raiddev_t));
	obj->count = count;
//	obj->add = add;
	obj->set = set;
	obj->get = get;
    }
    return obj;
}

DEFINE_DEL_INSTANCE(client_raiddev)
{
    if(obj)
        free(obj);
}

