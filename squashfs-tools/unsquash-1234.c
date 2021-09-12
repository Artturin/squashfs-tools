/*
 * Unsquash a squashfs filesystem.  This is a highly compressed read only
 * filesystem.
 *
 * Copyright (c) 2021
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * unsquash-1234.c
 *
 * Helper functions used by unsquash-1, unsquash-2, unsquash-3 and
 * unsquash-4.
 */

#include "unsquashfs.h"

/*
 * Check name for validity, name should not
 *  - be ".", "./", or
 *  - be "..", "../" or
 *  - have a "/" anywhere in the name, or
 *  - be shorter than the expected size
 */
int check_name(char *name, int size)
{
	char *start = name;

	if(name[0] == '.') {
		if(name[1] == '.')
			name++;
		if(name[1] == '/' || name[1] == '\0')
			return FALSE;
	}

	while(name[0] != '/' && name[0] != '\0')
		name ++;

	if(name[0] == '/')
		return FALSE;

	if((name - start) != size)
		return FALSE;

	return TRUE;
}


void squashfs_closedir(struct dir *dir)
{
	int i;

	for(i = 0; i < dir->dir_count; i++)
		free(dir->dirs[i].name);

	free(dir->dirs);
	free(dir);
}
