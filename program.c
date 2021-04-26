#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passwords.h"

#define READ 1
#define WRITE 2
#define DELETE 4

struct user
{
	char name[20];
	char username[20];
	char password[20];
	int permissions;
};

void print_user(struct user* usr)
{
	printf("Username: %s", usr->username);
	printf(usr->username);
}

void chat()
{

}

void shell(struct user* usr)
{
	if usr->
}

int main()
{
	char username[20];
	char password[20];
	printf("Enter your name: ");
	fgets(username, sizeof(username)-1, stdin);
	printf("Enter your password: ");
	fgets(password, sizeof(password)-1, stdin);
	struct user* users[20];
	
	struct user* joey = malloc(sizeof(struct user));
	strcpy(joey->name, "Joey Mathis");
	strcpy(joey->username, "jmathis");
	strcpy(joey->password, JOEY_PASSWORD);
	joey->permissions = READ | WRITE | DELETE;
	users[0] = joey;

	print_user(users[0]);
}

