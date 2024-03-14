#include <stdbool.h>
#include "audio.h"
#include "mainwindow.h"
void on_activate(GtkApplication *app, gpointer data)
{
    struct Args *args = data;
    GtkWidget *window = gtk_application_window_new(app);
    audio(args->argc, args->argv);
    return gtk_widget_show_all(window);
}