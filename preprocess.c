#include "preprocess.h"

struct headerFile {
    char headerMacro[20];
    struct headerFile *next;
}*headerFiles;

struct headerFile *makeNode(char *macro) {
    struct headerFile *newNode = (struct headerFile *)malloc(sizeof(struct headerFile));
    strcpy(newNode->headerMacro, macro);
    newNode->next = NULL;
    
    return newNode;
}

void insertMacro(char *macro) {
    struct headerFile *newNode = makeNode(macro);
    if (headerFiles == NULL) {
        headerFiles = newNode;
        return;
    }
    
    struct headerFile *current = headerFiles;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
}

int isIncluded(char *macro) {
    if (headerFiles == NULL) {
        insertMacro(macro);
        return 0;
    }
    
    struct headerFile *current = headerFiles;
    
    while (current != NULL) {
        if (strcmp(current->headerMacro, macro) == 0) {
            return 1;
        }
        current = current->next;
    }
    
    insertMacro(macro);
    return 0;
}

int stringMatchN(char *line, char *key, int len) {
    if (strlen(line) < len) {
        return 0;
    }
    
    if (strlen(key) < len) {
        return 0;
    }
    
    for(int i = 0; i < len; i++) {
        if (line[i] != key[i]) {
            return 0;
        }
    }
    
    return 1;
}

void concat(char *a, char *b) {
    unsigned long i = strlen(a);
    unsigned long j = 0;
    for(;b[j] != '\0'; i++, j++) {
        a[i] = b[j];
    }
}

char *getMacro(char *line) {
    if (strlen(line) < 8) {
        return NULL;
    }
    
    int i;
    char *macro = (char *)malloc(sizeof(char) * 20);
    for (i = 8; line[i] != '\0'; i++) {
        if (line[i] == ' ' || line[i] == '\r' || line[i] == '\n') {
            break;
        }
        macro[i - 8] = line[i];
    }
    macro[i] = '\0';
    return macro;
}

char *isPreprocessor(char *line) {
    if (!stringMatchN(line, "#include", 8)) {
        return NULL;
    }
    
    int copy = 0;
    int fIndex = 0;
    char *filename = (char *)malloc(sizeof(char) * 20);
    for(int i = 0; line[i] != '\0'; i++) {
        if (copy) {
            filename[fIndex++] = line[i];
        }
        
        if (line[i] == '"') {
            copy = !copy;
        }
    }
    filename[fIndex - 1] = '\0';
    
    return filename;
}

char *readLine(FILE *source, int bufferSize) {
    if (source == NULL) {
        printf("Files Missing\n");
        exit(0);
    }
    
    char *line = (char *)malloc(sizeof(char) * bufferSize);
    if (fgets(line, bufferSize, source) == NULL)
        return NULL;
    return line;
}

void writeLine(FILE *target, char *line) {
    fprintf(target, "%s", line);
}

void preprocessor(FILE *source, FILE *target) {
    char *line = (char *)malloc(sizeof(char) * 100);
    if ((line = readLine(source, 100)) == NULL) {
        return;
    }
    
    if (stringMatchN(line, "#ifndef", 7)) {
        char *macro = getMacro(line);
        if (isIncluded(macro)) {
            free(macro);
            return;
        }
        free(macro);
    }
    
    char *filename;
    if ((filename = isPreprocessor(line)) != NULL) {
        //char filepath[100] = "/Users/ajayraj/Desktop/RecursiveIncludeLibrary/";
        //concat(filepath, filename);
        FILE *newSource = fopen(filename, "r");
        preprocessor(newSource, target);
        fclose(newSource);
    } else {
        writeLine(target, line);
    }
    preprocessor(source, target);
    free(filename);
    free(line);
}

void freeAll() {
    if (headerFiles->next == NULL) {
        free(headerFiles);
    }

    struct headerFile *current = headerFiles;
    struct headerFile *prev = NULL;

    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
}