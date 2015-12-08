//
//  kernel.cpp
//  OS
//
//  Created by Adam Kopeć on 9/26/15.
//  Copyright © 2015 Adam Kopeć. All rights reserved.
//

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "terminal.cpp"

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This kernel will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void kernel_main() {
    /* Initialize terminal interface */
    Terminal terminal;   //TODO: Move to stdio.h
    
    terminal.printf("Hello!\nWelcome to BetaOS!\n");
    
    while (1) {
        //terminal.printf("BetaOS: ");*
        terminal.getcommand();
    }
}
