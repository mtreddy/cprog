#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void
die( char *msg ) {
    perror( msg );
    exit( EXIT_FAILURE );
}

int
main( void )
{
    size_t len;
    size_t len1;
    FILE *f;
    FILE *f1;
    int c;
    char *buf;
    char *buf1;
    char *cmd = "md5sum /nvram.data";
    char *cmd1 = "md5sum /nvram.copy";
    char *path = "/tmp/output"; /* Should really use mkstemp() */
    char *path1 = "/tmp/output1"; /* Should really use mkstemp() */
    char str[50];
    char str1[50];

    len = (size_t) snprintf( buf, 0,  "%s > %s", cmd, path ) + 1;
    buf = (char *)malloc( len );
    if( buf == NULL ) die( "malloc");
    len1 = (size_t) snprintf( buf1, 0,  "%s > %s", cmd1, path1 ) + 1;
    buf1 = (char *)malloc( len1 );
    if( buf1 == NULL ) die( "malloc");

    snprintf( buf, len, "%s > %s", cmd, path );
    if( system( buf )) die( buf );
    f = fopen( path, "r" );
    if( f == NULL ) die( path );
    printf( "output of command: %s\n", buf );
    snprintf( buf1, len1, "%s > %s", cmd1, path1 );
    if( system( buf1 )) die( buf1 );
    f1 = fopen( path1, "r" );
    if( f1 == NULL ) die( path1 );
    int i = 0;
    while((( c = getc( f )) != EOF ) && (c != ' ')) {
        str[i] = c;
        fputc( c, stdout );
        i++;
    }
    printf("\n");
    str[i++] = '\0';
    i = 0;
    while((( c = getc( f1 )) != EOF ) && (c != ' ')) {
        fputc( c, stdout );
        str1[i] = c;
        i++;
    }
    str1[i++] = '\0';
  
    printf("\n");
    if(strcmp(str, str1) != 0)
        printf("Doesn't match test failed\n");
    else
        printf(" Successfull Test Passed\n");

    
    return EXIT_SUCCESS;
    fclose(f);
    fclose(f1);
    free(buf);
    free(buf1);
}
