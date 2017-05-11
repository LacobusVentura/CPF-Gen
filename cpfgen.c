/*!
	\file cpfgen.c
	\brief Gerador de CPFs validos aleatorios
	\author Tiago Ventura (tiago.ventura@gmail.com)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_BUF_LEN (16)

static int g_formated_output = 0;
static unsigned long g_sample_count = 1;


static void show_syntax( int argc, char ** argv )
{
	printf( "Sintaxe:\n\t%s [-n qtd] [-f]\n\n", argv[0] );
}


static void initialize( int argc, char ** argv )
{
	int i = 0;

	srand(time(NULL));

	if( argc <= 1 )
		return;

	for( i = 1; i < argc; i++ )
	{
		if( !strcmp( "-n", argv[ i ] ) )
		{
			i++;

			if( i < argc )
			{
				g_sample_count = atol(argv[i]);
			}
			else
			{
				show_syntax( argc, argv );
				exit(1);
			}
		}
		else if( !strcmp( "-f", argv[i] ) )
		{
			g_formated_output = 1;
		}
		else
		{
			show_syntax( argc, argv );
			exit(1);
		}
	}
}


static int check( const char * cpf )
{
	int i = 0;

	for( i = 1; i < 9; i++ )
		if( cpf[i] != cpf[i-1] )
			return 1;

	return 0;
}


static const char * generate( char * cpf, int fmtd )
{
	int a = 0;
	int b = 0;
	int c = 0;
	int sum = 0;
	int i = 0;
	int res = 0;
	int n = 0;
	int ok = 0;
	int dv = 0;
	char buf[ MAX_BUF_LEN + 1 ] = {0};


	while(!ok)
	{
		a = rand() % 1000;
		b = rand() % 1000;
		c = rand() % 1000;

		snprintf( buf, MAX_BUF_LEN, "%03d%03d%03d", a, b, c );

		ok = check( buf );
	}

	for( i = 0; i < 9; i++ )
	{
		n = buf[i] - 48;
		sum += (n * (10 - i));
	}

	res = 11 - (sum % 11);

	if( res < 10 )
	{
		buf[9] = res + 48;
		dv = res * 10;
	}

	sum = 0;

	for( i = 0; i < 10; i++ )
	{
		n = buf[i] - 48;
		sum += n * (11 - i);
	}

	res = 11 - (sum % 11);

	if( res < 10 )
		dv += res;

	if( fmtd )
	{
		snprintf( cpf, MAX_BUF_LEN, "%03d.%03d.%03d-%02d", a, b, c, dv );
	}
	else
	{
		snprintf( cpf, MAX_BUF_LEN, "%03d%03d%03d%02d", a, b, c, dv );
	}

	return cpf;
}


int main( int argc, char ** argv )
{
	int i = 0;
	char buf[ MAX_BUF_LEN + 1 ] = {0};

	initialize( argc, argv );

	for( i = 0; i < g_sample_count; i++ )
		fprintf( stdout, "%s\n", generate( buf, g_formated_output ) );

	return 0;
}

/* eof */
