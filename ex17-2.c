#include <stddef.h>
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
    int max_rows;
    int max_data;
    struct Address *rows;  
};

/**
 * Description: connection file in ROM and db in RAM
 */
struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message) {
    if (errno) {
        // system call or library function error
        perror(message);
    } else {
        // custom function error
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Database_close(struct Connection *conn); 

void diec(const char *message, struct Connection *conn) {
    if (errno) {
        // system call or library function error
        perror(message);
    } else {
        // custom function error
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr) {
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

/**
 * Description: read data from ROM to RAM
 * Note: The way the database is organized determines how the database is loaded
 * Call By: Database_open 
 */ 
void Database_load(struct Connection *conn) {
    assert(conn->db && conn->file);
    if (!(conn->db && conn->file)) diec("Invalid Connection Info", conn);   

    // First: load (int)max_rows & (int)max_data
    if (fread(&conn->db->max_rows, sizeof(conn->db->max_data), 1, conn->file) != 1) {
        diec("Failed to loaded database's MAX_ROWS", conn);
    }
    if (fread(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file) != 1) {
        diec("Failed to loaded database's MAX_ROWS", conn);
    }
    
    // Second: load ((struct Address)[max_rows])row
    if (!conn->db->rows) diec("Failed to loaded database's rows", conn);
    
    // Third: load every struct Address
    for (size_t i = 0; i < conn->db->max_rows; ++i) {
        // 1. Load (int)id
        if (fread(&conn->db->rows[i].id, sizeof(conn->db->rows[i].id), 1, conn->file) != 1) {
            diec("Failed to load database element's id", conn);
        } 
        // 2. Load (int)set
        if (fread(&conn->db->rows[i].set, sizeof(conn->db->rows[i].set), 1, conn->file) != 1) {
            diec("Failed to load database element's set", conn);
        } 
        // 3. Load (char[max_data])name
        if (fread(&conn->db->rows[i].name, sizeof(char) * conn->db->max_data, 1, conn->file) != 1) {
            diec("Failed to load database element's name", conn);
        } 
        // 4. Load (char[max_data])email
        if (fread(&conn->db->rows[i].email, sizeof(char) * conn->db->max_data, 1, conn->file) != 1) {
            diec("Failed to load database element's email", conn);
        } 
    } 
}

/**
 * Description: open database depend on various modes
 * Call: Database_load
 * Return value: upon successful completion, return a Connection pointer
 */
struct Connection *Database_open(const char *filename, char mode) {
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory error");

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

    // TODO
    // Close database and free memory
    
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file);

    // TODO 
    // Write database from ram to rom 

    int rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.");
}

/**
 * Description: 
 */
void Database_create(struct Connection *conn) {
    printf("MAX_ROWS: ");
    scanf("%d", &conn->db->max_rows);
    if (conn->db->max_rows <= 0) diec("MAX_ROWS must be positive.", conn);

    printf("MAX_ROWS: ");
    scanf("%d", &conn->db->max_data);
    if (conn->db->max_data <= 0) diec("MAX_DATA must be positive.", conn);

    conn->db->rows = (struct Address *)malloc(sizeof(struct Address *) * conn->db->max_rows);

    for (int i = 0; i < conn->db->max_rows; ++i) {
        conn->db->rows[i].id = i;
        conn->db->rows[i].set = 0;
        conn->db->rows[i].name = (char *)malloc(sizeof(char) * conn->db->max_data);
        conn->db->rows[i].name = (char *)memset(conn->db->rows[i].name, 0, conn->db->max_data);  
        conn->db->rows[i].email = (char *)malloc(sizeof(char) * conn->db->max_data);
        conn->db->rows[i].email = (char *)memset(conn->db->rows[i].email, 0, conn->db->max_data);
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first");

    // TODO

    addr->set = 1;
    // WARING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    addr->name[MAX_DATA - 1] = '\0';
    // demonstrate the strncpy bug
    if (!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    addr->name[MAX_DATA - 1] = '\0';
    if (!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; ++i) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
    
    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);

    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("There's not that many records.");
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
