#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user
{
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

void balance_inquiry(struct user *user)
{
    printf("Your current balance is Rs. %.2f", user->balance);
}

void add_fund(struct user *user)
{
    int amount;
    printf("Enter amount to be added:\t");
    scanf("%d", &amount);
    user->balance += amount;
    FILE *fp = fopen(user->phone, "w");
    fwrite(user, sizeof(struct user), 1, fp);
    fclose(fp);
    printf("\n\nYou have deposited Rs.%d", amount);
}

void cash_withdraw(struct user *user)
{
    int amount;
    printf("Enter withdrawal amount:\t");
    scanf("%d", &amount);
    if (amount % 500 != 0)
        printf("\nSorry amount should be multiple of 500");
    else if (amount > user->balance)
        printf("\nSorry insufficient balance");
    else
    {
        user->balance -= amount;
        FILE *fp = fopen(user->phone, "w");
        fwrite(user, sizeof(struct user), 1, fp);
        fclose(fp);
        printf("\n\nYou have withdrawn Rs.%d", amount);
    }
}

void online_transfer(struct user *user)
{
    struct user usr;
    char phone[50];
    int amount;
    printf("Please enter the phone number to transfer balance:\t");
    scanf("%s", phone);
    printf("Enter the amount to transfer:\t");
    scanf("%d", &amount);
    if (amount > user->balance)
        printf("\nSorry insufficient balance");
    else
    {
        FILE *fptr = fopen(strcat(phone, ".dat"), "r");
        if (fptr == NULL)
            printf("Sorry number is not registered");
        else
        {
            fread(&usr, sizeof(struct user), 1, fptr);
            fclose(fptr);
            usr.balance += amount;
            fptr = fopen(phone, "w");
            fwrite(&usr, sizeof(struct user), 1, fptr);
            if (fwrite != 0)
            {
                printf("Your transfer is completed. You have transferred Rs.%d to %s", amount, usr.phone);
                fclose(fptr);
                user->balance -= amount;
                FILE *fp = fopen(user->phone, "w");
                fwrite(user, sizeof(struct user), 1, fp);
                fclose(fp);
            }
        }
    }
}

void change_password(struct user *user)
{
    char password[50];
    printf("\n\nPlease enter your old password:\t");
    scanf("%s", password);
    if (!strcmp(password, user->password))
    {
        printf("\n\nPlease enter your new password:\t");
        scanf("%s", password);
        strcpy(user->password, password);
        FILE *fp = fopen(user->phone, "w");
        fwrite(user, sizeof(struct user), 1, fp);
        fclose(fp);
        printf("\nPassword successfully changed");
    }
    else
        printf("\nSorry your password is wrong");
}

int main()
{
    struct user user, usr;
    char filename[50], phone[50], password[50], phone2[50];
    FILE *fp, *fptr;
    int opt, choice;
    int amount;
    char cont = 'y';
    printf("\nWhat do you want to do?");
    printf("\n\n1.Register your account");
    printf("\n2.Login to your account");
    printf("\nEnter your choice:\t");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("\nEnter your phone number:\t");
        scanf("%s", user.phone);
        printf("Enter your account number:\t");
        scanf("%s", user.ac);
        printf("Enter a password for your account:\t");
        scanf("%s", user.password);
        printf("Enter the amount you want to deposit:\t");
        scanf("%f", &user.balance);
        fp = fopen(strcat(user.phone, ".dat"), "wb");
        fwrite(&user, sizeof(struct user), 1, fp);
        fclose(fp);
        printf("\nRegistration successful.");
        break;
    case 2:
        printf("\nEnter your phone number:\t");
        scanf("%s", phone);
        printf("Enter your password:\t");
        scanf("%s", password);
        fp = fopen(strcat(phone, ".dat"), "rb");
        if (fp == NULL)
        {
            printf("\nSorry your account does not exist");
            exit(1);
        }
        fread(&user, sizeof(struct user), 1, fp);
        if (strcmp(password, user.password))
        {
            printf("\nSorry your password is wrong");
            exit(1);
        }
        fclose(fp);
        printf("\n\nWelcome %s", user.ac);
        while (cont == 'y')
        {
            printf("\n\nWhat do you want to do?");
            printf("\n\n1.Check balance");
            printf("\n2.Deposit money");
            printf("\n3.Withdraw money");
            printf("\n4.Transfer money online");
            printf("\n5.Change password");
            printf("\n6.Exit");
            printf("\n\nEnter your choice:\t");
            scanf("%d", &opt);
            switch (opt)
            {
            case 1:
                balance_inquiry(&user);
                break;
            case 2:
                add_fund(&user);
                break;
            case 3:
                cash_withdraw(&user);
                break;
            case 4:
                online_transfer(&user);
                break;
            case 5:
                change_password(&user);
                break;
            case 6:
                cont = 'n';
                printf("\n\nThank you for using our banking system");
                break;
            default:
                printf("\nInvalid choice");
            }
        }
        break;
    default:
        printf("\nInvalid choice");
    }
    return 0;
}
