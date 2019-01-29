/*
 * mapper.c -- simple file that mmap()s a file region and prints it
 *
 * Copyright (C) 1998,2000,2001 Alessandro Rubini
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 *   how to test: ./scullsingleTest /dev/scullsingle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char **argv)
{
    char *fname;
    FILE *f, *f1;
    unsigned long offset, itemlen, itemsize;
    itemsize = 1;
    itemlen = 1024;
	char buffer[1024];

    fname=argv[1];

    if (!(f=fopen(fname,"r"))) {
        fprintf(stderr, "%s: %s: %s\n", argv[0], fname, strerror(errno));
        exit(1);
    }
    if (!(f1=fopen(fname,"r"))) {
        fprintf(stderr, "%s: %s: %s\n", argv[0], fname, strerror(errno));
        exit(1);
    }

//	fread(buffer, itemsize, itemlen, f);
    fclose(f);
    fclose(f1);

    return 0;
}
