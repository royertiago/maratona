/* fpdiff.c
 *
 * usage: fpdiff file1 file2 tolerance
 *
 * perform scanf file1 and file2 for floating-point numbers. If they differ by more
 * than tolerance, returns 1; otherwise, returns 0.
 *
 * Either file1 or file2 can be stdin.
 *
 * Other format data (nonnumeric characters) are compared for equality.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

FILE * open_file( const char * arg ) {
    if( strcmp(arg, "-") == 0 )
        return stdin;
    FILE * file = fopen( arg, "r" );
    if( file == NULL )
        printf( "Could not open file %s\n", arg );
    return file;
}

FILE * left_file, * right_file;

void close_files() {
    if( left_file ) fclose( left_file );
    if( right_file ) fclose( right_file );
}

int main( int argc, char * argv[] ) {
    left_file = right_file = NULL;
    atexit(close_files);
    if( argc != 4 ) {
        printf( "Usage: %s file1 file2 tolerance\n"
                "Either file can be '-', when stdin is read\n",
                argv[0] );
        return 2;
    }
    if( strcmp(argv[1], argv[2]) == 0 )
        return 0;

    left_file = open_file( argv[1] );
    right_file = open_file( argv[2] );

    if( !left_file || !right_file )
        return 2;

    long double ldouble, rdouble;
    long double tolerance;
    sscanf( argv[3], "%Lf", &tolerance );

    while( 1 ) {
        int l = fscanf( left_file, "%Lf", &ldouble );
        int r = fscanf( right_file, "%Lf", &rdouble );
        if( l == EOF || r == EOF ) {
            if( l != EOF || r != EOF )
                return 1;
            else
                return 0;
        }
        if( l == 0 || r == 0 ) {
            if( l != 0 || r != 0 )
                return 1;
            l = fgetc( left_file );
            r = fgetc( right_file );
            if( l != r ) return 1;
            continue;
        }
        if( fabs(ldouble - rdouble) > tolerance )
            return 1;
    }

    return 2; /* Should never reach here */
}
