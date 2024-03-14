#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gst/gst.h>
#include "timer.h"
gboolean on_bus(GstBus *bus, GstMessage *msg, gpointer data)
{
    switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_ERROR: {
        GError *err;
        char *debug;
        gst_message_parse_error(msg, &err, &debug);
        gst_message_unref(msg);
        puts(err->message);
        g_error_free(err);
        free(debug);
        gst_object_unref(bus);
        break;
    }
    case GST_MESSAGE_EOS:
        gst_element_set_state(GST_ELEMENT(data), GST_STATE_NULL);
        gst_object_unref(bus);
        break;
    default:
        break;
    }
    return true;
}
void play_audio(int hour)
{
    GstElement *pipeline = gst_pipeline_new("gtk-pipeline");
    GstElement *playbin = gst_element_factory_make("playbin", "gtk-play");
    if (playbin)
    {
        gst_bin_add(GST_BIN(pipeline), playbin);
        char *dir = g_get_current_dir();
        char *file = alloca(strlen(dir) + 16);
        strcpy(file, "file:///");
        strcat(file, dir);
        strcat(file, "\\");
        char num[3] = { '\0' };
        sprintf(num, "%d", hour);
        strcat(file, num);
        strcat(file, ".mp3");
        g_object_set(G_OBJECT(playbin), "uri", file, NULL);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
        GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
        gst_bus_add_watch(bus, on_bus, pipeline);
    }
    return;
}
static void play_home_audio(void)
{
    GstElement *pipeline = gst_pipeline_new("gtk-pipeline");
    GstElement *playbin = gst_element_factory_make("playbin", "gtk-play");
    if (playbin)
    {
        gst_bin_add(GST_BIN(pipeline), playbin);
        char *dir = g_get_current_dir();
        char *file = alloca(strlen(dir) + 20);
        strcpy(file, "file:///");
        strcat(file, dir);
        strcat(file, "\\home.mp3");
        g_object_set(G_OBJECT(playbin), "uri", file, NULL);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
        GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
        gst_bus_add_watch(bus, on_bus, pipeline);
    }
    return;
}
void audio(int argc, char *argv[])
{
    gst_init(&argc, &argv);
    play_home_audio();
    start_timer(play_audio);
    return;
}