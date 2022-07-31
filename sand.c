// Sand Simulator
// Classifier System Based

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// RNG Functions
#define seed()          ( srand( time( NULL ) ) )
#define getSRand()      ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

#define NROWS 35
#define NCOLS 90

char canvas[ NROWS ][ NCOLS ];

typedef struct
{
    char pattern[6];
    char output[6];
    double probability;
} rules_t;

rules_t translations[]=
{
   { "..."
     "...",
     "..."
     "...",
     1.0 },

   { ".#."
     "...",
     "..."
     ".#.",
     1.0 },

   { ".#."
     "..#",
     "..."
     ".##",
     1.0 },

   { ".#."
     ".#.",
     "..."
     "##.",
     0.1 },

   { ".#."
     ".#.",
     "..."
     ".##",
     0.1 },

   { ".#."
     ".##",
     "..."
     "###",
     0.1 },

   { ".#."
     "#..",
     "..."
     "##.",
     1.0 },

   { ".#."
     "#.#",
     "..."
     "###",
     1.0 },

   { ".#."
     "##.",
     "..."
     "###",
     0.1 },

   { ".##"
     "...",
     "..#"
     ".#.",
     1.0 },

   { ".##"
     "..#",
     "..#"
     ".##",
     1.0 },

   { ".##"
     ".#.",
     "..#"
     "##.",
     0.1 },

   { ".##"
     ".#.",
     "..#"
     ".##",
     0.1 },

   { ".##"
     ".##",
     "..#"
     "###",
     0.1 },

   { ".##"
     "#..",
     "..#"
     "##.",
     1.0 },

   { ".##"
     "#.#",
     "..#"
     "###",
     1.0 },

   { ".##"
     "##.",
     "..#"
     "###",
     0.1 },

   { ".##"
     "##.",
     ".#."
     "###",
     0.1 },

   { "##."
     "...",
     "#.."
     ".#.",
     1.0 },

   { "##."
     "..#",
     "#.."
     ".##",
     1.0 },

   { "##."
     ".#.",
     "#.."
     "##.",
     0.1 },

   { "##."
     ".#.",
     "#.."
     ".##",
     0.1 },

   { "##."
     ".##",
     "#.."
     "###",
     0.1 },

   { "##."
     "#..",
     "#.."
     "##.",
     1.0 },

   { "##."
     "#.#",
     "#.."
     "###",
     1.0 },

   { "##."
     "##.",
     "#.."
     "###",
     0.1 },

   { "###"
     "...",
     "#.#"
     ".#.",
     1.0 },

   { "###"
     "..#",
     "# #"
     ".##",
     1.0 },

   { "###"
     ".#.",
     "#.#"
     "##.",
     0.1 },

   { "###"
     ".#.",
     "# #"
     ".##",
     0.1 },

   { "###"
     ".##",
     "#.#"
     "###",
     0.1 },

   { "###"
     "#..",
     "#.#"
     "##.",
     1.0 },

   { "###"
     "#.#",
     "#.#"
     "###",
      1.0 },

   { "###"
     "##.",
     "##."
     "###",
     1.0 }
};


void print_canvas( void )
{
   for ( int rows = 0 ; rows < NROWS ; rows++ )
   {
      for ( int cols = 0 ; cols < NCOLS ; cols++ )
      {
         printf( "%c", canvas[ rows ][ cols ] );
      }
      printf("\n");
   }
   printf("\n");


   struct timespec timer;
   timer.tv_sec = 0;
   timer.tv_nsec = 100000000;

   nanosleep( &timer, NULL );

   return;
}

void drop_sand( void )
{
#if 0
    // Populate top
    for ( int i = 0 ; i < NCOLS ; i++ )
    {
        if ( getSRand() > 0.995 ) canvas[ 0 ][ i ] = '#';
        else canvas[ 0 ][ i ] = '.';
    }
#else
    if ( getSRand() > 0.7 ) canvas[ 0 ][ 25 ] = '#';
    if ( getSRand() > 0.1 ) canvas[ 0 ][ 40 ] = '#';
    if ( getSRand() > 0.6 ) canvas[ 0 ][ 55 ] = '#';
#endif

    return;
}

