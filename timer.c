#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include "timer.h"
static struct
{
    short hour;
    double sec;
} ts;
static void get_timespec(void)
{
    time_t cur = time(NULL);
    struct tm *curTime = localtime(&cur);
    struct tm tarTime;
    memcpy(&tarTime, curTime, sizeof(struct tm));
    tarTime.tm_hour = curTime->tm_hour + 1;
    tarTime.tm_min = 0;
    tarTime.tm_sec = 0;
    ts.hour = tarTime.tm_hour;
    ts.sec = difftime(mktime(&tarTime), mktime(curTime));
    return;
}
gboolean deal_time(gpointer data)
{
    void (*f)(int);
    f = data;
    f(ts.hour);
    start_timer(data);
    return false;
}
void start_timer(void (*func)(int))
{
    get_timespec();
    long long sec = ts.sec == 0 ? sec = 60 * 60 : ts.sec;
    g_timeout_add_seconds(sec, G_SOURCE_FUNC(deal_time), func);
    return;
}