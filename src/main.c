#include <dlfcn.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

typedef int (*JLINKARM_GetDLLVersion)();

#define LOGE(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)
#define LOGI(format, ...) fprintf(stdout, format "\n", ##__VA_ARGS__)

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        LOGE("Usage: %s [libfile]", basename((char *)argv[0]));
        return -1;
    }

    void *handle;
    char *err;

    JLINKARM_GetDLLVersion GetDLLVersion = NULL;

    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
        LOGE("%s", dlerror());
        return -1;
    }

    *(void **)(&GetDLLVersion) = dlsym(handle, "JLINKARM_GetDLLVersion");
    if ((err = dlerror()) != NULL) {
        LOGE("%s", err);
        return -1;
    }

    int version = GetDLLVersion();

    int major = version / 10000;
    int minor = version / 100 % 100;

    int idx = version % 100;
    char rev = idx == 0 ? '\0' : 'a' + (idx - 1);

    LOGI("V%d.%02d%c", major, minor, rev);

    dlclose(handle);
    return 0;
}
