#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[15];
    double balance;
};

unsigned int enterChoice(void);
void initializeFile();
void addAccount(FILE *fPtr);
void viewAccounts(FILE *fPtr);
void searchAccount(FILE *fPtr);
void deposit(FILE *fPtr);
void withdraw(FILE *fPtr);
void transfer(FILE *fPtr);
void updateAccount(FILE *fPtr);
void deleteAccount(FILE *fPtr);
void textFile(FILE *fPtr);
void statistics(FILE *fPtr);

int main()
{
    FILE *cfPtr;

    initializeFile();

    if ((cfPtr = fopen("credit.dat", "rb+")) == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    unsigned int choice;

    while ((choice = enterChoice()) != 11)
    {
        switch (choice)
        {
        case 1:
            addAccount(cfPtr);
            break;

        case 2:
            viewAccounts(cfPtr);
            break;

        case 3:
            searchAccount(cfPtr);
            break;

        case 4:
            deposit(cfPtr);
            break;

        case 5:
            withdraw(cfPtr);
            break;

        case 6:
            transfer(cfPtr);
            break;

        case 7:
            updateAccount(cfPtr);
            break;

        case 8:
            deleteAccount(cfPtr);
            break;

        case 9:
            textFile(cfPtr);
            break;

        case 10:
            statistics(cfPtr);
            break;

        default:
            printf("Invalid Choice!\n");
        }
    }

    fclose(cfPtr);
    printf("\nThank You!\n");
    return 0;
}

void initializeFile()
{
    FILE *fPtr;

    if ((fPtr = fopen("credit.dat", "rb")) == NULL)
    {
        fPtr = fopen("credit.dat", "wb");

        struct clientData blank = {0, "", "", 0.0};

        for (int i = 0; i < 100; i++)
        {
            fwrite(&blank, sizeof(struct clientData), 1, fPtr);
        }

        fclose(fPtr);
    }
}

unsigned int enterChoice(void)
{
    unsigned int choice;

    printf("\n============================");
    printf("\n BANK MANAGEMENT SYSTEM");
    printf("\n============================");

    printf("\n1. Add Account");
    printf("\n2. View All Accounts");
    printf("\n3. Search Account");
    printf("\n4. Deposit Money");
    printf("\n5. Withdraw Money");
    printf("\n6. Transfer Money");
    printf("\n7. Update Balance");
    printf("\n8. Delete Account");
    printf("\n9. Generate Text Report");
    printf("\n10. Statistics");
    printf("\n11. Exit");

    printf("\n\nEnter Choice: ");
    scanf("%u", &choice);

    return choice;
}

void addAccount(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};
    unsigned int account;

    printf("Enter Account Number (1-100): ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists!\n");
        return;
    }

    client.acctNum = account;

    printf("Enter Last Name: ");
    scanf("%s", client.lastName);

    printf("Enter First Name: ");
    scanf("%s", client.firstName);

    printf("Enter Balance: ");
    scanf("%lf", &client.balance);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&client, sizeof(struct clientData), 1, fPtr);

    printf("Account Added Successfully!\n");
}

void viewAccounts(FILE *fPtr)
{
    struct clientData client;

    rewind(fPtr);

    printf("\n%-8s%-15s%-15s%-12s\n",
           "AccNo", "Last Name", "First Name", "Balance");

    while (fread(&client, sizeof(struct clientData), 1, fPtr))
    {
        if (client.acctNum != 0)
        {
            printf("%-8u%-15s%-15s%.2lf\n",
                   client.acctNum,
                   client.lastName,
                   client.firstName,
                   client.balance);
        }
    }
}

void searchAccount(FILE *fPtr)
{
    unsigned int account;
    struct clientData client;

    printf("Enter Account Number: ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account Not Found!\n");
    }
    else
    {
        printf("\nAccount Number : %u", client.acctNum);
        printf("\nName : %s %s",
               client.firstName,
               client.lastName);
        printf("\nBalance : %.2lf\n",
               client.balance);
    }
}

