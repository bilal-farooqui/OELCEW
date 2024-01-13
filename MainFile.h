#ifndef HEADERFILE_H
#define HEADERFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define USERNAME "hk7800608@gmail.com"
#define APP_PASSWORD "xyjg wjmg xclb lxlf"

struct UploadStatus {
    const char *data;
    size_t size;
};

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t ReadCallback(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct UploadStatus *upload_ctx = (struct UploadStatus *)userp;

    size_t to_copy = size * nmemb;
    to_copy = (to_copy > upload_ctx->size) ? upload_ctx->size : to_copy;

    if (to_copy) {
        memcpy(ptr, upload_ctx->data, to_copy);
        upload_ctx->data += to_copy;
        upload_ctx->size -= to_copy;
        return to_copy;
    }

    return 0;
}

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (!mem->memory) {
        fprintf(stderr, "Error: Out of memory\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

