// Include all the requisite libraries

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Define the two below as constants by the C pre-processor. 
/* #define MAX_DATA 512 */
/* #define MAX_ROWS 100 */

struct Address {
	 int id;
	 int set;
	 char *name;
	 char *email;

};



struct Database {
	 int MAX_DATA;
	 int MAX_ROWS;
	 struct Address *rows;
};

struct Connection {
	 FILE *file;
	 struct Database *db;
};

void Database_close(struct Connection *conn);


void die(const char *message, struct Connection *conn)
{
	 if(errno) {
		  perror(message);
	 } else {

		  printf("ERROR: %s\n", message);
	 }
	 
	 Database_close(conn); // Free memory

	 if(conn) Database_close(conn);
	 exit(1);
}


void Address_print(struct Address *addr)
{
	 printf("%d %s %s\n",
			addr->id, addr->name, addr->email);
}


void Database_load(struct Connection *conn)
{
	 int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

	 if(rc != 1) die("Failed to load database.", conn);

	 const int MAX_ROWS = conn->db->MAX_ROWS;
	 const int MAX_DATA = conn->db->MAX_DATA;
	 int i = 0;
	 
	 conn->db->rows = malloc(MAX_ROWS * sizeof(struct Address));
	 
	 for (i = 0; i < MAX_ROWS; ++i) {
		  rc = fread(&conn->db->rows[i], sizeof(struct Address),
					 1 , conn->file);
		  if(rc != 1) die("Failed to load rows.", conn);
		  conn->db->rows[i].name = malloc(sizeof(char)*MAX_DATA);
		  conn->db->rows[i].email = malloc(sizeof(char)*MAX_DATA);
		  rc = fread(conn->db->rows[i].name, sizeof(char),
					 MAX_DATA, conn->file);
		  if(rc != MAX_DATA) die("Failed to load name.", conn);
		  rc = fread(conn->db->rows[i].email, sizeof(char),
					 MAX_DATA, conn->file);
		  if(rc != MAX_DATA) die("Failed to load email.", conn);

	 }
}


struct Connection *Database_open(const char *filename, char mode)
{
	 struct Connection *conn = malloc(sizeof(struct Connection));

	 if(!conn) die("Memory error", conn); 


	 conn->db = malloc(sizeof(struct Database));
	 if(!conn->db) die("Memory error", conn);

	 if(mode == 'c') {
		  conn->file = fopen(filename, "w");
	 } else {
		  conn->file = fopen(filename, "r+");


		  if(conn->file) {
			   Database_load(conn);
		  }
	 }


	 if(!conn->file) die("Failed to open the file", conn);
	 
	 return conn;
}


void Database_close(struct Connection *conn)
{
	 int i = 0;
	 struct Address *cur_row = NULL;

	 if(conn) {

		  if(conn->file) fclose(conn->file);
		  if(conn->db) {
			   if(conn->db->rows) {
			   		for(i = 0; i < conn->db->MAX_ROWS; i++) {
						 cur_row = &conn->db->rows[i];
						 if(cur_row) {
							  free(cur_row->name);
							  free(cur_row->email); 
						 }
			   		}
					free(conn->db->rows);
			   }
			   free(conn->db);
		  }
		  // Of course, we shold always free the memory associated with
		  // the connection data structure.
		  free(conn);
	 }

}



// A function which returns nothing and accepts
// a pointer of type Connection
void Database_write(struct Connection *conn)
{

	 rewind(conn->file);

	 int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);


	 if(rc != 1) die("Failed to write database", conn);

	 const int MAX_ROWS = conn->db->MAX_ROWS;
	 const int MAX_DATA = conn->db->MAX_DATA;
	 int i = 0;
	 
	 for(i = 0; i < MAX_ROWS; i++) {
		  rc = fwrite(&conn->db->rows[i], sizeof(struct Address),
					  1, conn->file);
		  if(rc != 1) die("Failed to write rows", conn);
		  
		  rc = fwrite(conn->db->rows[i].name,
					  sizeof(char), MAX_DATA,
					  conn->file);
		  if(rc != MAX_DATA) die("Failed to load name", conn);
		  rc = fwrite(conn->db->rows[i].email,
					  sizeof(char), MAX_DATA,
					  conn->file);
		  if(rc != MAX_DATA) die("Failed to load name", conn);
	 }

		  
	 rc = fflush(conn->file);
	 if(rc == -1) die("Cannot flush database.", conn);
}


