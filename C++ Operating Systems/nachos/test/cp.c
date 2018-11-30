char* template = "How to use:  cp [Source][Destination]";
   int templateLen = 37;

   char* invalidFile = "Unable to open file.";
   int invalidLen = 20;

   int readSize;
   int writeSize;
   int readFileSize;
   int writeFileSize;

   char* fileInfo[1000];
   char* readFile[55];
   char* writeFile[55];

   OpenFileId* readFrom;
   OpenFileId* writeTo;

   char c;

  while(Read(&c, 1, ConsoleInpt))
{
  for(int i = 0; i < 55; i++)
  {
        readFileSize = Read(readFile, 1, ConsoleInput);
        if(readFile[i] == ' ')
        {
                for(int j = 0; j < 55; i++)
                {
                 writeFileSize = Read(writeFile, 1, ConsoleInput;
                if(writeFile[i] == ' ' || writeFile[i] == '\n')
                        break;
                }
        }
  }
}

readFrom = Open(readFile);
writeTo = Open(writeFile);

if(readFrom == NULL)
        Write(template, templateLen, ConsoleOutput);
        return 0;

else if(writeFrom == NULL)

{       Create(writeFile);
        writeTo = Open(writeFile);
        readSize = Read(fileInfo, 1, readFrom);
        Write(fileInfo, readSize, writeTo);

        close(writeFrom);
}
close(readFrom);

return 0;
}

