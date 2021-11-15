///////// gcc `pkg-config --cflags gtk+-3.0` -rdynamic -o test2 test2.c `pkg-config --libs gtk+-3.0` -lsqlite3 -std=c99


//////gcc `pkg-config --cflags gtk+-3.0` -rdynamic -o test2 test2.c `pkg-config --libs gtk+-3.0` -lsqlite3 -std=c99 -lm -Wall


#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <limits.h>
#include <string.h>
#include <ftw.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

GtkBuilder *builder;
GtkWidget *window;
GtkWidget *button;
GtkWidget *play_button;
GtkWidget *history_exit;
GtkWidget *popup;
GtkWidget *align1;
GtkWidget *combo_box;
GtkWidget *combo_box2;
GtkWidget *image1;
GtkWidget *image2;
GtkWidget *image_popup;
GtkWidget *image_popup2;
GtkWidget *cbb_entry;
GtkWidget *cbb_entry2;


GdkPixbuf *buf1;
GdkPixbuf *buf2;
GdkPixbuf *buf_popup;

GError* err = NULL;
GError* err2 = NULL;
GtkListStore *store;
GtkListStore *store2;

char prev[100];
char prev2[100];

char newest[PATH_MAX];
char newest2[PATH_MAX];
time_t mtime = 0;
time_t mtime2 =0;





G_MODULE_EXPORT void exit_button_cb(GtkButton* button, gpointer data)
{
    gtk_main_quit();
    g_print(".............EXIT PROGRAM.............\n");
}

G_MODULE_EXPORT void history_exit_cb(GtkButton* button, GtkWidget *popup)
{
    gtk_widget_destroy(popup);
}

G_MODULE_EXPORT void show_popup_cb(GtkButton *button,GtkWidget *popup)
{
    gtk_widget_show( popup );
    

}

static int checkifnewer(const char *path, const struct stat *sb, int typeflag)
{
    if (typeflag == FTW_F && sb->st_mtime > mtime) {
        mtime = sb->st_mtime;
        strncpy(newest, path, PATH_MAX);
    }
    return 0 ;
}

G_MODULE_EXPORT void check_new_cb(GtkWidget *image)
{

    GtkTreeIter iter;
    int value ;

    GdkPixbuf *pixbuf;

    ftw("/home/nachanon/Desktop/www/", checkifnewer, 1); 
    //printf("%s\n", newest);

    //printf("%s\n", prev);
    value = strcmp(prev,newest);

    buf1 = gdk_pixbuf_new_from_file(newest,&err);
    pixbuf=gdk_pixbuf_scale_simple(buf1,400,350,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image1), pixbuf);
    //gtk_container_add(GTK_CONTAINER(align1),image);
    gtk_widget_show(image1);
    
    while(1)
    {
        
        if (value != 0)
        {
        while(1){
            strcpy(prev,newest);
            gtk_list_store_append (store, &iter);
            gtk_list_store_set (store, &iter, 0, newest, -1);
            break;
        }
        printf("\n");
        }

        break;
    }
}

static int checkifnewer2(const char *path, const struct stat *sb, int typeflag)
{
    if (typeflag == FTW_F && sb->st_mtime > mtime2) {
        mtime2 = sb->st_mtime;
        strncpy(newest2, path, PATH_MAX);
    }
    return 0 ;
}

G_MODULE_EXPORT void check_new2_cb(GtkWidget *image)
{

    GtkTreeIter iter;
    int value ;

    GdkPixbuf *pixbuf;

    ftw("/home/nachanon/Desktop/camera2/", checkifnewer2, 1); 
    //printf("%s\n", newest);

    //printf("%s\n", prev);
    value = strcmp(prev2,newest2);

    buf2 = gdk_pixbuf_new_from_file(newest2,&err);
    pixbuf=gdk_pixbuf_scale_simple(buf2,400,350,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image2), pixbuf);
    //gtk_container_add(GTK_CONTAINER(align1),image);
    gtk_widget_show(image2);
    
    while(1)
    {
        
        if (value != 0)
        {
        while(1){
            strcpy(prev2,newest2);
            gtk_list_store_append (store2, &iter);
            gtk_list_store_set (store2, &iter, 0, newest2, -1);
            break;
        }
        printf("\n");
        }

        break;
    }
}



G_MODULE_EXPORT void on_play_button_clicked(GtkButton *button)
{
    
    g_timeout_add(1000, (GSourceFunc)check_new_cb, NULL);

    g_timeout_add(1000, (GSourceFunc)check_new2_cb, NULL);
}


