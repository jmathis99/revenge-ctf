#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "passwords.h"

// Note the goal of this CTF is to call the flag() function that is stored within passwords.h (hidden). This will print the flag!

// gcc -fno-stack-protector -no-pie

struct user
{
  char username[32];
  char password[32];
  int admin;
  int wins;
  int losses;
  char description[128];
  int description_len;
};

struct user users[5] = {0};

void rand_str(char *dest, int len){
	char charset[] = "0123456789"
			 "abcdefghijklmnopqrstuvwxyz"
			 "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	while (len-- > 0) {
		int index = (double) rand() / RAND_MAX * (sizeof(charset) - 1);
		*dest++ = charset[index];
	}
	*dest = '\0';
}

void create_user()
{
  struct user tmp = {0};
  struct user u;

  int idx = -1;
  for (int i = 0; i < 4; ++i) {
    if (memcmp(&users[i], &tmp, sizeof(tmp)) == 0) {
      idx = i;
      break;
    }
  }
  
  if(idx == -1){
    printf("Error: Too Many Users\n");
    return;
  }
  printf("Enter Username: ");
  fgets(u.username, sizeof(u.username)-1, stdin);
  printf("Username: %s\n", u.username);
  if(!strncmp(u.username, "bala", 4)){
    printf("Error: Invalid Username\n");
    return;
  }
  printf("Enter Password: ");
  fgets(u.password, sizeof(u.password)-1, stdin);
  printf("Pass: %s", u.password);
  printf("Enter Description: ");
  fgets(u.description, sizeof(u.description)-1, stdin);
  printf("Desc: %s", u.description);
  
  users[idx] = u;
}

void change_description(struct user* usr) {
  char input[10];
  printf("How long would you like your description to be? ");
  fgets(input, 10, stdin);
  usr->description_len = atoi(input);
  if(usr->description_len > 128) usr->description_len = 128; //clip values to the size of the buffer
  if(usr->description_len < 0) usr->description_len *= -1; //make sure there's no funny business with negatives
  printf("Please enter your new description: ");
  fgets(usr->description, usr->description_len, stdin);
  printf("Description updated: %s\n", usr->description);
  printf("Description length: %d\n", usr->description_len);
}

void print_user(struct user* usr)
{
	printf("%s, Wins: %d, Losses: %d\n", usr->username, usr->wins, usr->losses);
}

void print_user_details(struct user* usr)
{
  printf("Username: %s\n", usr->username);
  printf("Description: %s\n", usr->description);
  printf("Wins: %d\n", usr->wins);
  printf("Losses: %d\n", usr->losses);
}

void chat(struct user* usr)
{
  if(!usr->admin){
    printf("We're sorry. The BALA_BOT is a high level research project that only authorized users can access. Please use our other services!");
    return;
  }

  char buf[128];
  printf("Hello ") && printf(usr->username) && printf("! I'm the Big Bala Bot (BBB)! How are you today?\n");
  gets(buf); // gets is secure because we have a stack canary ^_^
  printf("Cool! I'm doing great! Nice weather we're having, isn't it?\n");
  gets(buf);
  printf("I agree! Well, I've gotta go write our cumulative final exam. Bye!\n");
}

int login()
{
  char username[32];
  char password[32];
  printf("Enter your username: ");
  fgets(username, sizeof(username)-1, stdin);
  printf("Enter your password: ");
  fgets(password, sizeof(password)-1, stdin);
  mprotect(users[4].password, 32, PROT_READ);
  for(int i = 0; i < 5; ++i){
    if(!strncmp(username, users[i].username, strlen(users[i].username))
      && !strncmp(password, users[i].password, strlen(users[i].password)))
      {
        mprotect(users[4].password, 32, PROT_WRITE);
        printf("Logged in as %s\n", users[i].username);
        return i;
      }
  }
  mprotect(users[4].password, 32, PROT_WRITE);
  printf("Error: Incorrect Login. Logging in as guest...\n");
  return 0;
}

