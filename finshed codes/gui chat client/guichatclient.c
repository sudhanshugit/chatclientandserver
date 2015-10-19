#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include "ip_check.h"
//gchar *ip=NULL,*port=NULL,*u_id=NULL,*me_id=NULL;
/*void hello( GtkWidget *widget,
            gpointer   data )
{
    //g_print ("Hello World\n");
    GtkWidget *window2;
    GtkWidget *button1;
    window2=gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_signal_connect (GTK_OBJECT (window2), "destroy",
                      GTK_SIGNAL_FUNC (destroy), NULL);
    button1=gtk_button_new_with_label("exit");
    gtk_widget_show(button);
    gtk_widget_show(window2);
}*/
struct args
{
 gchar *ip;
 gchar *port;
 gchar *u_id;
 gchar *me_id;
 gchar *msg_r;
 gchar *msg_s;
 gint sockfd;
 GtkWidget *entry_ip,*entry_port,*entry_me,*entry_u;
};
void sending_server(GtkWidget *widget,struct args *data)
{
	data->msg_s=gtk_entry_get_text(GTK_ENTRY(widget));
	send(data->sockfd,data->msg_s,200,0);
	gtk_entry_set_text(GTK_ENTRY (widget),"");
}
void connect_server(GtkWidget *widget, struct args *data);
gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
		   gpointer   data )
{

    g_print ("delete event occurred\n");
    return(TRUE);
}
void destroy( GtkWidget *widget,
              gpointer   data )
{
    gtk_main_quit();
}
void talk( int sockfd,struct args *data)
{
    //g_print ("Hello World\n");
    GtkWidget *window2;
    GtkWidget *button1;
    GtkWidget *table;
    GtkWidget *entry1,*entry2;
    GtkWidget *scroller;
    GtkWidget *label,*label2;
//    GtkWidget *view;
    GtkTextBuffer *buffer;
    window2=gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_signal_connect (GTK_OBJECT (window2), "destroy",
                      GTK_SIGNAL_FUNC (destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window2),20);
    table=gtk_table_new(15,15,TRUE);
    gtk_container_add(GTK_CONTAINER(window2),table);
    gtk_widget_show(table);
    gchar *server_msg;
    if(recv(sockfd,server_msg,100,0))
    label2=gtk_label_new(server_msg);
    gtk_table_attach_defaults(GTK_TABLE(table),label2,0,15,0,1);
    gtk_widget_show(label2);
    if(send(sockfd,data->u_id,50,0)<0);
    //            perror("send");
    if(send(sockfd,data->me_id,50,0)<0);
      //          perror("send");

    //perror("recv");
    //puts(server_msg);
  /*-------------------------scroller--------------------------------------*/
//    scroller=gtk_vscrollbar_new(GTK_TEXT(entry1));
  //  gtk_table_attach_defaults(GTK_TABLE(table),scroller,14,15,0,13);
    //gtk_widget_show(scroller);
  /*-------------------text area one-------------------------------------*/
//    entry1=gtk_entry_new_with_max_length(100000);
  //  gtk_entry_get_text_area(entry1,20);
    entry1 = gtk_text_new(NULL,NULL);
    //buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry1));
    //gtk_text_buffer_set_text(buffer,"helladfafd",-1);
    //gtk_text_set_editable(GTK_TEXT(entry1),TRUE);
    
    gtk_table_attach_defaults(GTK_TABLE(table),entry1,0,14,1,13);
    gtk_widget_show(entry1);
  /*******************lable***********************************************/
    label=gtk_label_new("enter text ::");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,2,13,14);
    gtk_widget_show(label);
  /*--------------------text area two------------------------------------*/
    entry2=gtk_entry_new_with_max_length(200);
    gtk_signal_connect(GTK_OBJECT(entry2),"activate",
				GTK_SIGNAL_FUNC(sending_server),
				(struct args *)data);
    gtk_table_attach_defaults(GTK_TABLE(table),entry2,2,15,13,14);
    gtk_widget_show(entry2);
  /*-----------------------------text areas ends--------------------------*/
    button1=gtk_button_new_with_label("exit");
    //gtk_container_add(GTK_CONTAINER(window2),button1);
    gtk_signal_connect(GTK_OBJECT(button1),"clicked",
                         GTK_SIGNAL_FUNC(destroy),NULL);
    gtk_table_attach_defaults(GTK_TABLE(table),button1,6,9,14,15);
    gtk_widget_show(button1);
    gtk_widget_show(window2);
}

