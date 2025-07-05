#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../include/account.h"

#define FILE_PATH "database/accounts.txt"

int save_account(Account data)
{
    FILE *fp = fopen(FILE_PATH, "a");
    if (!fp)
        return 0;
    fprintf(
        fp,
        "%u|%s|%s|%d|%s|%s|%.2f|%d\n",
        data.account_id, data.full_name, data.address, data.age,
        data.national_id, data.password, data.balance, data.status);
    fclose(fp);
    return 1;
}

void save_all_accounts(Account *accounts, int count)
{
    FILE *fp = fopen("database/accounts.txt", "w");
    if (!fp)
    {
        printf("Failed to open file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%u|%s|%s|%d|%s|%s|%.2f|%d\n",
                accounts[i].account_id,
                accounts[i].full_name,
                accounts[i].address,
                accounts[i].age,
                accounts[i].national_id,
                accounts[i].password,
                accounts[i].balance,
                accounts[i].status);
    }

    fclose(fp);
}

int load_all_accounts(Account *accounts)
{
    FILE *fp = fopen("database/accounts.txt", "r");
    if (!fp)
        return 0;

    int count = 0;
    while (fscanf(fp, "%u|%[^|]|%[^|]|%d|%[^|]|%[^|]|%lf|%d\n",
                  &accounts[count].account_id,
                  accounts[count].full_name,
                  accounts[count].address,
                  &accounts[count].age,
                  accounts[count].national_id,
                  accounts[count].password,
                  &accounts[count].balance,
                  (int *)&accounts[count].status) == 8)
    {
        count++;
    }

    fclose(fp);
    return count;
}

Account *find_account_by_id(unsigned int id)
{
    static Account data;
    FILE *fp = fopen(FILE_PATH, "r");
    if (!fp)
        return NULL;
    while (fscanf(fp, "%u|%[^|]|%[^|]|%d|%[^|]|%[^|]|%lf|%d\n",
                  &data.account_id, data.full_name,
                  data.address, &data.age,
                  data.national_id, data.password,
                  &data.balance, (int *)&data.status) == 8)
    {
        if (data.account_id == id)
        {
            fclose(fp);
            return &data;
        }
    }
    fclose(fp);
    return NULL;
}

void update_account(Account updated)
{
    Account accounts[100];
    int count = load_all_accounts(accounts);
    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (accounts[i].account_id == updated.account_id)
        {
            accounts[i] = updated;
            found = 1;
            break;
        }
    }

    if (found)
    {
        save_all_accounts(accounts, count);
        printf("Account ID %u updated successfully.\n", updated.account_id);
    }
    else
    {
        printf("Account ID %u not found.\n", updated.account_id);
    }
}

unsigned int generate_unique_id()
{
    return (rand() % 9000) + 1000;
}

void generate_random_password(char *password)
{
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 6; i++)
    {
        password[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    password[6] = '\0';
}
