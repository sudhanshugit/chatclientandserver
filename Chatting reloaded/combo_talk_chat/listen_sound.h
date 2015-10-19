
/*

This example reads standard from input and writes
to the default PCM device for 5 seconds of data.

*/

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API
#define MYPORT "3228"
#include <alsa/asoundlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/stat.h>

void *listen_sound(void *abc) {
  int *talkfd= (int *)abc;
  int sockfd=*talkfd;
  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params;
  unsigned int val;
  int dir;
  snd_pcm_uframes_t frames;
  char *buffer;

/****************network part to add into it**********************************/
/*	int sockfd,status;// to get socket and status of getaddrinfo....
        struct addrinfo hints; // to set up things in advance
        struct addrinfo *server_info; // to put in the server information
        struct sockaddr_storage their_addr;
        socklen_t addr_size;
        memset(&hints,0,sizeof(hints));
        hints.ai_family=AF_UNSPEC;
        hints.ai_socktype= SOCK_STREAM;
        hints.ai_flags=AI_PASSIVE;
	if ((status=getaddrinfo(NULL,MYPORT,&hints,&server_info)) !=0)
        {
                perror("getaddrinfo error :");
                exit(1);
        }
	 sockfd= socket(server_info->ai_family,server_info->ai_socktype,server_info->ai_protocol);
        if (sockfd<0) perror("socket error::");
        int bind_status;//gettint the bind status
        bind_status=bind(sockfd,server_info->ai_addr,server_info->ai_addrlen);
        if (bind_status==-1)
                {perror("bind failed :");}
        else    puts ("bind done\n");
        if (listen(sockfd,1)<0)
                printf ("the listening failed\n");
        puts("waiting for incoming connection...\n");
        int sin_size= sizeof(their_addr);
	int newfd;
	if ((newfd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1)
        {
                 perror ("not accepted");
                 //continue;
		 exit(1);
        }*/

/***********************NETWORK PART ENDS HERE************************/

  /* Open PCM device for playback. */
  rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_PLAYBACK, 0);
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
  snd_pcm_hw_params_get_period_size(params, &frames,
                                    &dir);
  size = frames * 4; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size);

  /* We want to loop for 5 seconds */
  snd_pcm_hw_params_get_period_time(params,
                                    &val, &dir);
  /* 5 seconds in microseconds divided by
   * period time */
  loops = 5000000 / val;
 /* int fd=open("./rec1",O_WRONLY);
	if (fd==-1) {
		perror("open file :");
	}*/
  int err;
  while (1) {
    loops--;
    rc = read(sockfd, buffer, size);
//    puts(buffer);
   // err=write (fd,buffer,size);
	if (err==-1) perror("write into the file");
    if (rc == 0) {
      fprintf(stderr, "end of file on input\n");
      break;
    } else if (rc != size) {
      fprintf(stderr,
              "short read: read %d bytes\n", rc);
    }
    rc = snd_pcm_writei(handle, buffer, frames);
    if (rc == -EPIPE) {
      /* EPIPE means underrun */
      fprintf(stderr, "underrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc < 0) {
      fprintf(stderr,
              "error from writei: %s\n",
              snd_strerror(rc));
    }  else if (rc != (int)frames) {
      fprintf(stderr,
              "short write, write %d frames\n", rc);
    }
  }

  snd_pcm_drain(handle);
  snd_pcm_close(handle);
  free(buffer);

  return 0;
}

