#include <glib.h>
#include <glib/gprintf.h>
#include <pthread.h> // thread creation :)
#include <gtk/gtk.h>  // gui :)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "ip_check.h"
struct args
{
 gchar *ip;
 gchar *port;
 gchar *u_id;
 gchar *me_id;
 gchar *msg_r;
 gchar *msg_s;
 gchar *u_id1;
 int sockfd;
 //int fd_chat;
 //int fd_gui;
 FILE* fd_chat,*fd_gui;
 GtkWidget *entry_ip,*entry_port,*entry_me,*entry_u,*entry1,*entry2;
};
void *connect_1(void *);
void sending_server(GtkWidget *widget,struct args *data)
{
	data->msg_s=gtk_entry_get_text(GTK_ENTRY(widget));
	send(data->sockfd,data->msg_s,200,0);
//	puts(data->msg_s);
	char msgs[210];
	strcpy(msgs,"me ::");
//	g_stpcpy(msgs,data->me_id);
//	puts(msgs); puts(data->me_id);
//	strcat(msgs,"  ::  ");
	strcat(data->msg_s,"\n");
	strcat(msgs,data->msg_s);
	//write(data->fd_gui,data->msg_s,200);
//	fwrite(data->msg_s,200,1,data->fd_gui);
//	send(data->sockfd,data->msg_s,200,0);
//	strcat(data->me_id,data->msg_s);
//	puts(data->me_id);
//	gtk_text_insert(GTK_TEXT(data->entry1),NULL,NULL,NULL,"me:: ",-1);
	GtkTextBuffer *buffer;
	GtkTextMark *mark;
	GtkTextIter iter;
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->entry1));
	mark=gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark(buffer,&iter,mark);
	gtk_text_buffer_insert(buffer,&iter,msgs,-1);
	//strcat(data->msg_s,"\n");
	//strcat()
	//gtk_text_insert(GTK_TEXT_VIEW(data->entry1),NULL,NULL,NULL,data->msg_s,-1);
	gtk_entry_set_text(GTK_ENTRY (widget),"");
}
void *print_inbox(void *abc)
{
	struct args *data=(struct args *)abc;
	puts("in print_inbox");
	char msgr[200];
	while(1)
	{
		recv(data->sockfd,msgr,200,0);
		puts("after recv");
		puts(msgr);
		char msgr_ex[200];
		strcpy(msgr_ex,data->u_id);
		puts(data->u_id);
		puts(msgr_ex);
		strcat(msgr,"\n");
		//strcat(msgr,"")
		if(strcmp(msgr,"exit")==0)
			break;
//	strcat(data->u_id,msgr);
//	puts(data->u_id);
	//gtk_text_insert(GTK_TEXT(data->entry1),NULL,NULL,NULL,data->u_id,-1);
	//strcat(msgr,"\n");
	//gtk_text_insert(GTK_TEXT(data->entry1),NULL,NULL,NULL,msgr,-1);
	GtkTextBuffer *buffer;
        GtkTextMark *mark;
        GtkTextIter iter;
        buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->entry1));
        mark=gtk_text_buffer_get_insert(buffer);
        gtk_text_buffer_get_iter_at_mark(buffer,&iter,mark);
        gtk_text_buffer_insert(buffer,&iter,msgr,-1);
	}

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
void talk(struct args *data)
{
    puts("step 1");
    //g_print ("Hello World\n");
    GtkWidget *window2;
    GtkWidget *button1;
    GtkWidget *table;
    GtkWidget *entry1,*entry2;
    GtkWidget *scroller;
    GtkWidget *label,*label2;
//    GtkWidget *view;
    GtkTextBuffer *buffer;
	
	
	
	pthread_t thread_id;
        pthread_create(&thread_id,NULL,&print_inbox,data);
//	puts("step 1");
//	pthread_create();
    window2=gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_signal_connect (GTK_OBJECT (window2), "destroy",
                      GTK_SIGNAL_FUNC (destroy), NULL);
    puts("step 2");
    gtk_container_set_border_width(GTK_CONTAINER(window2),20);
    table=gtk_table_new(15,15,TRUE);
    gtk_container_add(GTK_CONTAINER(window2),table);
    gtk_widget_show(table);
    gchar *server_msg;
//    if(recv(sockfd,server_msg,100,0))
    label2=gtk_label_new("**welcome to sudhanshu's chat client**");
    gtk_table_attach_defaults(GTK_TABLE(table),label2,0,15,0,1);
    gtk_widget_show(label2);
    //if(send(sockfd,data->u_id,50,0)<0);
    //            perror("send");
    //if(send(sockfd,data->me_id,50,0)<0);
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
    data->entry1 = gtk_text_view_new();
    GIOChannel *sfd;
	sfd=g_io_channel_unix_new(data->sockfd);
    //buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(entry1));
    //gtk_text_buffer_set_text(buffer,"helladfafd",-1);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(data->entry1),FALSE);
    gtk_text_view_get_wrap_mode(GTK_TEXT_VIEW(data->entry1));
//    g_io_add_watch(sfd,G_IO_IN,(GIOFunc)print_inbox,(struct args*)data);
        gchar msgr[200];
	 puts("step 3");
//        recv(data->sockfd,msgr,200,0);
//      strcat(data->u_id,msgr);
//      puts(data->u_id);
 //     gtk_text_insert(GTK_TEXT(data->entry1),NULL,NULL,NULL,msgr,-1);
	 puts("step 4");
    gtk_table_attach_defaults(GTK_TABLE(table),data->entry1,0,14,1,13);
    gtk_widget_show(data->entry1);
  /*******************lable***********************************************/
    label=gtk_label_new("enter text ::");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,2,13,14);
    gtk_widget_show(label);
  /*--------------------text area two------------------------------------*/
    data->entry2=gtk_entry_new_with_max_length(200);
    gtk_signal_connect(GTK_OBJECT(data->entry2),"activate",
				GTK_SIGNAL_FUNC(sending_server),
				(struct args *)data);
    gtk_table_attach_defaults(GTK_TABLE(table),data->entry2,2,15,13,14);
    gtk_widget_show(data->entry2);
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
    gtk_entry_set_text( GTK_ENTRY (user_input.entry_ip),"127.0.0.1");

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
   gtk_entry_set_text( GTK_ENTRY (user_input.entry_port),"12345");
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
   gtk_entry_set_text( GTK_ENTRY (user_input.entry_me),"sudhanshu");
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
    gtk_entry_set_text( GTK_ENTRY (user_input.entry_u),"kumar");
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
        GtkWidget *window3;
        GtkWidget *label1,label2,label3;
	data->ip=gtk_entry_get_text(GTK_ENTRY (data->entry_ip));
	data->port=gtk_entry_get_text(GTK_ENTRY (data->entry_port));
	data->me_id=gtk_entry_get_text(GTK_ENTRY (data->entry_me));
	data->u_id1=data->u_id=gtk_entry_get_text(GTK_ENTRY (data->entry_u));
	puts(data->u_id1);
