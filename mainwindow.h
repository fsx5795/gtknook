#include <gtk/gtk.h>
struct Args
{
    int argc;
    char **argv;
};
extern void on_activate(GtkApplication*, gpointer);