#include <stdio.h>
#include <string.h>

#include "../include/account.h"
#include "../include/client.h"

void client_login()
{
    unsigned int id;
    char password[20];
    printf("Account ID: ");
    scanf("%u", &id);
    printf("Password: ");
    scanf("%s", password);

    Account *account = find_account_by_id(id);
    if (account && strcmp(account->password, password) == 0 && account->status == ACTIVE)
    {
        client_menu(id);
    }
    else
    {
        printf("Login Failed\n");
    }
}

void client_menu(unsigned int id)
{
    int choice;
    do
    {
        printf("\n1. Transfer\n2. GetCash\n3. Deposit \n4. Change Password\n5. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            make_transaction_client(id);
            break;
        case 2:
            deposit_client(id);
            break;
        case 3:
            get_cash_client(id);
            break;
        case 4:
            change_password(id);
            break;
        case 5:
            return;
        }
    } while (choice != 5);
}

void make_transaction_client(unsigned int id)
{
    unsigned int to_id;
    double amount;

    Account accounts[100];
    int count = load_all_accounts(accounts);

    Account *from = NULL;
    Account *to = NULL;

    printf("Target Account: ");
    scanf("%u", &to_id);

    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_id == id)
            from = &accounts[i];
        if (accounts[i].account_id == to_id)
            to = &accounts[i];
    }

    if (!from || !to)
    {
        printf("One or both accounts not found.\n");
        return;
    }

    if (from->status != ACTIVE || to->status != ACTIVE)
    {
        printf("One or both accounts are not active.\n");
        return;
    }

    printf("Amount: ");
    scanf("%lf", &amount);

    if (from->balance >= amount)
    {
        from->balance -= amount;
        to->balance += amount;
        save_all_accounts(accounts, count);
        printf("Transaction completed.\n");
    }
    else
    {
        printf("Insufficient balance.\n");
    }
}

void deposit_client(unsigned int id)
{
    double amount;
    Account accounts[100];
    int count = load_all_accounts(accounts);

    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_id == id)
        {
            printf("Amount: ");
            scanf("%lf", &amount);
            accounts[i].balance += amount;
            save_all_accounts(accounts, count);
            printf("Deposit successful.\n");
            return;
        }
    }

    printf("Account not found.\n");
}

void get_cash_client(unsigned int id)
{
    double amount;
    Account accounts[100];
    int count = load_all_accounts(accounts);

    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_id == id)
        {
            printf("Amount: ");
            scanf("%lf", &amount);
            if (accounts[i].balance >= amount)
            {
                accounts[i].balance -= amount;
                save_all_accounts(accounts, count);
                printf("Withdrawal successful.\n");
            }
            else
            {
                printf("Insufficient funds.\n");
            }
            return;
        }
    }

    printf("Account not found.\n");
}

void change_password(unsigned int id)
{
    char old_pass[20], new_pass[20];
    Account accounts[100];
    int count = load_all_accounts(accounts);

    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_id == id)
        {
            printf("Old Password: ");
            scanf("%s", old_pass);
            if (strcmp(accounts[i].password, old_pass) == 0)
            {
                printf("New Password: ");
                scanf("%s", new_pass);
                strcpy(accounts[i].password, new_pass);
                save_all_accounts(accounts, count);
                printf("Password updated.\n");
            }
            else
            {
                printf("Incorrect old password.\n");
            }
            return;
        }
    }

    printf("Account not found.\n");
}