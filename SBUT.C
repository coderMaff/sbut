#include <stdio.h>
#include <conio.h>

int main(int argc, char **argv)
{
    FILE    *fp;
    char    o = 0;
    char    p = 5;

    printf("\nsbut is buggering explorer.exe [by maff in 97]\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    if ( argc<2 )
    {
        printf("usage : sbut.exe START (where START is new start button text (5chars))\n");
        return 1;
    }

    printf("if you aint backed up explorer.exe yet, use CTRL-C now!\n");

    getch();

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

    printf("changing start button to read %s\n",argv[1]);

    fseek( fp, 0x2df0c, SEEK_SET);
    fwrite( &argv[1][0], 1, 1, fp );

    fseek( fp, 0x2df0e, SEEK_SET);
    fwrite( &argv[1][1], 1, 1, fp );

    fseek( fp, 0x2df10, SEEK_SET);
    fwrite( &argv[1][2], 1, 1, fp );

    fseek( fp, 0x2df12, SEEK_SET);
    fwrite( &argv[1][3], 1, 1, fp );

    fseek( fp, 0x2df14, SEEK_SET);
    fwrite( &argv[1][4], 1, 1, fp );

    printf("opperation complete, reboot windoze to continue\n");
    
    fclose(fp);

    return 0;
}
