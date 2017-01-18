#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "common.h"
#include "iopccmd_db.h"
#include "client_db.h"

static uint8_t get_bool_flash(uint8_t* key)
{
    DEFINE_DATA_PTR(struct req_dbgetbool_t, struct res_dbgetbool_t)
    uint8_t value = 0;
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, GET_BOOL_FLASH, &qname[0], sizeof(struct req_dbgetbool_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));

    _setAndGetData(&req, &res, &qname[0]);

    value = res_data->val;
    return value;
}

static uint8_t get_bool_ram(uint8_t* key)
{
    DEFINE_DATA_PTR(struct req_dbgetbool_t, struct res_dbgetbool_t)
    uint8_t value = 0;
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, GET_BOOL_RAM, &qname[0], sizeof(struct req_dbgetbool_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));

    _setAndGetData(&req, &res, &qname[0]);

    value = res_data->val;
    return value;
}

static uint8_t set_bool_flash(uint8_t* key, uint8_t val)
{
    DEFINE_DATA_PTR(struct req_dbsetbool_t, struct res_dbsetbool_t)
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SET_BOOL_FLASH, &qname[0], sizeof(struct req_dbsetbool_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));
    req_data->val = val;

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint8_t set_bool_ram(uint8_t* key, uint8_t val)
{
    DEFINE_DATA_PTR(struct req_dbsetbool_t, struct res_dbsetbool_t)
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SET_BOOL_RAM, &qname[0], sizeof(struct req_dbsetbool_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));
    req_data->val = val;

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint32_t get_uint32_flash(uint8_t* key)
{
    DEFINE_DATA_PTR(struct req_dbgetuint32_t, struct res_dbgetuint32_t)
    uint8_t qname[20];
    uint32_t val = 0;

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, GET_UINT32_FLASH, &qname[0], sizeof(struct req_dbgetuint32_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));

    _setAndGetData(&req, &res, &qname[0]);

    val = res_data->val;

    return val;
}

static uint32_t get_uint32_ram(uint8_t* key)
{
    DEFINE_DATA_PTR(struct req_dbgetuint32_t, struct res_dbgetuint32_t)
    uint8_t qname[20];
    uint32_t val = 0;

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, GET_UINT32_RAM, &qname[0], sizeof(struct req_dbgetuint32_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));

    _setAndGetData(&req, &res, &qname[0]);

    val = res_data->val;

    return val;
}

static uint8_t set_uint32_flash(uint8_t* key, uint32_t val)
{
    DEFINE_DATA_PTR(struct req_dbsetuint32_t, struct res_dbsetuint32_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SET_UINT32_FLASH, &qname[0], sizeof(struct req_dbsetuint32_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));
    req_data->val = val;

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint8_t set_uint32_ram(uint8_t* key, uint32_t val)
{
    DEFINE_DATA_PTR(struct req_dbsetuint32_t, struct res_dbsetuint32_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SET_UINT32_RAM, &qname[0], sizeof(struct req_dbsetuint32_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));
    req_data->val = val;

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint16_t get_string_flash(uint8_t* key, uint8_t* val)
{
    DEFINE_DATA_PTR(struct req_dbgetstring_t, struct res_dbgetstring_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, GET_STRING_FLASH, &qname[0], sizeof(struct req_dbgetstring_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));

    _setAndGetData(&req, &res, &qname[0]);

    memcpy(val, res_data->val, res_data->val_len);
    return res_data->val_len;
}

static uint16_t get_string_ram(uint8_t* key, uint8_t* val)
{
    DEFINE_DATA_PTR(struct req_dbgetstring_t, struct res_dbgetstring_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, GET_STRING_RAM, &qname[0], sizeof(struct req_dbgetstring_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));

    _setAndGetData(&req, &res, &qname[0]);

    memcpy(val, res_data->val, res_data->val_len);
    return res_data->val_len;
}

static uint8_t set_string_flash(uint8_t* key, uint8_t* val)
{
    DEFINE_DATA_PTR(struct req_dbsetstring_t, struct res_dbsetstring_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SET_STRING_FLASH, &qname[0], sizeof(struct req_dbsetstring_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));
    req_data->val_len = strlen(val);
    memcpy(req_data->val, val, strlen(val));

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint8_t set_string_ram(uint8_t* key, uint8_t* val)
{
    DEFINE_DATA_PTR(struct req_dbsetstring_t, struct res_dbsetstring_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SET_STRING_RAM, &qname[0], sizeof(struct req_dbsetstring_t));

    req_data->key_len = strlen(key);
    memcpy(req_data->key, key, strlen(key));
    req_data->val_len = strlen(val);
    memcpy(req_data->val, val, strlen(val));

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint8_t save2persist()
{
    DEFINE_DATA_PTR(struct req_save2persist_t, struct res_save2persist_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, SAVE2PERSIST, &qname[0], sizeof(struct req_save2persist_t));

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

static uint8_t restore2default()
{
    DEFINE_DATA_PTR(struct req_restore2default_t, struct res_restore2default_t);
    uint8_t qname[20];

    _getQName(&qname[0], sizeof(qname));
    _initReqData(&req, CLA_DB, RESTORE2DEFAULT, &qname[0], sizeof(struct req_restore2default_t));

    _setAndGetData(&req, &res, &qname[0]);

    return res_data->status;
}

DEFINE_INSTANCE(client_db);
DEFINE_GET_INSTANCE(client_db)
{
    if(!obj) {
        obj = malloc(sizeof(struct client_db_t));
	obj->get_bool_flash = get_bool_flash;
	obj->set_bool_flash = set_bool_flash;
	obj->get_uint32_flash = get_uint32_flash;
	obj->set_uint32_flash = set_uint32_flash;
	obj->get_string_flash = get_string_flash;
	obj->set_string_flash = set_string_flash;
	obj->save2persist = save2persist;

	obj->get_bool_ram = get_bool_ram;
	obj->set_bool_ram = set_bool_ram;
	obj->get_uint32_ram = get_uint32_ram;
	obj->set_uint32_ram = set_uint32_ram;
	obj->get_string_ram = get_string_ram;
	obj->set_string_ram = set_string_ram;
	obj->restore2default = restore2default;
    }
    return obj;
}

DEFINE_DEL_INSTANCE(client_db)
{
    if(obj)
        free(obj);
}

