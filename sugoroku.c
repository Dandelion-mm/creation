#include <stdio.h>
#include	<stdlib.h>
#include	<time.h>

int ThrowDices( int n )
{
    int i;
    int	 sum = 0;

    for( i = 0 ; i < n ; i++ )
        sum += ( ( rand() % 3 ) + 1 );

    return sum;
}

void ShowBoard( int pos )
{
    int	i;

    for( i = 0 ; i < pos ; i++ )
        printf( "_ " );

        printf( "▲" );

    for( i = pos + 1 ; i < 30 ; i++ )
        printf( "_ " );

    printf( "|上がり！\n" );
}

int main (void)
{
    int	 reply;

    srand( (unsigned int)time( 0 ) );

    printf( "▲すごろく▼\n" );
    printf( "30マス先にゴールがあります。\n" );
    printf( "1,2,3の３つの目を持つ特別なサイコロ10個を、好きな数だけ振って駒を進めます。\n" );
    printf( "ぴったり上がりに止まれば終わりです。目の数が多ければ、余った目の数だけ戻ります。\n" );
    printf( "----------------------------------------------\n" );

    do
    {
        int	turn;
        int	position = 0;

        ShowBoard( position );

        for( turn = 1 ; ; turn++ )
        {
            int	n;
            int	me;

            while( 1 )
            {
                printf( "残り%dマスです。サイコロの数は？", 30 - position );
                scanf( "%d", &n );
                
                if( n <= 10 )
                    break;
                else
                    printf( "サイコロは10個までです。" );
            }

            me = ThrowDices( n );

            printf( "出た目の合計 %d\n", me );

            position += me;

            if( position == 30 )
            {
                printf( "おめでとう！！ %d回目で上がりです\n", turn );
                break;
            }

            if( position > 30 )
                position = 30 - ( position - 30 );

            ShowBoard( position );
        }

        printf( "もう一度やりますか？（Yes:1 No:0）" );
        scanf( "%d", &reply );

    }while( reply !=0 );
}