#include <stdio.h>
#include <string.h>

#include "../include/account.h"
#include "../include/admin.h"

#include "../private/private.config.h"

void admin_login()
{
    char user[20], pass[20];
    printf("Enter Admin Username: ");
    scanf("%s", user);
    printf("Enter Admin Password: ");
    scanf("%s", pass);

    if (strcmp(user, ADMIN_USERNAME) == 0 && strcmp(pass, ADMIN_PASSWORD) == 0)
    {
        admin_menu();
    }
    else
    {
        printf("Invalid Credentials\n");
    }
}

void admin_menu()
{
    int choice;
    do
    {
        printf("\nAdmin Menu:\n1. Create Account\n2. Open Existing\n3. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            create_new_account();
            break;
        case 2:
            open_existing_account();
            break;
        case 3:
            return;
        }

    } while (choice != 3);
}

void create_new_account()
{
    Account account;
    getchar();
    printf("Full Name: ");
    fgets(account.full_name, sizeof(account.full_name), stdin);
    account.full_name[strcspn(account.full_name, "\n")] = '\0';
    printf("Address: ");
    fgets(account.address, sizeof(account.address), stdin);
    account.address[strcspn(account.address, "\n")] = '\0';
    printf("Age: ");
    scanf("%d", &account.age);
    getchar();
    printf("National ID: ");
    scanf("%s", account.national_id);
    account.account_id = generate_unique_id();
    generate_random_password(account.password);
    account.balance = 0.0;
    account.status = ACTIVE;
    if (save_account(account))
    {
        printf("Account created successfully!\n");
        printf("ID: %u\nPassword: %s\n", account.account_id, account.password);
    }
    else
    {
        printf("Failed to save account to file.\n");
    }
}

void open_existing_account()
{
    int choice;
    do
    {
        printf("\n1. Make Transaction\n2. Change Status\n3. Deposit\n4. GetCash\n5. Back\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            make_transaction_admin();
            break;
        case 2:
            change_account_status();
            break;
        case 3:
            deposit_in_account_admin();
            break;
        case 4:
            get_cash_admin();
            break;
        case 5:
            return;
        }
    } while (choice != 5);
}

void make_transaction_admin()
{
    unsigned int from_id, to_id;
    double amount;
    Account accounts[100];
    int count = load_all_accounts(accounts);
    printf("From Account ID: ");
    scanf("%u", &from_id);
    printf("To Account ID: ");
    scanf("%u", &to_id);
    Account *from = NULL;
    Account *to = NULL;
    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_id == from_id)
        {
            from = &accounts[i];
        }
        if (accounts[i].account_id == to_id)
        {
            to = &accounts[i];
        }
    }
    if (!from || !to)
    {
        printf("One or both accounts not found.\n");
        return;
    }
    printf("From Account Status: %d | Balance: %.2f\n", from->status, from->balance);
    printf("To Account Status  : %d | Balance: %.2f\n", to->status, to->balance);
    if (from->status != ACTIVE)
    {
        printf("Source account is not ACTIVE.\n");
        return;
    }
    if (to->status != ACTIVE)
    {
        printf("Destination account is not ACTIVE.\n");
        return;
    }
    printf("Amount: ");
    scanf("%lf", &amount);
    if (from->balance >= amount)
    {
        from->balance -= amount;
        to->balance += amount;

        save_all_accounts(accounts, count);

        printf("Transaction successful!\n");
        printf("New From Account Balance: %.2f\n", from->balance);
        printf("New To Account Balance  : %.2f\n", to->balance);
    }
    else
    {
        printf("Insufficient balance in the source account.\n");
    }
}

void change_account_status()
{
    unsigned int id;
    printf("Enter Account ID: ");
    scanf("%u", &id);
    Account *account = find_account_by_id(id);
    if (!account)
        return;
    int status;
    printf("0-Active 1-Restricted 2-Closed: ");
    scanf("%d", &status);
    account->status = (AccountStatus)status;
    printf("Account %u status changed to %d\n", account->account_id, account->status);
    update_account(*account);
}

void get_cash_admin()
{
    unsigned int id;
    double amount;
    printf("Account ID: ");
    scanf("%u", &id);
    Account *account = find_account_by_id(id);
    if (!account)
        return;
    printf("Amount: ");
    scanf("%lf", &amount);
    if (account->balance >= amount)
    {
        account->balance -= amount;
        update_account(*account);
    }
    else
    {
        printf("Insufficient funds.\n");
    }
}

void deposit_in_account_admin()
{
    unsigned int id;
    double amount;
    printf("Account ID: ");
    scanf("%u", &id);
    Account *account = find_account_by_id(id);
    if (!account)
        return;
    printf("Amount: ");
    scanf("%lf", &amount);
    account->balance += amount;
    update_account(*account);
}
