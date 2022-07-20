#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// RNG Functions
#define seed()          ( srand( time( NULL ) ) )
#define getSRand()      ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )

#define NROWS 40
#define NCOLS 60

char canvas[ NROWS ][ NCOLS ];

typedef struct
{
    char pattern[7];
    char output[7];
    double probability;
} rules_t;

rules_t translations[]=
{
#if 0
   { "..."
     "...", 
     "..." 
     "...", 
     1.0 },

   { "..."
     "..#",
     "..."
     "..#",
     1.0 },

   { "..."
     ".#.",
     "..."
     ".#.",
     1.0 },

   { "..."
     ".##",
     "..."
     ".##",
     1.0 },

   { "..."
     "#..",
     "..."
     "#...",
     1.0 },

   { "..."
     "#.#",
     "..."
     "#.#",
     1.0 },

   { "..."
     "##.",
     "..."
     "##.",
     1.0 },

   { "..."
     "###",
     "..."
     "###",
     1.0 },

   { "..#"
     "...",
     "..."
     "..#",
     1.0 },

   { "..#"
     "..#",
     "..#"
     "..#",
     1.0 },

   { "..#"
     ".#.",
     "..#"
     ".#.",
     1.0 },

   { "..#"
     ".##",
     "..#"
     ".##",
     1.0 },

   { "..#"
     "#..",
     "..#"
     "#..",
     1.0 },

   { "..#"
     "# #",
     "..#"
     "# #",
     1.0 },

   { "..#"
     "##."
     1.0 },

   { "..#"
     "###",
     "..#"
     "###",
     1.0 },
#endif

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
     ".##",
     "..."
     "###",
     1.0 },

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
     1.0 },

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
     0.5 },
   { ".##"
     ".#.",
     "..#"
     ".##",
     1.0 },

   { ".##"
     ".##",
     "..#"
     "###",
     1.0 },

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
     1.0 },

   { "##."
     "...",
     "#.."
     ".#.",
     1.0 },

   { "##."
     "..#"
     "#..",
     ".##",
     1.0 },

   { "##."
     ".#.",
     "#.."
     "##."
     0.5 },
   { "##."
     ".#.",
     "#.."
     ".##"
     1.0 },

   { "##."
     ".##",
     "#.."
     "###"
     1.0 },

   { "##."
     "#..",
     "#.."
     "##."
     1.0 },

   { "##."
     "#.#",
     "#.."
     "###",
     1.0 },

   { "###"
     "..."
     "#.#"
     ".#.",
     1.0 },

   { "###"
     "..#"
   { "###"
     ".#."
   { "###"
     ".##"
   { "###"
     "#.."
   { "###"
     "#.#"

   { "###"
     "##.",
     "##."
     "###",
     1.0 },







}

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

   return;
}

void drop_sand( void )
{
    // Populate top
    for ( int i = 0 ; i < NCOLS ; i++ )
    {
        if ( getSRand() > 0.8 ) canvas[ 0 ][ i ] = '#';
    }

    return;
}

void simulate_grain( int rows, int cols )
{
   int rule;

   rule = find_rule( rows, cols )



}

void simulate_sand( void )
{
    for ( rows = NROWS -2 ; rows > 0 ; rows -=2 )
    {
        for ( cols = 0 ; cols < NCOLS ; cols++ )
        {
            simulate_grain( rows, cols );
           
            int grain = 
                 ( canvas[ rows+0 ][ cols+0 ] << 0 )
                 ( canvas[ rows+0 ][ cols+1 ] << 1 )
                 ( canvas[ rows+0 ][ cols+2 ] << 2 )
                 ( canvas[ rows+1 ][ cols+0 ] << 3 )
                 ( canvas[ rows+1 ][ cols+1 ] << 4 )
                 ( canvas[ rows+1 ][ cols+2 ] << 5 );

        }
    }

    return;
}

void main( void )
{
   memset( canvas, '.', sizeof(canvas) );

//   while (1)
   {
      drop_sand();
      print_canvas();
      simulate_sand();
   }

   return;
}