/*void get_entry_callback(GtkWidget *widget, gpointer data)

}*/
int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button1;
    GtkWidget *vbox, *hbox;
    GtkWidget *label;
//    gchar *ip,*port,*u_id,*me_id;
    int fl;
    struct args user_input;
 //   gchar *x;
    gtk_init(&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_signal_connect (GTK_OBJECT (window), "delete_event",
			GTK_SIGNAL_FUNC (destroy), NULL);
    //gtk_signal_connect (GTK_OBJECT (window), "destroy",
//			GTK_SIGNAL_FUNC (destroy), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    vbox=gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
//    gtk_widget_show(vbox);
    //gtk_box_pack_start(GTK_BOX vbox,)
/*-----------------------------for ip-----------------------------------------*/
    hbox=gtk_hbox_new(FALSE,0);
//    gtk_container_add(GTK_CONTAINER(vbox),hbox);
    label=gtk_label_new("IP ADDRESS::    ");
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_widget_show(label);
    user_input.entry_ip=gtk_entry_new_with_max_length(50);
    //user_input.ip=gtk_entry_get_text(GTK_ENTRY (user_input.entry_ip));
    //printf("adf %s\n",user_input.ip);
    gtk_box_pack_start(GTK_BOX(hbox),user_input.entry_ip,TRUE,TRUE,0);
    gtk_widget_show(user_input.entry_ip);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
    gtk_widget_show(hbox);
/*-----------------------------for port--------------------------------------*/
    hbox=gtk_hbox_new(FALSE,0);
  //  gtk_container_add(GTK_CONTAINER(vbox),hbox);
    label=gtk_label_new("PORT NUMBER::");
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_widget_show(label);
    user_input.entry_port=gtk_entry_new_with_max_length(50);
    //user_input.port=gtk_entry_get_text(GTK_ENTRY (user_input.entry_port));
    gtk_box_pack_start(GTK_BOX(hbox),user_input.entry_port,TRUE,TRUE,0);
    gtk_widget_show(user_input.entry_port);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
    gtk_widget_show(hbox);
/*--------------------------------for your id/me----------------------------*/
    hbox=gtk_hbox_new(FALSE,0);
    //gtk_container_add(GTK_CONTAINER(vbox),hbox);
    label=gtk_label_new("YOUR ID   ::     ");
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_widget_show(label);
    user_input.entry_me=gtk_entry_new_with_max_length(50);
    //user_input.me_id=gtk_entry_get_text(GTK_ENTRY (user_input.entry_me));
    gtk_box_pack_start(GTK_BOX(hbox),user_input.entry_me,TRUE,TRUE,0);
    gtk_widget_show(user_input.entry_me);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
    gtk_widget_show(hbox);
/*-----------------------------for your friends id-------------------------*/
    hbox=gtk_hbox_new(FALSE,0);
    //gtk_container_add(GTK_CONTAINER(vbox),hbox);
    label=gtk_label_new("FREINDS ID ::   ");
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_widget_show(label);
    user_input.entry_u=gtk_entry_new_with_max_length(50);
   // user_input.u_id=gtk_entry_get_text(GTK_ENTRY (user_input.entry_u));
    gtk_box_pack_start(GTK_BOX(hbox),user_input.entry_u,TRUE,TRUE,0);
    gtk_widget_show(user_input.entry_u);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
    gtk_widget_show(hbox);
/*-----------------------------------------------------------------------*/

    button = gtk_button_new_with_label ("Connect");
    gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (connect_server), (struct args*)&user_input);
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			       GTK_SIGNAL_FUNC (gtk_widget_destroy),
			       GTK_OBJECT (window));
