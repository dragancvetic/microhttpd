#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define PORT 8888
static int print_out_key (void *cls,
        enum MHD_ValueKind kind,
        const char *key,
        const char *value)
{
    printf ("%s: %s\n", key, value);
    printf ("%s\n", key);
    printf ("%s\n", value);
    return MHD_YES;
}

static int answer_to_connection (void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **con_cls)
{
    printf ("New %s request for %s using version %s\n", method, url, version);
    MHD_get_connection_values (connection,
            MHD_HEADER_KIND,
            print_out_key,
            NULL);
    return MHD_NO;
}

int main (int argc, char *argv[])
{
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY,
            PORT,
            NULL,
            NULL,
            &answer_to_connection,
            NULL,
            MHD_OPTION_END);

    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon (daemon);
    return 0;
}
