#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

void usage(){
   printf("\n./webhdfsTest hostname port command\n");
}

int main(int argc, char *argv[]) {

   // usage should be
   // ./webhdfsTest hostname port command
   if ( argc != 4 ) {
       printf("\nNot enough arguments were passed: %d in\n", argc);
       usage();
       exit(1);
   }
   CURL *curl;
   CURLcode res;
   char *HOSTNAME = argv[1];
   char *PORT = argv[2];
   char *COMMAND = argv[3];
   char *HTTP_PREFIX = "http://";
   char *HTTP_COLON = ":";
   char *HTTP_SLASH = "/";
   int urlLenght = strlen(HTTP_PREFIX)+strlen(HOSTNAME)+strlen(HTTP_COLON)+strlen(PORT)+strlen(HTTP_SLASH)+strlen(COMMAND)+1; // add 1 and null termination

   curl = curl_easy_init();
   if (curl) {
       char *wUrl;
       wUrl = malloc(urlLenght);
       strcat(wUrl, HTTP_PREFIX); // "http://"
       strcat(wUrl, HOSTNAME); // "hdm1.phd.local"
       strcat(wUrl, HTTP_COLON); // ":"
       strcat(wUrl, PORT); // "50070"

       // handle if user adds a leading "/" to command string
       if (COMMAND[0] == '/') {
           strcat(wUrl, COMMAND); // "/webhdfs/v1/TESTDIR/rsasoc/v1/sessions/data/2014/5/17/15/27?user.name=gpadmin&op=MKDIRS&permission=777";"
       } else {
           strcat(wUrl, HTTP_SLASH); // "/"
           strcat(wUrl, COMMAND); // "webhdfs/v1/TESTDIR/rsasoc/v1/sessions/data/2014/5/17/15/27?user.name=gpadmin&op=MKDIRS&permission=777";"
       }

       printf("\nrunning http put: %s\n", wUrl);
       curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
       curl_easy_setopt(curl, CURLOPT_URL, wUrl);

       printf("\nResponse:\n");
           res = curl_easy_perform(curl);
       printf("\n\n"); // add a couple of new lines to make things pretty
       if (res != CURLE_OK) {
       fprintf(stderr, "curl_easy_perform() failed: %sn",curl_easy_strerror(res));
   }

   curl_easy_cleanup(curl);
 }
 return 0;
}
