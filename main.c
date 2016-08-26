#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define rConfigPath ".config/remindme"
#define rConfigFile "configuration.conf"

int main () {
  char *homedir = getenv("HOME");
  char *configFolder = malloc(strlen(homedir) + strlen(rConfigPath));
  snprintf(configFolder, strlen(homedir) + strlen(rConfigPath) + 2, "%s/%s", homedir, rConfigPath);
  char *configFile = malloc(strlen(configFolder) + strlen(rConfigFile));
  snprintf(configFile, strlen(configFolder) + strlen(rConfigFile) + 2, "%s/%s", configFolder, rConfigFile);

  // Check paths
  printf("home: %s\n", homedir);
  printf("conf: %s\n", configFolder);
  printf("file: %s\n", configFile);

  struct stat st = {0};
  if (stat(configFolder, &st) == -1) {
    printf("INFO: Configuration folder doesnt exists yet, creating\n");
    mkdir(configFolder, 0700);
  }

  FILE *stack = fopen(configFile, "r+"); 
  if (stack == NULL) {
    printf("ERROR: Configuration file in %s can't be opened\n", configFile);
    return -1;
  }
  char *buffer = NULL;
  ssize_t bufferl;
  /*  */
  /* fread(&buffer, sizeof(stack), 1, stack); */
  /* printf("file is %s\n", buffer); */
  
  getdelim(&buffer, &bufferl, '\n', stack);
  /* buffer = realloc(buffer, (int)bufferl - 1); */
  printf("Read %s from file\n", buffer);
  free(buffer);

  free(configFolder);
  free(configFile);
  fclose(stack);
  return 1;
}
