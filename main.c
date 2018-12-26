//
//  main.c
//  Recursive Include
//
//  Created by Ajay Raj Nelapudi on 22/12/18.
//  Copyright © 2018 Ajay Raj Nelapudi. All rights reserved.
//

#include <stdio.h>
#include "preprocess.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Run as ./a.out <inputfile>\n");
    }
    
    FILE *source, *target;
    
    
    source = fopen(argv[1], "r");
    target = fopen("target.i", "w");
    
    preprocessor(source, target);
    
    freeAll();
    fclose(source);
    fclose(target);
    
    printf("Target File Generated: target.i\n");
    return 0;
}