G_MODULE_EXPORT void open_image_popup_cb(GtkButton *button )
{
    GtkWidget * win;
    GdkPixbuf *pixbuf;
    char *path;

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "Image");
    gtk_window_set_default_size(GTK_WINDOW(win), 500, 400);


    path = gtk_editable_get_chars(GTK_EDITABLE(cbb_entry),0,-1);
    //printf("%s \n",path);
    //gtk_widget_show( open_image_popup );

    image_popup = gtk_image_new();

    buf_popup = gdk_pixbuf_new_from_file(path,&err);
    pixbuf=gdk_pixbuf_scale_simple(buf_popup,400,350,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_popup), pixbuf);
    //gtk_container_add(GTK_CONTAINER(align1),image);
    gtk_widget_show(image_popup);

    gtk_container_add(GTK_CONTAINER(win),image_popup);
    printf("OPENING CAMERA_1 IMAGE FROM : %s\n",path);
    gtk_editable_delete_text(GTK_EDITABLE(cbb_entry),0,-1);

    gtk_widget_show_all(win);
    //g_object_unref(G_OBJECT(buf2));

}

G_MODULE_EXPORT void open_image_popup_cb2(GtkButton *button )
{
    GtkWidget * win;
    GdkPixbuf *pixbuf;
    char *path;

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "Image");
    gtk_window_set_default_size(GTK_WINDOW(win), 500, 400);


    path = gtk_editable_get_chars(GTK_EDITABLE(cbb_entry2),0,-1);
    //printf("%s \n",path);
    //gtk_widget_show( open_image_popup );

    image_popup = gtk_image_new();

    buf_popup = gdk_pixbuf_new_from_file(path,&err);
    pixbuf=gdk_pixbuf_scale_simple(buf_popup,400,350,GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_popup), pixbuf);
    //gtk_container_add(GTK_CONTAINER(align1),image);
    gtk_widget_show(image_popup);

    gtk_container_add(GTK_CONTAINER(win),image_popup);
    printf("OPENING CAMERA_2 IMAGE FROM : %s\n",path);
    gtk_editable_delete_text(GTK_EDITABLE(cbb_entry2),0,-1);

    gtk_widget_show_all(win);
    //g_object_unref(G_OBJECT(buf2));

}

G_MODULE_EXPORT void clear_button_cb(GtkButton *button)
{
    gtk_list_store_clear(store);
}

G_MODULE_EXPORT void clear_button_cb2(GtkButton *button)
{
    gtk_list_store_clear(store2);
}

int main(int argc,char **argv)
{
    
    //GtkCellRenderer *col;
    
    //GtkTreeIter iter;

    gtk_init(&argc,&argv);

    builder =gtk_builder_new();

    gtk_builder_add_from_file( builder, "FMD.glade",NULL);
    

    window =GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
    button =GTK_WIDGET(gtk_builder_get_object(builder,"Exit_button"));
    popup = GTK_WIDGET(gtk_builder_get_object(builder,"history_popup" ) );
    history_exit =GTK_WIDGET(gtk_builder_get_object(builder,"history_exit_button"));
    play_button =GTK_WIDGET(gtk_builder_get_object(builder,"Play_button"));
    align1 =GTK_WIDGET(gtk_builder_get_object(builder,"align1"));
    combo_box =GTK_WIDGET(gtk_builder_get_object(builder,"combobox"));
    combo_box2 =GTK_WIDGET(gtk_builder_get_object(builder,"combobox2"));
    image1 =GTK_WIDGET(gtk_builder_get_object(builder,"image1"));
    image2 =GTK_WIDGET(gtk_builder_get_object(builder,"image2"));
    cbb_entry =GTK_WIDGET(gtk_builder_get_object(builder,"cbb_entry"));
    cbb_entry2=GTK_WIDGET(gtk_builder_get_object(builder,"cbb_entry2"));


    store = gtk_list_store_new(1,  G_TYPE_STRING);
    store2 = gtk_list_store_new(1, G_TYPE_STRING);

    gtk_combo_box_set_model(GTK_COMBO_BOX(combo_box),GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    gtk_combo_box_set_model(GTK_COMBO_BOX(combo_box2),GTK_TREE_MODEL(store2));
    g_object_unref(store2);
   
   
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    
   
   

    gtk_builder_connect_signals(builder, popup );

    
  

    gtk_builder_connect_signals(builder,NULL);
    
    g_object_unref(G_OBJECT(builder));

    
    
    

    gtk_widget_show_all(window);

    
    
    
  
    


    gtk_main();





    return 0;
}

