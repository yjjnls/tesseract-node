#include <stdio.h>

#include <iostream>
#include <exception>

#include "nlohmann/json.hpp"

#include "./plugin_interface.h"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#define __VERSION__ "0.0.1"

#define const_error_msg(type, msg) \
    "{\"type\": \"" type "\", \"message\": \"" msg "\"}"

tesseract::TessBaseAPI *api = NULL;

static void init(const void *iface,
                 const void *context,
                 const plugin_buffer_t *data,
                 plugin_callback_fn callback)
{
    plugin_interface_t *self = (plugin_interface_t *)iface;

    if (callback)
    {
        callback(iface, context, 0, NULL);
    }

    api = new tesseract::TessBaseAPI();
    api->Init(NULL, "eng");
    return;
}


static void call(const void *iface,
                 const void *context,
                 plugin_buffer_t *data,
                 plugin_buffer_t *meta,
                 plugin_callback_fn callback)
{
    plugin_interface_t *self = (plugin_interface_t *)iface;
    if (!meta || !meta->data || !meta->size)
    {
        plugin_buffer_t err;
        plugin_buffer_string_set(&err,
                                 const_error_msg("call", "action not specified."));
        callback(self, context, 1, &err);
        return;
    }
    nlohmann::json jmeta;
    try
    {
        const char *begin = (const char *)meta->data;
        const char *end = begin + meta->size;

        jmeta = nlohmann::json::parse(begin, end);
    }
    catch (std::exception &)
    {
        plugin_buffer_t err;
        plugin_buffer_string_set(&err,
                                 const_error_msg("call", "invalid meta json string."));
        callback(self, context, 1, &err);
        return;
    }

    nlohmann::json jdata;
    try
    {
        if (data && data->data && data->size)
        {
            const char *begin = (const char *)data->data;
            const char *end = begin + data->size;
            jdata = nlohmann::json::parse(begin, end);
        }
    }
    catch (std::exception &)
    {
        plugin_buffer_t err;
        plugin_buffer_string_set(&err,
                                 const_error_msg("call", "invalid data json string."));
        callback(self, context, 1, &err);
        return;
    }


    size_t size = jdata["size"];
    long long pointer = jdata["data"];
    unsigned char *buffer = reinterpret_cast<unsigned char *>(pointer);

    char *outText;
    Pix *image = pixReadMemBmp(buffer, size);
    image->xres = 70;
    image->yres = 70;
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    std::string res(outText, strlen(outText) - 1);
    // printf("OCR output: %s\n", outText);

    delete[] outText;

    pixDestroy(&image);

    jdata["ocr"] = res;
    // printf("result: %s\n", jdata.dump().c_str());

    plugin_buffer_t m, d;
    plugin_buffer_string_set(&d, jdata.dump().c_str());
    plugin_buffer_string_set(&m, jmeta.dump().c_str());
    self->notify(self, &d, &m);
}

static void terminate(const void *iface,
                      const void *context,
                      plugin_callback_fn callback)
{
    plugin_interface_t *self = (plugin_interface_t *)iface;

    if (callback)
    {
        callback(self, context, 0, NULL);
    }
    if (self->instance)
    {
        free(self->instance);
        self->instance = NULL;
    }
    api->End();
}

PLUGIN_INTERFACE(__VERSION__, init, call, terminate)