int get_cell( int row, int col )
{
  if ( ( row < 0 ) || ( row > NROWS-1 ) ||
       ( col < 0 ) || ( col > NCOLS-1 ) )
  {
    return 1;
  }

  return ( canvas[ row ][ col ] == '#' ) ? 1 : 0;
}

void put_cell( int row, int col, int val )
{
  if ( ( row < 0 ) || ( row > NROWS-1 ) ||
       ( col < 0 ) || ( col > NCOLS-1 ) )
  {
    return;
  }

  if ( val )
  {
    canvas[ row ][ col ] = '#';
  }
  else
  {
    canvas[ row ][ col ] = '.';
  }

}


int xlate( char x )
{
   return ( x == '#' ) ? 1 : 0;
}


int find_pattern( int grain )
{
   int result = -1;

   for ( int i = 0 ; i < ( sizeof( translations ) / sizeof( rules_t ) ) ; i++ )
   {
      if ( ( xlate(translations[ i ].pattern[0]) == ( ( grain >> 0 ) & 0x1 ) ) &&
           ( xlate(translations[ i ].pattern[1]) == ( ( grain >> 1 ) & 0x1 ) ) &&
           ( xlate(translations[ i ].pattern[2]) == ( ( grain >> 2 ) & 0x1 ) ) &&
           ( xlate(translations[ i ].pattern[3]) == ( ( grain >> 3 ) & 0x1 ) ) &&
           ( xlate(translations[ i ].pattern[4]) == ( ( grain >> 4 ) & 0x1 ) ) &&
           ( xlate(translations[ i ].pattern[5]) == ( ( grain >> 5 ) & 0x1 ) ) )
      {
          if ( getSRand() < translations[ i ].probability )
          {
             result  = xlate(translations[ i ].output[ 0 ]) << 0;
             result |= xlate(translations[ i ].output[ 1 ]) << 1;
             result |= xlate(translations[ i ].output[ 2 ]) << 2;
             result |= xlate(translations[ i ].output[ 3 ]) << 3;
             result |= xlate(translations[ i ].output[ 4 ]) << 4;
             result |= xlate(translations[ i ].output[ 5 ]) << 5;
             break;
          }
      
      }

   }

   return result;
}


void simulate_sand( void )
{
    for ( int rows = NROWS-2 ; rows >= 0 ; rows-- )
    {
        for ( int cols = 0 ; cols < NCOLS ; cols++ )
        {
            int grain = 
                 ( get_cell( rows+0, cols-1 ) << 0 ) |
                 ( get_cell( rows+0, cols+0 ) << 1 ) |
                 ( get_cell( rows+0, cols+1 ) << 2 ) |
                 ( get_cell( rows+1, cols-1 ) << 3 ) |
                 ( get_cell( rows+1, cols+0 ) << 4 ) |
                 ( get_cell( rows+1, cols+1 ) << 5 );

            int result = find_pattern( grain );
            if ( result != -1 )
            {
               put_cell( rows+0, cols-1, ( ( result & 0x01 ) >> 0 ) );
               put_cell( rows+0, cols+0, ( ( result & 0x02 ) >> 1 ) );
               put_cell( rows+0, cols+1, ( ( result & 0x04 ) >> 2 ) );
               put_cell( rows+1, cols-1, ( ( result & 0x08 ) >> 3 ) );
               put_cell( rows+1, cols+0, ( ( result & 0x10 ) >> 4 ) );
               put_cell( rows+1, cols+1, ( ( result & 0x20 ) >> 5 ) );
            }
        }
    }

    return;
}

void main( void )
{
   seed();

   memset( canvas, '.', sizeof(canvas) );

   for ( int i = 0 ; i < 800 ; i++ )
   {
      if ( i < 450 ) drop_sand();
      simulate_sand();
      print_canvas();
   }

   return;
}