//	window3= gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_signal_connect(GTK_OBJECT(window3),"delete_event",
//				GTK_SIGNAL_FUNC(gtk_widget_destroy),NULL);

//	puts(data->ip);
//	puts(data->port);
//	puts(data->u_id);
//	puts(data->me_id);
// creating a thread just because a single process cannot handle more than a //
// fixed number of file descriptors :) i am intelligent courtsy krishna //
	pthread_t thread_id;
	pthread_create(&thread_id,NULL,&connect_1,data);
	sleep(2);
	talk(data);
	pthread_join(thread_id,NULL);
/*
//	FILE *fd1,*fd2;
//	int asd=fork(); //just because a process can support a
			// ltd no. of file des.
//	if (asd==0)
	{
		mkfifo("./temp/gui_fifo",0777);
		puts("1\n");
		(data->fd_gui)=fopen("./temp/gui_fifo","w");
//		printf("%d\n",data->fd_gui);
		perror("file:");
		 puts("2\n");
		(data->fd_chat)=fopen("./temp/chat_fifo","r");
		 puts("3\n");
		fwrite(data->ip,100,1,data->fd_gui);
		 puts("4\n");
	        //write(data->fd_gui,data->port,100);
		fwrite(data->port,100,1,data->fd_gui);
		 puts("5\n");
	        //write(data->fd_gui,data->u_id,100);
		fwrite(data->me_id,100,1,data->fd_gui);
		 puts("6\n");
	        //write(data->fd_gui,data->me_id,100);
		fwrite(data->u_id,100,1,data->fd_gui);
		 puts("6\n");
		talk(data);
	}
*/
}
void *connect_1(void *data1)
{
	//if (argc < 4){puts("error enter ip and port no.\n your id and your freinds id\n as 4 args \n"); exit(1);}
	struct args* data=(struct args *)data1;
//	puts(data->ip);
  //      puts(data->port);
        puts(data->u_id);
        puts(data->me_id);
	FILE *fd1,*fd2;
//      int asd=fork(); //just because a process can support a
                        // ltd no. of file des.
//      if (asd==0)
/*        {
                mkfifo("./temp/gui_fifo",0777);
                puts("1\n");
                (data->fd_gui)=fopen("./temp/gui_fifo","w");
//              printf("%d\n",data->fd_gui);
                perror("file:");
                 puts("2\n");
                (data->fd_chat)=fopen("./temp/chat_fifo","r");
                 puts("3\n");
                fwrite(data->ip,200,1,data->fd_gui);
                 puts("4\n");
                //write(data->fd_gui,data->port,100);
                fwrite(data->port,200,1,data->fd_gui);
                 puts("5\n");
                //write(data->fd_gui,data->u_id,100);
                fwrite(data->me_id,200,1,data->fd_gui);
                 puts("6\n");
                //write(data->fd_gui,data->me_id,100);
                fwrite(data->u_id,200,1,data->fd_gui);
                 puts("6\n");
//                talk(data);
        }
*/

        char ip[20],ip1[20];
        strcpy(ip,data->ip);
	strcpy(ip1,data->ip);
        //puts("\n\n check post \n\n");puts(ip);
        int valid = ip_check(2,ip,data->port);
        if (!valid) exit(1);
        int port=atoi(data->port);
        int sockfd;
        char msg[200];
        struct sockaddr_in server1;
//        sockfd=socket(AF_INET,SOCK_STREAM,0);
//        if (sockfd==-1)

/////////                perror("error in creating in socket\n");
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	//printf("errno=%d\n",errno);
	int err=errno;
	perror("socket");
	printf("errno=%d\n",err);
        server1.sin_family=AF_INET;
	//puts("\n\n\n\n");puts(ip1);
        server1.sin_addr.s_addr = inet_addr(ip1);
        server1.sin_port=htons(port);
	memset(&(server1.sin_zero),'\0',8);
        connect(sockfd,(struct sockaddr *)&server1 ,sizeof(struct sockaddr));
		err=errno;
                perror("connection error\n");
		printf("errno=%d\n",err);////////////////////////////
// a diffrent way to connect :) :) :) :) :) :) :) :)//
/*	int status;
	struct addrinfo hints;
	struct addrinfo *res;
	memset(&hints,0,sizeof(hints));
	hints.ai_family=AF_INET;
	hints.ai_socktype =SOCK_STREAM;
	status= getaddrinfo(ip,data->port,&hints,&res);
	sockfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	perror("socket");
	res->ai_addr->sin_addr.s_addr=inet_addr(ip);
	connect(sockfd,res->ai_addr,res->ai_addrlen);
//	puts(res->ai_addr);
	perror ("connect");
//	puts(res->ai_addr);

//	 end of connect and socket//*/
        puts("connected\n");
        char msg_srvr[200];
        recv(sockfd,msg_srvr,200,0);
        puts(msg_srvr);
        send(sockfd,data->me_id,50,0);// my name
        send(sockfd,data->u_id,50,0);// my friend's name
	data->sockfd=sockfd;
	//GIOChannel *sfd;
	//sfd= g_io_channel_unix_new(sockfd);
//	g_io_add_watch(sfd,)
	int x;
//	x=fork();
//	if (x==0)
	{
//		puts("asdf");
//		char msgr[200];
//		while(1){
//		puts("step 5");
//		char msgr[200];
//		recv(sockfd,msgr,200,0);
//		puts("step 6");
//		puts(msgr);
//		GtkTextBuffer *buffer;
//		if (strcmp(msgr,"exit")==0);
//                        break;
//	        GtkTextMark *mark;
  //      	GtkTextIter iter;
//	        buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(data->entry1));
  //      	mark=gtk_text_buffer_get_insert(buffer);
//	        gtk_text_buffer_get_iter_at_mark(buffer,&iter,mark);
  //      	gtk_text_buffer_insert(buffer,&iter,msgr,-1);
		
	}
}
