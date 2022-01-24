#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main(){
    FILE *fp, *ft;
    char another, choice;


    struct contact{
        char name[40];
        int phonenumber;
    };

    struct contact c;

    char conname[40];

    long int recsize;


    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL){
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL){
            printf("Cannot open file");
            exit(1);
        }
    }


    recsize = sizeof(c);


    while(1){
        printf("1. Add Contact\n");
        printf("2. List Contact\n");
        printf("3. Modify Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        fflush(stdin);
        scanf("\n%c", &choice);
        switch(choice){
            case '1':
                system("clear");
                fseek(fp,0,SEEK_END);

                another = 'y';
                while(another == 'y'){
                    flush();
                    printf("\nEnter name: ");
                    fgets(c.name, 40, stdin);
                    printf("\nEnter Phone number: ");
                    scanf("%d", &c.phonenumber);
                    fwrite(&c,recsize,1,fp);

                    printf("\nAdd another contact(y/n) ");
                    fflush(stdin);
                    scanf("\n%c", &another);
                }
                break;
            case '2':
                system("clear");
                rewind(fp);
                while(fread(&c,recsize,1,fp)==1){
                    printf("\n%s %d\n",c.name,c.phonenumber);
                }
                break;

            case '3':
                system("clear");
                another = 'y';
                while(another == 'y'){
                    printf("Enter the contact's name to modify: ");
                    scanf("%s", conname);
                    rewind(fp);
                    while(fread(&c,recsize,1,fp)==1){
                        if(strcmp(c.name,conname) == 0){
                            printf("\nEnter new name and phone number: ");
                            scanf("%s%d",c.name,&c.phonenumber);
                            fseek(fp,-recsize,SEEK_CUR);
                            fwrite(&c,recsize,1,fp);
                            break;
                        }
                    }
                    printf("\nModify another contact(y/n)");
                    fflush(stdin);
                    scanf("\n%c", &another);
                }
                break;
            case '4':
                system("clear");
                another = 'y';
                while(another == 'y'){
                    flush();
                    printf("\nEnter name of contact to delete: ");
                    fgets(conname,40, stdin);
                    ft = fopen("Temp.dat","wb");
                    rewind(fp);
                    while(fread(&c,recsize,1,fp) == 1){
                        if(strcmp(c.name,conname) != 0){
                            fwrite(&c,recsize,1,ft);
                        }
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("EMP.DAT");
                    rename("Temp.dat","EMP.DAT");
                    fp = fopen("EMP.DAT", "rb+");
                    printf("Delete another contact(y/n)");
                    fflush(stdin);
                    scanf("\n%c", &another);
                }
                break;
            case '5':
                fclose(fp);
                exit(0);
        }
    }
    return 0;
}
