#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//#define MAX_DATA 512
//#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};
/*
struct Database {
    struct Address rows[MAX_ROWS];  
};
*/
/**
 * Description: connection file in ROM and db in RAM
 */
struct Connection {
    FILE *file;
    struct Address *db;
    int MAX_DATA;
    int MAX_ROWS;
};

void die(const char *message) {
    if (errno) {
        // system call or library function error
        perror(message);
    } else {
        // custom function error
        printf("ERROR: %s\n", message);
    }
;
    exit(1);
}

void Address_print(struct Address *addr) {
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

/**
 * Description: read data from ROM to RAM
 * Call By: Database_open 
 */ 
void Database_load(struct Connection *conn) {
    //if (rc != 1) die("Failed to load database.");
    int rc = fread(conn->db, sizeof(struct Address) * conn->MAX_ROWS, 1, conn->file);   
    if (rc != 1) die("Failed to load database.");
    int i = 0;
    for (i = 0; i < conn->MAX_ROWS; ++i) {
        rc = fread(conn->db[i].name, sizeof(char) * conn->MAX_DATA, 1, conn->file);
        if (rc != 1) die("Failed to load database");
        rc = fread(conn->db[i].email, sizeof(char) * conn->MAX_DATA, 1, conn->file);
        if (rc != 1) die("Failed to load database");
    }
}

/**
 * Description: open database depend on various modes
 * Call: Database_load
 * Return value: upon successful completion, return a Connection pointer
 */
struct Connection *Database_open(const char *filename, char mode, int max_data, int max_rows) {
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error");
    
    conn->MAX_DATA = max_data;
    conn->MAX_ROWS = max_rows;

    conn->db = malloc(sizeof(struct Address) * max_rows);
    if (!conn->db) die("Memory error");
    for (int i = 0; i < conn->MAX_ROWS; ++i) {
        conn->db[i].name = malloc(sizeof(char) * conn->MAX_DATA);
        if (!conn->db[i].name) die("Memory error");
        conn->db[i].email = malloc(sizeof(char) * conn->MAX_DATA);
        if (!conn->db[i].email) die("Memory error");
    }

    if (mode == 'c') {
        // Truncate file to zero length or 
        // create text file for writing.
        conn->file = fopen(filename, "w");
    } else {
        // Open for reading and writing.
        conn->file = fopen(filename, "r+");
        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file);
    
    //int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    //if (rc != 1) die("Failed to write database.");

    int rc = fwrite(conn->db, sizeof(struct Address) * conn->MAX_ROWS, 1, conn->file);
    if (rc != 1) die("Failed to write database."); 
    int i = 0;
    for (i = 0; i < conn->MAX_ROWS; ++i) {
        rc = fwrite(conn->db[i].name, sizeof(char) * conn->MAX_DATA, 1, conn->file); 
        if (rc != 1) die("Failed to write database.");
        rc = fwrite(conn->db[i].email, sizeof(char) * conn->MAX_DATA, 1, conn->file); 
        if (rc != 1) die("Failed to write database.");
    }

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
}

void Database_create(struct Connection *conn) {
    int i = 0;

    for (i = 0; i < conn->MAX_ROWS; ++i) {
        // make a prototype to initialize it
        struct Address addr = { .id = i, .set = 0 };
        // the just assign it
        conn->db[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
    struct Address *addr = &conn->db[id];
    if (addr->set) die("Already set, delete it first");

    addr->set = 1;
    // WARING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->MAX_DATA);
    addr->name[conn->MAX_DATA - 1] = '\0';
    // demonstrate the strncpy bug
    if (!res) die("Name copy failed");

    res = strncpy(addr->email, email, conn->MAX_DATA);
    addr->name[conn->MAX_DATA - 1] = '\0';
    if (!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address addr = {.id = id, .set = 0};
    conn->db[id] = addr;
}

void Database_list(struct Connection *conn) {
    int i = 0;

    for (i = 0; i < conn->MAX_ROWS; ++i) {
        struct Address *cur = &conn->db[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
    
    char *filename = argv[1];
    char action = argv[2][0];
    int max_rows = 0, max_data = 0;
    if (action == 'c') {
        max_rows = atoi(argv[3]);
        max_data = atoi(argv[4]);
    }
    struct Connection *conn = Database_open(filename, action, max_rows, max_data);

    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (id >= conn->MAX_ROWS) die("There's not that many records.");
    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
