#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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



void die(const char *message)
{
	 if(errno) {
		  perror(message);
	 } else {
		  printf("ERROR: %s\n", message);
	 }

	 exit(1);
	 
}

void Database_create(struct Connection *conn, const int MAX_ROWS, const int MAX_DATA)
{
	 int i = 0;
	 conn->db->MAX_ROWS = MAX_ROWS;
	 conn->db->MAX_DATA = MAX_DATA;

	 conn->db->rows = malloc(sizeof(struct Address) * MAX_ROWS);
	 assert(conn->db->rows != NULL);
	 
	 for(i = 0; i < MAX_ROWS; i++) {
		  struct Address *addr = malloc(sizeof(struct Address));
		  addr->set = 0;
		  addr->id = i;
		  addr->name = malloc(sizeof(char)*MAX_DATA);
		  addr->email = malloc(sizeof(char)*MAX_DATA);
		  if(i == 1) {
			   addr->set = 1;
			   strcpy(addr->name, "zed");
			   strcpy(addr->email, "zed@zedshaw.com");
		  }
		  conn->db->rows[i] = *addr;
		  free(addr);
	 }


	 
}

void Database_write(struct Connection *conn)
{
	 rewind(conn->file);
	 int MAX_ROWS = conn->db->MAX_ROWS;	 
	 int MAX_DATA = conn->db->MAX_DATA;
	 
	 int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	 if(rc != 1) die("Failed to write database. ");


}


void Database_load(struct Connection *conn)
{
	 
}

struct Connection *Database_open(const char *filename, char mode)
{
	 struct Connection *conn = malloc(sizeof(struct Connection));
	 if(!conn) die("Memory error");

	 conn->db = malloc(sizeof(struct Database));
	 if(!conn->db) die("Memory error");

	 if(mode == 'c') {
		  conn->file = fopen(filename, "w");
	 } else {
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
	 int i = 0;
	 
	 if(conn) {
		  if(conn->file) fclose(conn->file);
		  if(conn->db) {
			   if(conn->db->rows) {
					for(i = 0; i < conn->db->MAX_ROWS; i++){
						 if(conn->db->rows[i].name)  free(conn->db->rows[i].name);
						 if(conn->db->rows[i].email)  free(conn->db->rows[i].email);
					}
					free(conn->db->rows);
			   }
			   free(conn->db);
		  }
		  free(conn);
	 }
}

int main(int argc, char *argv[])
{
	 char *filename = argv[1];
	 char action = argv[2][0];
	 struct Connection *conn = Database_open(filename, action);
	 int id = 0;
	 
	 Database_create(conn, 10, 50);

	 printf("For row %d user %s his email is %s\n",
			conn->db->rows[1].id,
			conn->db->rows[1].name,
			conn->db->rows[1].email);	 
	 Database_close(conn);

	 
	 return 0;
}