void Database_create(struct Connection *conn, const int MAX_ROWS, const int MAX_DATA)
{
	 int i = 0;


	 conn->db->MAX_ROWS = MAX_ROWS;
	 conn->db->MAX_DATA = MAX_DATA;
	 conn->db->rows = malloc(sizeof(struct Address)*MAX_ROWS);

	 for(i = 0; i < MAX_ROWS; i++) {
		  // make a prototype to initialize it
		  struct Address *addr = malloc(sizeof(struct Address));
		  addr->id = i;
		  addr->set = 0;
		  addr->name = memset(malloc(sizeof(char)*MAX_DATA), 0, MAX_DATA);
		  addr->email = memset(malloc(sizeof(char)*MAX_DATA), 0, MAX_DATA);
		  
		  conn->db->rows[i] = *addr;
		  free(addr);
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


	 const int MAX_DATA = conn->db->MAX_DATA;
	 if(addr->set) die("Already set, delete it first", conn);

	 // Say that it is set. Well of course it is, you just set it
	 addr->set = 1;
	 // WARNING: bug, read the "How to Break it" and fix this
	 char *res = strncpy(addr->name, name, MAX_DATA);
	 addr->name[MAX_DATA-1] = '\0';
	
	 // demonstrate the strncpy bug
	 if(!res) die("Name copy failed", conn);

	 
	 // Same thing as above
	 res = strncpy(addr->email, email, MAX_DATA);
	 
	 addr->email[MAX_DATA-1] = '\0';
	 if(!res) die("Email copy failed", conn);
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
		  die("ID is not set", conn);
	 }
}

void Database_find(struct Connection *conn, char *term)
{
	 int i = 0;
	 int rc = 0;
	 int MAX_ROWS = conn->db->MAX_ROWS;

	 for(i = 0; i < MAX_ROWS; i++){
		  struct Address *addr = &conn->db->rows[i];
		  if (addr->set) {
		
			   if(addr->set) rc = strncmp(term, addr->name,
										  sizeof(term));

			   if(rc != 0) rc = strcmp(term, addr->email);
		
			   if(rc == 0) {
					Address_print(addr);
					break;
			   }
		  }
	 }

}


// Function which returns nothing
// and accepts a pointer of type connection and an integer
void Database_delete(struct Connection *conn, int id)
{
	 struct Address *addr = malloc(sizeof(struct Address));

	 int MAX_DATA = conn->db->MAX_DATA;
	 
	 addr->set = 0;
	 addr->id = id;
	 addr->name = malloc(sizeof(char)*MAX_DATA);
	 addr->email = malloc(sizeof(char)*MAX_DATA);
	 memset(addr->name, 0, MAX_DATA);
	 memset(addr->email, 0, MAX_DATA);
	 // Then set the row of the database concerned to this 'zero' address


	 if(conn->db->rows[id].name)  free(conn->db->rows[id].name);
	 if(conn->db->rows[id].email)   free(conn->db->rows[id].email);
	 conn->db->rows[id] = *addr;

	 free(addr);
	 
	 
}

// Function that returns nothing and accepts
// a pointer of type connection
void Database_list(struct Connection *conn)
{
	 // Initialize by making a counter
	 // And having a pointer of type database
	 int i = 0;
	 struct Database *db = conn->db;

	 for(i = 0; i < db->MAX_ROWS; i++) {
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
	 if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

	 // No connection established so the connection is null

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
	 
	 int MAX_ROWS = 0;
	 int MAX_DATA = 0;
	 // If there are more than 3 variables, then convert the 4th arg
	 // to a row integer with atoi
	 if(argc > 3 && action != 'c')  id = atoi(argv[3]);
	 if(action == 'c') {
		  MAX_ROWS = atoi(argv[3]);
		  MAX_DATA = atoi(argv[4]);
	 } else {
		  MAX_ROWS = conn->db->MAX_ROWS;
		  MAX_DATA = conn->db->MAX_DATA;
	 }
	 
	 // If that number is bigger than the biggest number of rows
	 // Then cry and fail

	 // if(id >= MAX_ROWS) die("There's not that many records.", conn);

	 // Now check the action:
	 switch(action) {
		  // When creating a file for the first time, do 'c'
		  // and you will create a new database
		  // and write to a file with a blank
	 case 'c':
		  if(argc != 5) die("Need MAX_ROWS and MAX_DATA", conn);

		  //if(!(typeof()))
		  // Need to detect that the 4th and the 5th elements are integers
		  Database_create(conn, MAX_ROWS, MAX_DATA);
		  Database_write(conn);
		  break;

		  // When getting something from it
	 case 'g':
		  // Only work when you only have 4 entries
		  if(argc != 4) die("Need an id to get", conn);
		  // Then try to get the info in the data from the id
		  Database_get(conn, id);
		  break;

		  // When setting aka creating an entry in the database
	 case 's':
		  // Check to see you have exactly 6 arguments

		  if(argc != 6) die("Need id, name, email to set", conn);


		  // Then set stuff using what you think to be
		  // id, name, email
		  Database_set(conn, id, argv[4], argv[5]);
		  // Then write the info in memory to the file
		  Database_write(conn);
		  break;

	 case 'u':
		  if (argc != 6) die("Need id, name, email to update",
							 conn);
		  Database_delete(conn,id);
		  Database_set(conn, id, argv[4], argv[5]);
		  Database_write(conn);
		  break;
		  
		  // Finally, if we want to delete it
	 case 'd':
		  // We only need the id so...
		  if(argc != 4) die("Need id, to delete", conn);

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

	 case 'f':
		  if(argc != 4) die("Need a term to search", conn);
		  Database_find(conn, argv[3]);
		  break;

	 
		  
	 default:

		  die("Invalid action, only: c=create, g=get, s=set, d=delete f=find, u=update", conn);

	 }
	 // Finally, close the database so there are no memory leaks
	 Database_close(conn);

	 return 0;
}