void deposit(FILE *fPtr)
{
    unsigned int account;
    double amount;
    struct clientData client;

    printf("Enter Account Number: ");
    scanf("%u", &account);

    printf("Enter Deposit Amount: ");
    scanf("%lf", &amount);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account Not Found!\n");
        return;
    }

    client.balance += amount;

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&client, sizeof(struct clientData), 1, fPtr);

    printf("Deposit Successful!\n");
}

void withdraw(FILE *fPtr)
{
    unsigned int account;
    double amount;
    struct clientData client;

    printf("Enter Account Number: ");
    scanf("%u", &account);

    printf("Enter Withdrawal Amount: ");
    scanf("%lf", &amount);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account Not Found!\n");
        return;
    }

    if (amount > client.balance)
    {
        printf("Insufficient Balance!\n");
        return;
    }

    client.balance -= amount;

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&client, sizeof(struct clientData), 1, fPtr);

    printf("Withdrawal Successful!\n");
}

void transfer(FILE *fPtr)
{
    unsigned int from, to;
    double amount;

    struct clientData sender, receiver;

    printf("From Account: ");
    scanf("%u", &from);

    printf("To Account: ");
    scanf("%u", &to);

    printf("Amount: ");
    scanf("%lf", &amount);

    fseek(fPtr, (from - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&sender, sizeof(struct clientData), 1, fPtr);

    fseek(fPtr, (to - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&receiver, sizeof(struct clientData), 1, fPtr);

    if (sender.acctNum == 0 || receiver.acctNum == 0)
    {
        printf("Invalid Account!\n");
        return;
    }

    if (sender.balance < amount)
    {
        printf("Insufficient Balance!\n");
        return;
    }

    sender.balance -= amount;
    receiver.balance += amount;

    fseek(fPtr, (from - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&sender, sizeof(struct clientData), 1, fPtr);

    fseek(fPtr, (to - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&receiver, sizeof(struct clientData), 1, fPtr);

    printf("Transfer Successful!\n");
}

void updateAccount(FILE *fPtr)
{
    unsigned int account;
    double amount;
    struct clientData client;

    printf("Enter Account Number: ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account Not Found!\n");
        return;
    }

    printf("Current Balance: %.2lf\n", client.balance);

    printf("Enter Amount (+Deposit / -Withdraw): ");
    scanf("%lf", &amount);

    client.balance += amount;

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&client, sizeof(struct clientData), 1, fPtr);

    printf("Balance Updated!\n");
}

void deleteAccount(FILE *fPtr)
{
    unsigned int account;

    struct clientData blank = {0, "", "", 0.0};
    struct clientData client;

    printf("Enter Account Number: ");
    scanf("%u", &account);

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account Not Found!\n");
        return;
    }

    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    fwrite(&blank, sizeof(struct clientData), 1, fPtr);

    printf("Account Deleted Successfully!\n");
}

void textFile(FILE *fPtr)
{
    FILE *writePtr = fopen("accounts.txt", "w");

    struct clientData client;

    rewind(fPtr);

    fprintf(writePtr,
            "%-8s%-15s%-15s%-12s\n",
            "AccNo",
            "Last Name",
            "First Name",
            "Balance");

    while (fread(&client, sizeof(struct clientData), 1, fPtr))
    {
        if (client.acctNum != 0)
        {
            fprintf(writePtr,
                    "%-8u%-15s%-15s%.2lf\n",
                    client.acctNum,
                    client.lastName,
                    client.firstName,
                    client.balance);
        }
    }

    fclose(writePtr);

    printf("accounts.txt generated successfully!\n");
}

void statistics(FILE *fPtr)
{
    struct clientData client;

    int count = 0;
    double total = 0;

    rewind(fPtr);

    while (fread(&client, sizeof(struct clientData), 1, fPtr))
    {
        if (client.acctNum != 0)
        {
            count++;
            total += client.balance;
        }
    }

    printf("\nActive Accounts : %d\n", count);
    printf("Total Balance : %.2lf\n", total);

    if (count > 0)
    {
        printf("Average Balance : %.2lf\n",
               total / count);
    }
}