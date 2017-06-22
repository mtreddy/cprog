#include <stdlib.h>
#include <stdio.h>
void
die( char *msg ) {
    perror( msg );
    exit( EXIT_FAILURE );
}

int
main( void )
{
    size_t len;
    FILE *f;
    int c;
    char *buf;
    char *cmd = "rdmsr -p 0 0x19c";
    char *path = "/tmp/output"; /* Should really use mkstemp() */

    len = (size_t) snprintf( buf, 0,  "%s > %s", cmd, path ) + 1;
    buf = (char *)malloc( len );
    if( buf == NULL ) die( "malloc");
    snprintf( buf, len, "%s > %s", cmd, path );
    if( system( buf )) die( buf );
    f = fopen( path, "r" );
    if( f == NULL ) die( path );
    printf( "output of command: %s\n", buf );
    while(( c = getc( f )) != EOF )
        fputc( c, stdout );
    return EXIT_SUCCESS;
}
