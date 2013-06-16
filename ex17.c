// Include all the requisite libraries

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Define the two below as constants by the C pre-processor. 
#define MAX_DATA 512
#define MAX_ROWS 100

// Declare a structure with the following variables, nothing that the two strings are fixed size and can only have 512 characters in them.
struct Address {
	 int id;
	 int set;
	 char name[MAX_DATA];
	 char email[MAX_DATA];
};

// Make a new structure composed out of MAX_ROWS number of Address structs
struct Database {
	 // Imagine a 100 entry python list that you can only add 4-tuples
	 // to of the form(int, int, "string", "string")
	 struct Address rows[MAX_ROWS];
};

// A structure that's composed of a pointer to a file
// and the pointer to a database struct.
struct Connection {
	 // Note: FILE type only exists in <stdlib.h>
	 FILE *file;
	 struct Database *db;
};

// Die function that recieves a string message and returns nothing
void die(const char *message)
{
	 // If it's a predefined error, that we just saw
	 // detect it from errno flag...
	 if(errno) {
		  // ...and print out the associated error message
		  // Note that perror then linebreaks and
		  // prints out a message associated with the errno
		  // Note: man says that the message should usually be 
		  // the function the error is coming from
		  perror(message);
	 } else {
		  // Otherwise, just print your own custom error message
		  printf("ERROR: %s\n", message);
	 }

	 exit(1);
}

// Function that recieves a pointer to an address addr and returns nothing
void Address_print(struct Address *addr)
{
	 // prints out a single set of id, name and email
	 // of the database entry passed here
	 printf("%d %s %s\n",
			addr->id, addr->name, addr->email);
}

// Function that recieves a connection pointer and returns nothing
void Database_load(struct Connection *conn)
{
	 // Try to read data the size of 1 Database structure
	 // from the file pointer at conn->file
	 // and send that read information to the same location 
	 // inside conn->db
	 int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	 // Check to see if it returned 1 piece of data.
	 // the 1 comes from the THIRD argument in the fread function,
	 // it is NOT a truth 1. 
	 if(rc != 1) die("Failed to load database.");
}

// Function that returns a pointer of type Connection
// that recieves a pointer to a string and a character
struct Connection *Database_open(const char *filename, char mode)
{
	 // First allocate memory for the connection
	 struct Connection *conn = malloc(sizeof(struct Connection));
	 // if we fail, cry foul.
	 if(!conn) die("Memory error"); 

	 // Do the same thing as above for memory.
	 // Needs to be in this order because the database depends
	 // on the connection existing and C does not
	 // automatically allocate dependencies (Important!)
	 conn->db = malloc(sizeof(struct Database));
	 if(!conn->db) die("Memory error");

	 // If our mode argument is 'c' for create...
	 if(mode == 'c') {
		  // ...create a file of length 0 ready for reading
		  conn->file = fopen(filename, "w");
	 } else {
		  // ... otherwise 
		  conn->file = fopen(filename, "r+");

		  if(conn->file) {
			   Database_load(conn);
		  }
	 }

	 if(!conn->file) die("Failed to open the file");

	 return conn;
}

void Database_close(struct Connection *conn)
{
	 if(conn) {
		  if(conn->file) fclose(conn->file);
		  if(conn->db) free(conn->db);
		  free(conn);
	 }
}

void Database_write(struct Connection *conn)
{
	 rewind(conn->file);

	 int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	 if(rc != 1) die("Failed to write database");
	 
	 rc = fflush(conn->file);
	 if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
	 int i = 0;

	 for(i = 0; i < MAX_ROWS; i++) {
		  // make a prototype to initialize it
		  struct Address addr = {.id = i, .set = 0};
		  // then just assign it
		  conn->db->rows[i] = addr;
	 }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	 struct Address *addr = &conn->db->rows[id];
	 if(addr->set) die("Already set, delete it first");

	 addr->set = 1;
	 // WARNING: bug, read the "How to Break it" and fix this
	 char *res = strncpy(addr->name, name, MAX_DATA);
	 // demonstrate the strncpy bug
	 if(!res) die("Name copy failed");

	 res = strncpy(addr->email, email, MAX_DATA);
	 if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
	 struct Address *addr = &conn->db->rows[id];

	 if(addr->set) {
		  Address_print(addr);
	 } else {
		  die("ID is not set");
	 }
}

void Database_delete(struct Connection *conn, int id)
{
	 struct Address addr = {.id = id, .set = 0};
	 conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	 int i = 0;
	 struct Database *db = conn->db;

	 for(i = 0; i < MAX_ROWS; i++) {
		  struct Address *cur = &db->rows[i];

		  if(cur->set) {
			   Address_print(cur);
		  }
	 }
}

main(int argc, char *argv[])
{
	 if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

	 char *filename = argv[1];
	 char action = argv[2][0];
	 struct Connection *conn = Database_open(filename, action);
	 int id = 0;

	 if(argc > 3) id = atoi(argv[3]);
	 if(id >= MAX_ROWS) die("There's not that many records.");

	 switch(action) {
	 case 'c':
		  Database_create(conn);
		  Database_write(conn);
		  break;

	 case 'g':
		  if(argc != 4) die("Need an id to get");

		  Database_get(conn, id);
		  break;

	 case 's':
		  if(argc != 6) die("Need id, name, email to set");

		  Database_set(conn, id, argv[4], argv[5]);
		  Database_write(conn);
		  break;

	 case 'd':
		  if(argc != 4) die("Need id, to delete");

		  Database_delete(conn, id);
		  Database_write(conn);
		  break;

	 case 'l':
		  Database_list(conn);
		  break;
	 default:
		  die("Invalid action, only: c=create, g=get, s=set, d=delete");
	 }

	 Database_close(conn);

	 return 0;
}
