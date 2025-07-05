#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef enum
{
    ACTIVE = 0,
    RESTRICTED = 1,
    CLOSED = 2
} AccountStatus;

typedef struct
{
    unsigned int account_id;
    char full_name[100];
    char address[100];
    int age;
    char national_id[15];
    char password[15];
    double balance;
    AccountStatus status;
} Account;

int save_account(Account data);

int load_all_accounts(Account *accounts);

Account *find_account_by_id(unsigned int id);

void update_account(Account updated);

unsigned int generate_unique_id();

void generate_random_password(char* password);

void save_all_accounts(Account* accounts, int count);

#endif