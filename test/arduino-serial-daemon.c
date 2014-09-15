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
#include <mysql/mysql.h>

#define DAEMON_NAME "arduino-serial-daemon"

void process(){

  const int buf_max = 32;
  char buf;
  FILE *fp, *fpr;
  const int buf_string_max = 256;
  int fd = -1;
  char db_buf[buf_string_max], buf_db[buf_string_max];
  const char delimiters[] = "C F#%";
  char *token1, *token2, *cp, buff_time[50];
  struct tm *sTm;
  memset(buf,0,buf_max);

  MYSQL *conn;
  const char *server = "localhost";
  const char *user = "test";
  const char *password = "test";
  const char *database = "pihome";
/* End Variables */
/* Read from file*/
fpr = fopen("scribe_log",r);
//Read from file
fclose(fpr);

/* Write to out.txt and put the timestamp */

    time_t now = time (0);
    sTm = localtime (&now);
    strftime (buff_time, sizeof(buff_time), "%z %Y-%m-%d %A %H:%M:%S", sTm);
    fp = fopen("out.txt","a"); /* Open file in append monde */
    fprintf(fp, "%s Read string: %s", buff_time, buf); /* Write ouput in file */
    fclose(fp);/* Close file */

/* Send to mysql */

  sscanf(buf, "%s", buf_db);
  token1 = strtok (buf_db, delimiters);
  token2 = strtok (NULL, delimiters);

  conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
      syslog(LOG_ERR, "%s", mysql_error(conn));
      exit(EXIT_FAILURE); /* In case mysql server is not reachable */
	  }
    sprintf(db_buf, "update pi_devices set status='%s' where code='%s';", token1, token2); /* Puts entire query in a string */
    if (mysql_query(conn, db_buf)) { // send SQL query 
      syslog(LOG_ERR, "%s", mysql_error(conn));
      exit(EXIT_FAILURE); /* In case of MySQL sent query failure, close connection */
	  }
    syslog(LOG_INFO, "MySQL sent query: %s", db_buf); 
    mysql_close(conn); /* Close MySQL Connection */

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

while(1){
      process();    /* Run the Process */
      usleep(2);    /* Sleep for a while */
	}
}
