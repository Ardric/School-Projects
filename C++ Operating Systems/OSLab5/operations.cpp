/*
 *  Copyright 2012-2016 Robert Marmorstein
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "filesys.h"
#include "handle.h"
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

vector <FileHandle> F_Descriptors;

void Filesystem::format()
{
	//directory_size = (m_disk_size/1048) * 24;

	for (int i = 0; i < directory_size; i++)
	  m_disk[i] = '*';
}

bool Filesystem::create(const string name)
{
  d_entry* m_dir = (d_entry*) m_disk;
  int max_so_far = 0;
  int position = -1;

	for (int i = 0; i < (directory_size / 24); i++)
	{
	  if (name == m_dir[i].name)
	    return false;


	  if (strncmp(m_dir[i].name, "****************", 16) == 0)
	  {
	    if (position == -1)
	    	position = i;
	  }

	  else if (m_dir[i].pos > max_so_far)
	    max_so_far = m_dir[i].pos;

	  else if (m_dir[i].pos == 0 && max_so_far == 0)
	    max_so_far += 1024;
	}

	if (position == -1)
	  return false;

	else if (max_so_far < m_disk_size - directory_size)
	{
	  strcpy (m_dir[position].name, name.c_str());
	  
	  if (max_so_far > 0)
	    m_dir[position].pos = max_so_far + 1024;

	  else
	    m_dir[position].pos = max_so_far + directory_size;

	  m_dir[position].size = 0;

	  return true;
	}

	return false;
}

string Filesystem::list() const
{
  d_entry* m_dir = (d_entry*) m_disk;
  ostringstream so;


  for (int i = 0; i < (directory_size / 24); i++)
  {
    if (strncmp(m_dir[i].name, "****************", 16) == 0)
      continue;
    else
    {
      so << left << setw(16) << m_dir[i].name << left << setw(8) << to_string(m_dir[i].size) << "\n";
       
    }
  }
	return so.str();
}

bool Filesystem::rm(const string name)
{
  d_entry* m_dir = (d_entry*) m_disk;

	for (int i = 0; i < (directory_size / 24); i++)
	{
	  if (name == m_dir[i].name)
	  {
	    strcpy(m_dir[i].name, "****************");
	    return true;
	  }
	}
	return false;
}

bool Filesystem::rename(const string old_name, const string new_name) 
{
  d_entry* m_dir = (d_entry*) m_disk;
  bool name_exists = false;
  int position = -1;

	for (int i = 0; i < (directory_size / 24); i++)
	{
	  if (old_name == m_dir[i].name)
	    position = i;

	  if (strncmp(new_name.c_str(), m_dir[i].name, new_name.size()) == 0)
	  {
	    name_exists = true;
	  }

	}

	if (name_exists == false && position != -1)
	{
	  strncpy(m_dir[position].name, new_name.c_str(), 16);
	  return true;
	}

	return false;
}

bool Filesystem::copy(const string old_name, const string new_name)
{
  d_entry* m_dir = (d_entry*) m_disk;
  int max_so_far = 0;
  int position = -1;
  int old_pos = -1;

	for (int i = 0; i < (directory_size / 24); i++)
	{
	  if (new_name == m_dir[i].name)
	    return false;

	  if (old_name == m_dir[i].name)
	    old_pos = i;

	  if (strncmp(m_dir[i].name, "****************", 16) == 0)
	  {
	    if (position == -1)
	    	position = i;
	  }

	  else if (m_dir[i].pos > max_so_far)
	    max_so_far = m_dir[i].pos;

	  else if (m_dir[i].pos == 0 && max_so_far == 0)
	    max_so_far += 1024;
	}

	if (position == -1)
	  return false;

	else if (max_so_far < m_disk_size - directory_size && old_pos != -1)
	{
	  strcpy (m_dir[position].name, new_name.c_str());
	  
	  if (max_so_far > 0)
	    m_dir[position].pos = max_so_far + 1024;

	  else
	    m_dir[position].pos = max_so_far + directory_size;

	  m_dir[position].size = m_dir[old_pos].size;

	  for (int i = 0; i < 1024; i++)
	  {
	    m_disk[max_so_far + i] = m_disk[m_dir[old_pos].pos + i];
	  }

	  return true;
	}

	return false;
}

int Filesystem::open(const string name)
{
  FileHandle fd;
  d_entry* m_dir = (d_entry*) m_disk;

  for (int i = 0; i < (directory_size / 24); i++)
  {
    if (name == m_dir[i].name)
    {
      fd.pos = m_dir[i].pos;
      fd.size = m_dir[i].size;
      fd.offset = 0;
      if (F_Descriptors.size() == 256)
	break;
      F_Descriptors.push_back(fd);
      return F_Descriptors.size() - 1;
    }
  }

  return -1;

}

	
bool Filesystem::close(const int fd) const
{

  //int found = 0;

  if (fd > 255 || fd < 0)
    return false;

  else
  {
    if (F_Descriptors.size() <= fd)
      return false;
    else{
    F_Descriptors.erase(F_Descriptors.begin() + fd);
    return true;
    }
  }
}


bool Filesystem::read(const int fd, string &buffer, const unsigned int size) const
{
  int position = (F_Descriptors[fd].pos + F_Descriptors[fd].offset);
  if ((position + size) > m_disk_size)
   return false;

  if (F_Descriptors.size() <= fd)
   return false;

  if (fd > 255 || fd < 0)
   return false;

  for (int i = 0; i < size; i++)
  {
    buffer = buffer + m_disk[position + i];
  }

  return true;
}


bool Filesystem::write(const int fd, const string str, const unsigned int size){

  d_entry* m_dir = (d_entry*) m_disk;
  int position = (F_Descriptors[fd].pos + F_Descriptors[fd].offset);
  int dir;

  for (int i = 0; i < (directory_size / 24); i++)
   {
     if (m_dir[i].pos == F_Descriptors[fd].pos)
     {
       dir = i;
       break;
     }
   }

  if ((position + size) > m_disk_size)
    return false;

  if (F_Descriptors.size() <= fd)
    return false;

  if (fd > 255 || fd < 0)
    return false;

  for (int i = 0; i < size; i++)
  {
    m_disk[position + i] = str[i];
  }

  F_Descriptors[fd].size += size;
  F_Descriptors[fd].offset += size;

  m_dir[dir].size += size;

  return true;
}

bool Filesystem::isFragmented(){
  d_entry* m_dir = (d_entry*) m_disk;
 // int fragmented = 0;
  int check = 0;

  if (m_dir[0].name == "****************")
    check = 0;
  else
    check = 1;

  for (int i = 0; i < (directory_size / 24); i++)
  {
    if (check == 0 && m_dir[i].name != "****************")
    {
      return true;
    }

    else if (check == 1 && '*' == m_dir[i].name[0])
    {
      check = 0;
    }
  }

  return false;
}
void Filesystem::defragment(int start){

  d_entry* m_dir = (d_entry*) m_disk;
  int new_location = -1;
  string tmp = "";

  for (int i = start; i < (directory_size / 24); i++)
  {
    if ('*' == m_dir[i].name[0] && new_location == -1)
      new_location = i;
    else if (m_dir[i].name[0] != '*' && new_location != -1)
    {
      read_string(m_dir[i].pos, tmp, 1024);
      write_string(m_dir[new_location].pos, tmp, 1024);
      read_string(i, tmp, 16);
      write_string(new_location, tmp, 16);
      write_string(i, "****************", 16);
      defragment(i);
    }
  }
}