//    gtk_container_add (GTK_CONTAINER (window), button);
    gtk_box_pack_start(GTK_BOX (vbox),button,TRUE,TRUE,0);
//    if (!(g_strcmp0(ip,NULL)&&g_strcmp0(port,NULL)&&g_strcmp0(me_id,NULL)&&g_strcmp0(u_id,NULL)))
        gtk_widget_show (button);
//    gtk_container_add(GTK_CONTAINER (window),vbox);
    //entry=gtk_entry_new_with_max_length(50);
    //gtk_box_pack_start(GTK_BOX(vbox),entry,TRUE,TRUE,0);
    //gtk_widget_show(entry);
    button1=gtk_button_new_with_label("extra");
    gtk_box_pack_start(GTK_BOX(vbox),button1,TRUE,TRUE,0);
    gtk_widget_show(button1);
    gtk_widget_show(vbox);
    gtk_widget_show (window);
    //gtk_main_quit();
    //window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_widget_show(window2);
    gtk_main ();
    return(0);
}
void connect_server(GtkWidget *widget, struct args *data)
{
	//if (argc < 4){puts("error enter 4 arguments  \nip address\nport no.\nur name\nname to whom u want to chat\n"); exit(1);}
        //char ip[20];
        //strcpy(ip,argv[1]);
        //puts(ip);
        GtkWidget *window3;
        GtkWidget *label1,label2,label3;
	data->ip=gtk_entry_get_text(GTK_ENTRY (data->entry_ip));
	data->port=gtk_entry_get_text(GTK_ENTRY (data->entry_port));
	data->me_id=gtk_entry_get_text(GTK_ENTRY (data->entry_me));
	data->u_id=gtk_entry_get_text(GTK_ENTRY (data->entry_u));
//	window3= gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_signal_connect(GTK_OBJECT(window3),"delete_event",
//				GTK_SIGNAL_FUNC(gtk_widget_destroy),NULL);

	puts(data->ip);
	puts(data->port);
	puts(data->u_id);
	puts(data->me_id);
        int valid = ip_check(4,data->ip,data->port);
  //      if (!valid) exit(1);
        int port=atoi(data->port);
        int sockfd;
        //char msg[200];
        struct sockaddr_in server1;
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        if (sockfd==-1)
                printf("error in creating in socket\n");
	data->sockfd=sockfd;
        server1.sin_family=AF_INET;
        server1.sin_addr.s_addr = inet_addr(data->ip);
	printf("%d\n",server1.sin_addr.s_addr);
        server1.sin_port=htons(port);
	int con=-1;
        //if((con=connect(sockfd,(struct sockaddr *)&server ,sizeof(server)))<0);
          //      perror("connection error:");
	connect(sockfd,(struct sockaddr *)&server1,sizeof(struct sockaddr));
		perror("connection error:");
	//data->sockfd=sockfd;
	if (con < 0 || sockfd == -1 || (!valid))
        {
		window3 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		label1=gtk_label_new("\nXXXXXXXXXXXXXXXXXXXX\n\nerror in socket forming         \n     connection error        \nXXXXXXXXXXXXXXXXXXXXXXXX\n\n\n\n");
		//gtk_widget_show(label1);
		//gtk_widget_show(window3);
		gtk_signal_connect (GTK_OBJECT (window3), "delete_event",
                        GTK_SIGNAL_FUNC (destroy), NULL);
		gtk_container_add(GTK_CONTAINER(window3),label1);
		gtk_widget_show(label1);
                gtk_widget_show(window3);
		//exit(1);
	}
//        puts("connected\n");
//	data->sockfd=sockfd;
	else
	{
		talk(sockfd,data);
	}
}
