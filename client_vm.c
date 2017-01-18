#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "common.h"
#include "iopccmd_vmadd.h"
#include "iopccmd_vmcount.h"
#include "iopccmd_vmget.h"
#include "iopccmd_vmset.h"
#include "client_vm.h"

static uint32_t count()
{
    DEFINE_DATA_PTR(struct req_vmcount_t, struct res_vmcount_t)
    uint32_t count = 0;
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, VM_COUNT, &qname[0], sizeof(struct req_vmcount_t));
    _setAndGetData(&req, &res, &qname[0]);

    count = res_data->count;
    return count;
}

static int set(uint8_t index, struct vm_info_t* info)
{
    DEFINE_DATA_PTR(struct req_vmset_t, struct res_vmset_t)
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, VM_SET, &qname[0], sizeof(struct req_vmset_t));

    req_data->index = index;
    req_data->auto_start = info->auto_start;
    memcpy(req_data->name, info->name, strlen(info->name));
    memcpy(req_data->nettype, info->nettype, strlen(info->nettype));
    memcpy(req_data->nethwlink, info->nethwlink, strlen(info->nethwlink));
    memcpy(req_data->nethwaddr, info->nethwaddr, strlen(info->nethwaddr));
    memcpy(req_data->base_path, info->base_path, strlen(info->base_path));

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}
static int get(uint8_t index, struct vm_info_t* info)
{
    DEFINE_DATA_PTR(struct req_vmget_t, struct res_vmget_t)
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_BASE, VM_GET, &qname[0], sizeof(struct req_vmget_t));

    req_data->index = index;

    _setAndGetData(&req, &res, &qname[0]);

    if(res_data->status != 0)
        return res_data->status;

    info->auto_start = res_data->auto_start;
    strcpy(info->name, res_data->name);
    strcpy(info->base_path, res_data->base_path);
    strcpy(info->nettype, res_data->nettype);
    strcpy(info->nethwlink, res_data->nethwlink);
    strcpy(info->nethwaddr, res_data->nethwaddr);

    return res_data->status;
}

//static struct client_vm_t* obj = NULL;

DEFINE_INSTANCE(client_vm);
DEFINE_GET_INSTANCE(client_vm)
{
    if(!obj) {
        obj = malloc(sizeof(struct client_vm_t));
	obj->count = count;
	obj->set = set;
	obj->get = get;
    }
    return obj;
}

DEFINE_DEL_INSTANCE(client_vm)
{
    if(obj)
        free(obj);
}