int tictactoe(struct user * usr)
{
  printf("Welcome to Big Bala's Tic Tac Toe:\nHere's your board (BALABOT is X, you are O):\n");
  printf("   |   |   \n 0 | 1 | 2 \n   |   |   \n");
  printf("___________\n");
  printf("   |   |   \n 3 | 4 | 5 \n   |   |   \n");
  printf("___________\n");
  printf("   |   |   \n 6 | 7 | 8 \n   |   |   \n");
  
  printf("Coin flip to decide who goes first!\n");
  
  int random = rand() % 2;
  
  if(random == 0)
  {
    printf("Heads -- Bala Bot goes first!\n");
  }
  else
  {
    printf("Tails -- You go second!\n");
  }
  
  printf("The bot is deciding it's move...\n");
  sleep(5);
  for(int i = 0; i < 9; ++i){
    printf("   |   |   \n X | X | X \n   |   |   \n");
    printf("___________\n");
    printf("   |   |   \n X | X | X \n   |   |   \n");
    printf("___________\n");
    printf("   |   |   \n X | X | X \n   |   |   \n");
    break;
  }
  printf("BALABOT Wins!!! Better luck next time!");
  usr->losses++;
  return 0;
}

void details(struct user* usr)
{
  if(!usr->admin){
    printf("ERROR: You do not have permission to use this function!\n");
    return;
  }
  char input[32];
  printf("Which user would you like to see? ");
  fgets(input, sizeof(input)-1, stdin);
  for(int i=0; i < 5; ++i){
    if(!strncmp(input, users[i].username, strlen(users[i].username))){
      printf("Username: %s", users[i].username);
      printf("Tic-Tac-Toe Record: %d-%d", users[i].wins, users[i].losses);
      printf("Description: %s\n", users[i].description);
    }
  }
}

void list(struct user * usr)
{
    for(int i = 0; i < 5; ++i){
      print_user(&users[i]);
    }
}

int main()
{
  struct user guest;
  strcpy(guest.username, "guest");
	strcpy(guest.password, "guest");
  strcpy(guest.description, "The Guest Account");
  guest.description_len = 128;
  guest.admin = 0;
  guest.wins = 0;
  guest.losses = 0;
  users[0] = guest;

  struct user bala;
  strcpy(bala.username, "bala");
  strcpy(bala.password, "password");
  rand_str(bala.password, sizeof(bala.password) - 1);
  strcpy(bala.description, "The Biggest Bala of them all");
  bala.description_len = 128;
  bala.admin = 1;
  bala.wins = 3891;
  bala.losses = 0;
  users[4] = bala;
  
  // this high level feature disallows hackers from reading our secret password
  mprotect(users[4].password, 32, PROT_WRITE);
  
  struct user* current_user = &users[0];
  
  printf("Hi, welcome to the Big Bala Entertainment Server!\n");
  printf("You have been automatically logged in as guest!\n");
  while (1)
  {
    char input[8] = {0};
    printf("What would you like to do? \n");
    printf("1. Chat with The Big Bala Bot\n");
    printf("2. Play Big Bala's Tic-Tac-Toe\n");
    printf("3. Edit your profile\n");
    printf("4. View your profile\n");
    printf("5. List Entertainment Server users\n");
    printf("6. View another user's Profile\n");
    printf("7. Log in as a different user\n");
    printf("8. Leave the Big Bala Entertainment Server\n");
    printf("9. Delete a user\n");
    printf("0. Create a new user\n");
    
    fgets(input, sizeof(input) - 1, stdin);
    if (!strncmp("1", input, 1))
      chat(current_user);
    else if(!strncmp("2", input, 1))
      tictactoe(current_user);
    else if(!strncmp("3", input, 1))
      change_description(current_user);
    else if(!strncmp("4", input, 1))
      print_user_details(current_user);
    else if(!strncmp("5", input, 1))
      list(current_user);
    else if(!strncmp("6", input, 1))
      details(current_user);
    else if(!strncmp("7", input, 1))
      current_user = &users[login()];
    else if(!strncmp("8", input, 1))
      return 0;
    else if(!strncmp("0", input, 1))
      create_user();
    else{ 
      printf("Error: Invalid Choice!\n");
      printf("Input: %s", input);
      return 0;
    }

    
    memset(input, 0, 8);
  }
}
