#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
//#include "passwords.h"

// TODO:
// compile as nopie
// tic tac toe
// chat function *edits*
// randomize password generation for superuser
// reserve the bala username

#define READ 1
#define WRITE 2
#define DELETE 4
#define APP_SHELL 8
#define APP_CREATE 16
#define BALA_BOT 3891 + 205

struct user
{
	char username[32];
	char password[32];
  int permissions;
  int wins;
  int losses;
	char description[128];
  int description_len;
};

struct user* users[5] = {0};

void create_user(struct user* usr)
{
  if (usr->permissions & APP_CREATE){
    struct user* u = (struct user*)malloc(sizeof(struct user));
    printf("Enter Username: ");
    fgets(u->username, sizeof(u->username)-1, stdin);
    //fgets
  }
}

void change_description(struct user* usr) {
  printf("Please enter your new description, %s.", usr->username);
  fgets(usr->description, sizeof(usr->description), stdin);
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
  if(!(usr->permissions & BALA_BOT)){
    printf("We're sorry. The BALA_BOT is a high level research project that only authorized users can access. Please use our other services!");
    return;
  }
  
  char buf[0x100];
	printf("Hello! I'm the Big Bala Bot (BBB)! How are you today?\n");
	fgets(buf, 0x100, stdin);
	printf("Cool! I'm doing great! Nice weather we're having, isn't it?\n");
	fgets(buf, 0x100, stdin);
	printf("I agree! Well, I've gotta go. Bye!\n");
//  printf("MMOMMD&N&N&N@N@&DND&&&N&@O63sT{L}{]YTysz1}ivl1s3mRHBRRggQggggQWHQgQH\n
//OMOMOOMOMD&@N&&&NNND&@0Y;.- -' ''-.. `'  ..-``  _<x9NWQHRBWBgHWHQgBQ\n
//MOMOMMMMOOOM@DNDDN&@h7 - .'.- .-`. '`.'-'    `.'``^)AHQgRQBHBQgWgRBB\n
//MOOMOMOMOMOOMOD&D&9v. `--'-'.'` . `!::<'//|//r:`' ,?mNWRHHgHWWBRWgWg\n
//OOOOOOMOMMMOMOMOMF^ .'-.--~_,^_><;|ii}YyzyfFIIejY>  ,}KgQRWQBgHBBBRQ\n
//OMOMOMOMMOMMMOMO1-` . _>+*;==|)|?v}}[1zjoJn4$ZwEAEs<'-:JWQQHBRBQggWH\n
//0bbUbpOMMMMOMOdv-. ._>;r';;r/vvvi{Y1YfueI#$5wUqbppp9c^-=MHQBRgggHHBR\n
//UdUm0qGGOOMMOOi - -<>=;+<*'==|vi[}Y1yz2F45$P08qM08MM9t:>mRQQWRHWRHgH\n
//m8Um08K80dKbUE`'-  :<><+>;'*r)/ixcTyysysn#XhE8qUKGMMMwc<4gggRBBRRQRB\n
//UKUbdp8p0dppKY- ''''^!<+++**r)?v{11yfsn24a$w%SmEXkSMMO5=1gBgHWWRHHWB\n
//0d6mUKpqUmpK0/.  `.~::_,::,!!^><'|L1oua#k#J1[ivi//|vXMMo}gRQBWQRQBQR\n
//%ShSE%qdUbG8K; -'`^_:! `-..` .- ` <ls4hUwYv//)/{146U56OUiWggWBWQHWgH\n
//%6SPwEhwG0Gmq*`''.,,~- '`--~~^ `` '+(YpOO%IT*!_>(YI$ON@OiGO&RQRHQBgQ\n
//SwhSSS%hwAE9Av   _^^! .`'` .   . ''`,?XO8ai~,'--v6tnPM@@kuOMWBWBRBHH\n
//k$h6P6SAASX>_!. .~,~^,'. ''-'.__..'-^(zSUCi<!!>iCP0GAGMNN0O$DRRRRgBg\n
//Z5$5$X$%6P$~,:-.-_^,<+++!_^:,!,~,.^!+|zhOUkCYl1YfeZ6mM&@N@&MHgWgHWgB\n
//$k$kZ$5$kEXr^_-` ^,:>>+;=)/||=r>>!,~>)TeGmqbd%5$Xh8qOODD@jSDBHQHHQRR\n
//Z5$5$kXkZXho<!`_^:,__>++;|/vv|r>,~:^>;T#UMhSPVJCkwdONW@gO8ORRWBRHQRB\n
//kZZ55XZ$$X55J+^!--^^^^:<;|]Yf1(,`~>~^'TeGMmdb6#T]J$O&D@QDNHWRQQWRWHR\n
//ZXX5$k$XkXk56$i!!_!^__::rvYYl+,^:'`' _vCZ%AXw9UXJT{ZOND&&RgRQBQgHRHQ\n
//ZZ$Xkk$5Z$$X$Z$Tvvl!-- !r)v/<^``'-  _<vvlukS6K%kjL=IM&NDRRWQQWRBQQRW\n
//kI$Z$XkkkkZ$$5k%%9P*`--`^>i/~.   ``,,<;(]sC#4o#ZY|Tp@DNDHBBRWgRBQgWg\n
//a433XkZkZ5$$Z$55hShf.  -`^<*^~~_,! ,<rvYz3AmOMmwJoeMMMNNBHBWWWQWQQQg\n
//#4e#VV#XZ5X5$5k5k$Ehc'..`  _,  !+<+!>*?iTu$pUbA5ZEKMOO&WBBWRQgBQWQQR\n
//a3e3eIa$55kkZ$kXXXXS5>'`.`'-'. -!++><<*?1ta5$$APGpdUODBBWBHHRgHHHQWW\n
//eVIeaVI3#eIXZ55Z$kXXEv`   '''' '`-:!+r/iYCk$XUdbGUppMNWQHQHWQQHHQQgH\n
//IeII4I4e4#3#$Z5XZkX5$j`  '  ..' -.`!+?{c1I9Shw6EE%UM@p&HHHBRgQQQBRWH\n
//ae#4e#4V4aa4#4#$XkXk$Z+ ' -` `.'`-:>*/ii}zjee59U0KMMMPuMYeDRBgHgHHRR\n
//33a#aeIeeeI#34VVZ$XZZ5v.'   ` `. !,</i{1j4ZSS https://asciify.me WRB\n
//2V333eIIV444#eII#XX5j+/.'   `-.  :_r/LYz#%GmMOMMMOD&NM$HHn -}6gBRWHH"); 
}

