#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <gtk/gtk.h>

// Callback to activate the application
static void activate(GtkApplication *app, gpointer user_data) {
    // Create a new window
    GtkWidget *window = gtk_application_window_new(app);

    // Set the title of the window
    gtk_window_set_title(GTK_WINDOW(window), "Execute Program");

    // Set the default size of the window
    gtk_window_set_default_size(GTK_WINDOW(window), 450, 150);

    // Create a GtkFixed container
    GtkWidget *fixed = gtk_fixed_new();

    // Create a GtkEntry (text box)
    GtkWidget *entry = gtk_entry_new();

    // Set placeholder text
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "program");

    // Add the entry to the GtkFixed container at specific coordinates
    gtk_fixed_put(GTK_FIXED(fixed), entry, 65, 75); // X=65, Y=50

    // Set the size of the entry
    gtk_widget_set_size_request(entry, 375, 25); // Width=400, Height=65

    // Add the GtkFixed container to the window
    gtk_window_set_child(GTK_WINDOW(window), fixed);

    // Make the window visible
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
    // Create a new GtkApplication
    GtkApplication *app = gtk_application_new("com.example.ExecuteProgram", G_APPLICATION_FLAGS_NONE);

    // Connect the "activate" signal to the callback
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Free the application object
    g_object_unref(app);

    return status;
}

