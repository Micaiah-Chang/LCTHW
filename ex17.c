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
// that recieves a pointer to a char and a character
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
		  // ...create a text file ready for writing
		  // If the file already exists, truncate it to zero length
		  conn->file = fopen(filename, "w");
	 } else {
		  // ... otherwise open the file ready for writing
		  // and reading (Just reading would be "r")
		  conn->file = fopen(filename, "r+");

		  // If the pointer is not null then...
		  if(conn->file) {
			   // Load the database via current correction
			   Database_load(conn);
		  }
		  // If the pointer is NULL, then wait...
	 }
	 // And have it fail here!
	 if(!conn->file) die("Failed to open the file");
	 // Hence we only return when we either can create a file
	 // or can load a non-NULL file
	 // Presumptively, this always returns with a pointer
	 return conn;
}


// Function that returns void and accepts arguments
// of pointer containing type Connection
void Database_close(struct Connection *conn)
{
	 // If the connection pointer isn't null...
	 if(conn) {
		  // Then close the file if a file has been opened
		  if(conn->file) fclose(conn->file);
		  // and free the memory in use for the database struct
		  if(conn->db) free(conn->db);
		  // Of course, we shold always free the memory associated with
		  // the conneciton data structure.
		  free(conn);
	 }
}


// A function which returns nothing and accepts
// a pointer of type Connection
void Database_write(struct Connection *conn)
{
	 // set the file position to the beginning of the file
	 // So that it's not just at a random point
	 rewind(conn->file);

	 // Try to write to (the start) conn->file 1 element the size
	 // of a Database struct from the connection database in memory
	 int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	 // If you couldn't write 1 element, then you have failed
	 if(rc != 1) die("Failed to write database");

	 // Flushes stream
	 // Which means discarding the data inside of the buffer
	 // In this case, flushes everything out of conn->file
	 rc = fflush(conn->file);
	 // If that fails, then die...?
	 // weird, man fflush says that 0 is success.
	 if(rc == -1) die("Cannot flush database.");
}


// Function that returns nothing and recieves a pointer
// to a variable of type connection
void Database_create(struct Connection *conn)
{
	 int i = 0;
	 // For every possible row...
	 for(i = 0; i < MAX_ROWS; i++) {
		  // make a prototype to initialize it
		  struct Address addr = {.id = i, .set = 0};
		  // then just assign it
		  conn->db->rows[i] = addr;
	 }
}

// Function that returns void and accepts arguments
// of type Connection, int, string and string
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	 // A pointer of type struct is the same as
	 // The address of the idth row in the database contained
	 // within the connection
	 // Note that the one below can be rewritten &(conn->db->rows[id])
	 // Do NOT read as (&conn)-> etc. This makes no sense!
	 struct Address *addr = &conn->db->rows[id];
	 // If the set flag is already 1, then there is already something
	 // i.e. we cannot overwrite something in the database
	 // without deleting first. Have to be explicit
	 if(addr->set) die("Already set, delete it first");

	 // Say that it is set. Well of course it is, you just set it
	 addr->set = 1;
	 // WARNING: bug, read the "How to Break it" and fix this
	 char *res = strncpy(addr->name, name, MAX_DATA);
	 // demonstrate the strncpy bug
	 if(!res) die("Name copy failed");

	 // Same thing as above
	 res = strncpy(addr->email, email, MAX_DATA);
	 if(!res) die("Email copy failed");
}

// A function that returns nothing and accepts
// a pointer of type Connection and an integer
void Database_get(struct Connection *conn, int id)
{
	 // Create a pointer of type address
	 // which is the address of the connection's
	 // database and associated row
	 struct Address *addr = &conn->db->rows[id];

	 // If you successfully set the address from before
	 // i.e. if something exists there
	 if(addr->set) {
		  // Then try to print the address if you can
		  Address_print(addr);
	 } else {
		  // If not it's obviously been not set and send program off
		  // to die in peace
		  die("ID is not set");
	 }
}


// Function which returns nothing
// and accepts a pointer of type connection and an integer
void Database_delete(struct Connection *conn, int id)
{
	 // initialize an address structure which has
	 // the current id and the set set to 0 so that it can be overwritten
	 // note that name and email are not mentioned.
	 // They are \0 by default?
	 struct Address addr = {.id = id, .set = 0};
	 // Then set the row of the database concerned to this 'zero' address
	 conn->db->rows[id] = addr;
}

// Function that returns nothing and accepts
// a pointer of type connection
void Database_list(struct Connection *conn)
{
	 // Initialize by making a counter
	 // And having a pointer of type database
	 int i = 0;
	 struct Database *db = conn->db;

	 for(i = 0; i < MAX_ROWS; i++) {
		  // For the current Address, set it to the address of
		  // each row
		  struct Address *cur = &db->rows[i];

		  // If there is an entry here. e.g. set is 1...
		  if(cur->set) {
			   // then print it
			   Address_print(cur);
		  }
		  // Otherwise, then it's not set, there's nothing to print
	 }
}

// Finally! The main function!
int main(int argc, char *argv[])
{
	 // If you don't provide enough arguments, shut down
	 // And say what format your command needs to be
	 if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

	 // Following the error message
	 // The first not ex17 arg is the name of the database file
	 char *filename = argv[1];
	 // Then a character dictating the switch statement
	 // Notice that only the first letter is read. So we could
	 // in theory use the entire word
	 char action = argv[2][0];
	 // Establish a connection by opening a database with the requisite
	 // action. Only 'c' or not 'c' matters.
	 struct Connection *conn = Database_open(filename, action);
	 // initialize id variable
	 int id = 0;

	 // If there are more than 3 variables, then convert the 4th arg
	 // to a row integer with atoi
	 if(argc > 3) id = atoi(argv[3]);
	 // If that number is bigger than the biggest number of rows
	 // Then cry and fail
	 if(id >= MAX_ROWS) die("There's not that many records.");

	 // Now check the action:
	 switch(action) {
		  // When creating a file for the first time, do 'c'
		  // and you will create a new database
		  // and write to a file with a blank
	 case 'c':
		  Database_create(conn);
		  Database_write(conn);
		  break;

		  // When getting something from it
	 case 'g':
		  // Only work when you only have 4 entries
		  if(argc != 4) die("Need an id to get");
		  // Then try to get the info in the data from the id
		  Database_get(conn, id);
		  break;

		  // When setting aka creating an entry in the database
	 case 's':
		  // Check to see you have exactly 6 arguments
		  if(argc != 6) die("Need id, name, email to set");

		  // Then set stuff using what you think to be
		  // id, name, email
		  Database_set(conn, id, argv[4], argv[5]);
		  // Then write the info in memory to the file
		  Database_write(conn);
		  break;

		  // Finally, if we want to delete it
	 case 'd':
		  // We only need the id so...
		  if(argc != 4) die("Need id, to delete");

		  // If we have it, we can delete it with the id
		  Database_delete(conn, id);
		  // Then write our changes to the file
		  Database_write(conn);
		  break;

		  // If we want to list something,
		  //we can have any number of arguments
	 case 'l':
		  // Then just print everything out
		  Database_list(conn);
		  break;

		  // If your action matches nothing, then simply
		  // tell the user the right actions
	 default:
		  die("Invalid action, only: c=create, g=get, s=set, d=delete");
	 }
	 // Finally, close the database so there are no memory leaks
	 Database_close(conn);

	 return 0;
}
