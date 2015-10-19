// multiple chat client 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <alsa/asoundlib.h>
//#include "ip_check.h"
void *speak_sound(void *abc)
{
	int *talkfd=(int *)abc;
	int sockfd=*talkfd;
/************************for alsa initiations ******************/
	long loops;
  	int rc;
  	int size;
  	snd_pcm_t *handle;
  	snd_pcm_hw_params_t *params;
	unsigned int val;
	int dir;
	snd_pcm_uframes_t frames;
	char *buffer;
/***********************network initiation**********************/
/*	int port=atoi(argv[2]);
	int sockfd;
	char msg[200];
	struct sockaddr_in server;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd==-1)
		printf ("error in creating in socket\n");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port=htons(port);
	if (connect(sockfd,(struct sockaddr *)&server ,sizeof(server))<0)
		printf("connection error\n");
	puts("connected\n");
	int fd=open("/dev/urandom",O_RDONLY);
	if (fd == -1) printf("file error");
	char buf[200];
	int x;*/
/******************alsa work for pcm and device opening**********************/
	  /* Open PCM device for recording (capture). */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_CAPTURE, 0);
  if (rc < 0) {
    fprintf(stderr,
            "unable to open pcm device: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Allocate a hardware parameters object. */
  snd_pcm_hw_params_alloca(&params);

  /* Fill it in with default values. */
  snd_pcm_hw_params_any(handle, params);

  /* Set the desired hardware parameters. */

  /* Interleaved mode */
  snd_pcm_hw_params_set_access(handle, params,
                      SND_PCM_ACCESS_RW_INTERLEAVED);

  /* Signed 16-bit little-endian format */
  snd_pcm_hw_params_set_format(handle, params,
                              SND_PCM_FORMAT_S16_LE);

  /* Two channels (stereo) */
  snd_pcm_hw_params_set_channels(handle, params, 2);

  /* 44100 bits/second sampling rate (CD quality) */
  val = 4410;
  snd_pcm_hw_params_set_rate_near(handle, params,
                                  &val, &dir);

  /* Set period size to 32 frames. */
  frames = 32;
  snd_pcm_hw_params_set_period_size_near(handle,
                              params, &frames, &dir);

  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc < 0) {
    fprintf(stderr,
            "unable to set hw parameters: %s\n",
            snd_strerror(rc));
    exit(1);
  }

  /* Use a buffer large enough to hold one period */
  snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params,
                                         &val, &dir);
  loops = 5000000 / val;

  while (1) {
    //loops--;
    rc = snd_pcm_readi(handle, buffer, frames);
    if (rc == -EPIPE) {
      /* EPIPE means overrun */
      fprintf(stderr, "overrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      fprintf(stderr,
              "error from read: %s\n",
              snd_strerror(rc));
    } else if (rc != (int)frames) {
      fprintf(stderr, "short read, read %d frames\n", rc);
    }
    rc = send(sockfd, buffer, size,0);
    memset(buffer,'\0',size);
    if (rc != size)
      fprintf(stderr,
              "short write: wrote %d bytes\n", rc);
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);

/*	while(1){
		x=read(fd,buf,200);
		if(x==-1) perror("read :");
		puts(buf);
		x=send(sockfd,buf,200,0);
		if(x==-1) perror("send :");
		memset(buf,'\0',200);
	}
	puts("logging of chat\n");*/
//	if (x!=0)
//		kill(x,SIGTERM);
	close(sockfd);
	return 0;
}

