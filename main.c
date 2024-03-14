#include "mainwindow.h"
int main(int argc, char *argv[])
{
    struct Args args = { argc, argv };
    GtkApplication *app = gtk_application_new("nook.inc", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(G_OBJECT(app), "activate", G_CALLBACK(on_activate), &args);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}