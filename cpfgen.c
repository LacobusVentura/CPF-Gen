/*!
	\file cpfgen.c
	\brief Gerador de CPFs validos aleatorios
	\author Tiago Ventura (tiago.ventura@gmail.com)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_BUF_LEN (32)

static int g_formated_output = 0;
static int g_sample_count = 1;


static void syntax( int argc, char ** argv )
{
	printf( "Sintaxe:\n\tcpfgen [-n qtd] [-f]\n\n", argv[0] );
	exit(1);
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
				g_sample_count = atoi( argv[ i + 1 ] );
			}
			else
			{
				syntax( argc, argv );
			}
		}
		else if( !strcmp( "-f", argv[i] ) )
		{
			g_formated_output = 1;
		}
		else
		{
			syntax( argc, argv );
		}
	}
}


static const char * format( char * cpf )
{
	char aux[ MAX_BUF_LEN + 1 ] = {0};

	snprintf( aux, MAX_BUF_LEN, "%c%c%c.%c%c%c.%c%c%c-%c%c", cpf[0], cpf[1], cpf[2],
															cpf[3], cpf[4], cpf[5],
															cpf[6], cpf[7], cpf[8],
															cpf[9], cpf[10] );
	strncpy( cpf, aux, MAX_BUF_LEN );

	return cpf;
}


static const char * generate( char * buf, int fmtd )
{
	int a = 0;
	int b = 0;
	int c = 0;
	int sum = 0;
	int i = 0;
	int res = 0;
	int n = 0;
	char cpf[ MAX_BUF_LEN + 1 ] = {0};


	do {
		a = rand() % 1000;
		b = rand() % 1000;
		c = rand() % 1000;
	} while( (a == b) && (a == c) );

	snprintf( cpf, MAX_BUF_LEN, "%03d%03d%03d00", a, b, c );

	for( i = 0; i < 9; i++ )
	{
		n = cpf[i] - 48;
		sum += (n * (10 - i));
	}

	res = 11 - (sum % 11);

	if( (res != 10) && (res != 11) )
		cpf[9] = res + 48;

	sum = 0;

	for( i = 0; i < 10; i++ )
	{
		n = cpf[i] - 48;
		sum += n * (11 - i);
	}

	res = 11 - (sum % 11);

	if( (res != 10) && (res != 11) )
		cpf[10] = res + 48;

	cpf[11] = '\0';

	strncpy( buf, cpf, MAX_BUF_LEN );

	if(fmtd)
		format(buf);

	return buf;
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
