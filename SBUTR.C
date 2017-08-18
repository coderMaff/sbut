#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main(int argc, char **argv)
{
    div_t   answ;
    time_t  ntime;
    FILE    *fp;
    char    o = 0;
    char    p = 5;
    char    x = 1;
    char    y = 1;

    printf("\nsbutr is buggering explorer.exe [by maff in 97]\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    if ( argc<2 )
    {
        printf("usage : sbutr.exe START (where START is new start button text (5chars))\n");
        return 1;
    }

    fp=fopen("explorer.exe", "r+");

    if (!fp)
    {
        printf("cant find explorer.exe, try again\n");
        return 1;
    }

    if (fseek(fp, 0x2df0a, SEEK_SET) == 0)
    {
        fread(&o, 1, 1, fp);
        printf("explorer.exe at 0x2df0a is $%x should be $5 \n",o);
    }

    if ( o != p )
    {
        printf("incorrect byte found at 0x2df0a, exiting... \n");
        return 1;
    }

    for(;;)
    {
        y = time(&ntime);

        answ = div( y, 11 );
        
        x = answ.rem;

        if ( x<0 )
            x = ( x * -1 );   // Invert number if its negative

        if ( ( x > 0 ) && ( x < argc ) )
            break;

    }

    printf("changing start button to read %s arg %d\n",argv[x],x);

    fseek( fp, 0x2df0c, SEEK_SET);
    fwrite( &argv[x][0], 1, 1, fp );
        
    fseek( fp, 0x2df0e, SEEK_SET);
    fwrite( &argv[x][1], 1, 1, fp );

    fseek( fp, 0x2df10, SEEK_SET);
    fwrite( &argv[x][2], 1, 1, fp );

    fseek( fp, 0x2df12, SEEK_SET);
    fwrite( &argv[x][3], 1, 1, fp );

    fseek( fp, 0x2df14, SEEK_SET);
    fwrite( &argv[x][4], 1, 1, fp );

    printf("done... booting windoze on %s\n",ctime(&ntime));
    
    fclose(fp);

    return 0;
}
