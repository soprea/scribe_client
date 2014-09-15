#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <string.h>
#include </root/sandbox/c/scribe_client/test/arduino-serial-lib-daemon.h>
#include </root/sandbox/c/scribe_client/scribe/scribe_utils.h>

#define DAEMON_NAME "arduino-serial-daemon-nosql"

const int buf_max = 32;
char buf[50], buff_time[50];
FILE *fp;
struct tm *sTm;
    int fd = -1;
    int baudrate = 115200;  /* default */
    char serialport[]="/dev/ttyACM0";
    char eolchar = '\n'; /* Char used by arduino to signal the end of data */
    int timeout = 5000;
void process(){

/* End Variables */
/* Write to out.txt and put the timestamp */
    time_t now = time (0);
    sTm = localtime (&now);
    strftime (buff_time, sizeof(buff_time), "%z %Y-%m-%d %A %H:%M:%S", sTm);
    fp = fopen("out.txt","a"); /* Open file in append monde */
    fprintf(fp, "%s Read string: %s", buff_time, buf); /* Write ouput in file */
    fclose(fp);/* Close file */

/* Send to scribe attempt */
  //system("/root/sandbox/c/arduino-serial-daemon/scribe_client localhost 1463 buckettest arduino_test");
   char * scribe_logs = malloc(strlen(buff_time) + strlen(buf) + 2);
    strcpy(scribe_logs, buff_time);
    strcat(scribe_logs, " ");
    strcat(scribe_logs, buf);
   int  status = scribe_send_msg("127.0.0.1", 1455, "buckettest", scribe_logs);
    if (status != 0) { syslog(LOG_ERR, "Scribe not reachable");
      exit(EXIT_FAILURE); /* In case mysql server is not reachable */
          }
   free(scribe_logs);
}

int main(int argc, char *argv[]) {
    syslog(LOG_NOTICE, "Entering Daemon");
    syslog (LOG_INFO, "Program started by User %d", getuid ());
    pid_t pid, sid;
    pid = fork(); /* Fork the Parent Process */
    if (pid < 0) { syslog(LOG_ERR, "Can not create a new PID for our child process");}
    if (pid > 0) { exit(EXIT_SUCCESS); } /* We got a good pid, Close the Parent Process */
    umask(0); /* Change File Mask */
    sid = setsid(); /* Create a new Signature Id for our child */
    if (sid < 0) { syslog(LOG_ERR, "Can not create a new SID on child process");}
    if ((chdir("/")) < 0) { syslog(LOG_ERR, "Can not change directory on child process");}
    /* Close Standard File Descriptors: */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

  //-------------------------------
  // From here starts my program //
  //-------------------------------

    fd = serialport_init(serialport, baudrate);
    if (fd == -1) {
      syslog(LOG_ERR, "Serial port not opened %s\n", serialport);
      exit(EXIT_FAILURE); /* Serial port could not be opened */
	}
      syslog(LOG_INFO, "Serial port opened %s\n",serialport);

    //----------------
    // Main Process //
    //----------------

while(1){
      memset(buf,0,buf_max);
      serialport_read_until(fd, buf, eolchar, buf_max, timeout);
      process();    /* Run the Process */
      usleep(50000);    /* Sleep for a while */
	}
}
