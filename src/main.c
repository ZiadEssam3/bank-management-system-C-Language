#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/admin.h"
#include "../include/client.h"

int main()
{
    srand(time(NULL));
    int choice;

    do
    {
        printf("\nBank System\n1.Admin\n2.Client\n3.Exit\nChoose: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            admin_login();
            break;
        case 2: 
            client_login();
            break;
        case 3:
            printf("Exiting....\n");
        default: 
            printf("Invalid");
        }

    } while (choice != 3);

    return 0;
}