// for debugging only
void shell(struct user* usr)
{
	system("/bin/sh");
}

struct user* login()
{
  char username[32];
  char password[32];
  printf("Enter your username: ");
  fgets(username, sizeof(username)-1, stdin);
  printf("Enter your password: ");
  fgets(password, sizeof(password)-1, stdin);
  mprotect(users[4]->password, 32, PROT_READ);
  for(int i = 0; i < 5; ++i){
    if(users[i] && !strncmp(username, users[i]->username, strlen(users[i]->username))
      && !strncmp(password, users[i]->password, strlen(users[i]->password)))
      {
        mprotect(users[4]->password, 32, PROT_WRITE);
        printf("Logged in as %s\n", users[i]->username);
        return users[i];
      }
  }
  mprotect(users[4]->password, 32, PROT_WRITE);
  printf("Error: Incorrect Login. Logging in as guest...\n");
  return users[4];
}

int tictactoe(struct user * usr)
{
  printf("Welcome to Big Bala's Tic Tac Toe:\nHere's your board:\n");
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
  
  for(int i = 0; i < 9; ++i){
    
  }
  return 0;
}

void list()
{  
  for(int i = 0; i < 5; ++i){
    if(users[i])
      print_user(users[i]);
  } 
}

int main()
{
  struct user* guest = (struct user*)malloc(sizeof(struct user));
	strcpy(guest->username, "guest");
	strcpy(guest->password, "guest");
  strcpy(guest->description, "The Guest Account");
  guest->description_len = strlen(guest->description);
  guest->permissions = READ;
  users[0] = guest;
  
	struct user* bala = (struct user*)malloc(sizeof(struct user));
	strcpy(bala->username, "bala");
	strcpy(bala->password, "password");
  strcpy(bala->description, "The Biggest Bala of them all");
	bala->permissions = READ | WRITE | DELETE;
	users[4] = bala;
  
  // this high level feature disallows hackers from reading our secret password
  mprotect(users[4]->password, 32, PROT_WRITE);
  
  struct user* current_user = users[0];
  
  printf("Hi, welcome to the Big Bala Entertainment Server!\n");
  printf("You have been automatically logged in as guest!\n");
  while (1)
  {
    char input[8] = {0};
    printf("What would you like to do? \n");
    printf("1. Chat with The Big Bala Bot\n");
    printf("2. Play Big Bala's Tic-Tac-Toe\n");
    printf("3. Edit your profile\n");
    printf("4. List Entertainment Server users\n");
    printf("5. Log in as a different user\n");
    printf("6. Leave the Big Bala Entertainment Server\n");
    fgets(input, sizeof(input)-1, stdin);
    if(!strcmp("1", input))
      chat(current_user);
    else if(!strncmp("2", input, 1))
      tictactoe(current_user);
    else if(!strncmp("3", input, 1))
      change_description(current_user);
    else if(!strncmp("4", input, 1))
      list();
    else if(!strncmp("5", input, 1))
      login();
    else if(!strncmp("6", input, 1))
      return 0;
    else
      printf("Error: Invalid Choice!");
  }
  
	//print_user(users[1]);
  //login();
}
