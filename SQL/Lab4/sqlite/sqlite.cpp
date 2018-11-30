#include <iostream>
#include "sqlite3.h"

using namespace std;

const char* str_to_charptr (string x)
{
  const char* ret = reinterpret_cast<const char*>(x.c_str());
  return ret;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for (i = 0; i < argc; i++)
  {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void dumpdatabase(sqlite3 * db, const char* printer)
{
  sqlite3_stmt * prep;

  if ( sqlite3_prepare(db, printer, -1, &prep, nullptr) == SQLITE_OK)
  {
    unsigned int cols = sqlite3_column_count(prep);
    int result = 0;

    while (true)
    {
      result = sqlite3_step(prep);
      if(result == SQLITE_ROW)
      {
        for (unsigned int i = 0; i < cols; ++i)
        {
	  cout << sqlite3_column_text(prep, i) << endl;
        }
      }
      else
      {
        break;
      }
    }
  }
  sqlite3_finalize(prep);
}

void ModifyDatabase(sqlite3 * db, const char* printer)
{
  int check;
  char *zErrMsg = 0;

  check = sqlite3_exec(db, printer, callback, 0, nullptr);
  if (check != SQLITE_OK){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else{
    fprintf(stdout, "Operation executed successfully\n");
  }
}

void registrar(sqlite3 * db)
{
 string word, name, ID, section, course, department, teacher, cap, schedule, period, semester, CRN;
 cout << "To add students, teachers or classes to the database," << endl;
 cout << "type students, teachers or classes." << endl;
 cout << "If you would like to delete something from a table, please type delete." << endl;
 cout << "If you would like to update something in a table, please type update." << endl;

 cin >> word;

 if (word == "students")
 {
   cout << "Please type student name." << endl;
   cin >> word;
   name = word;
   cout << "Please type student ID." << endl;
   cin >> word;
   ID = word;
   string x = "insert into students values('" + name + "','" + ID + "');";
   const char* printer = str_to_charptr(x);
   ModifyDatabase(db, printer);
 }

 if (word == "teachers")
 {
   cout << "Please type teacher name." << endl;
   cin >> word;
   name = word;
   cout << "Please type teacher ID." << endl;
   cin >> word;
   ID = word;
   string x = "insert into teachers values('" + name + "','" + ID + "');";
   const char* printer = str_to_charptr(x);
   ModifyDatabase(db, printer);
 }

 if (word == "classes")
 {
   cout << "Please type section number." << endl;
   cin >> section;
   cout << "Please type class name." << endl;
   cin >> course;
   cout << "Please type department name." << endl;
   cin >> department;
   cout << "Please type teacher name." << endl;
   cin >> teacher;
   cout << "Please type class cap." << endl;
   cin >> cap;
   cout << "Please type when the class will be held." << endl;
   cin >> schedule;
   cout << "Please type class period." << endl;
   cin >> period;
   cout << "Please type semester class will be held." << endl;
   cin >> semester;
   cout << "Please type the CRN of the class." << endl;
   cin >> CRN;
   string x = "insert into classes values('" + section + "','" + course + "','" + department + "','" + teacher + "','" + cap + "','" + schedule + "','" + period + "','" + semester + "','" + CRN + "');";
   const char* printer = str_to_charptr(x);
   ModifyDatabase(db, printer);
 }

 if (word == "delete")
 {
   cout << "Please enter the table you want to delete from." << endl;
   cin >> word;
   if (word == "teachers")
   {
     const char* print = "select * from teachers;";
     dumpdatabase(db, print);
     cout << "Listed above are the current teachers in the teachers table." << endl;
     cout << "Please enter the teachers instructorID that you want to delete." << endl;
     cin >> word;
     string x = "delete from teachers where instructorID = '" + word + "';";
     const char* printer = str_to_charptr(x);
     ModifyDatabase(db, printer);
   }

   if (word == "students")
   {
     const char* print = "select * from students;";
     dumpdatabase(db, print);
     cout << "Listed above are the current students in the students table." << endl;
     cout << "Please enter the students studentID that you want to delete." << endl;
     cin >> word;
     string x = "delete from students where studentID ='" + word + "';";
     const char* printer = str_to_charptr(x);
     ModifyDatabase(db, printer);
   }

   if (word == "classes")
   {
     const char* print = "select * from classes;";
     dumpdatabase(db, print);
     cout << "Listed above are the current classes in the classes table." << endl;
     cout << "Please enter the class section you want to delete from the table." << endl;
     cin >> section;
     cout << "Please enter the class name you want to delete from the table." << endl;
     cin >> course;
     string x = "delete from classes where section = '" + section + "' and class = '" + course + "';";
     const char* printer = str_to_charptr(x);
     ModifyDatabase(db, printer);
   }
 }

 if (word == "update")
 {
   cout << "Please enter the table you want to update." << endl;
   cin >> word;
   if (word == "teachers")
   {
     const char* print = "select * from teachers;";
     dumpdatabase(db, print);
     cout << "Listed above are the current teachers in the teachers table." << endl;
     cout << "Please enter the updated teachers name." << endl;
     cin >> name;
     cout << "Please enter the ID of the teacher you changed." << endl;
     cin >> ID;
     string x = "update teachers set instructor = '" + name + "' where instructorID = '" + ID + "';";
     const char* printer = str_to_charptr(x);
     ModifyDatabase(db, printer);
    }

     if (word == "students")
     {
       const char* print = "select * from students;";
       dumpdatabase(db, print);
       cout << "Listed above are the current students in the students table." << endl;
       cout << "Please enter the updated students name." << endl;
       cin >> name;
       cout << "Please enter the ID of the student you changed." << endl;
       cin >> ID;
       string x = "update students set student = '" + name + "' where studentID = '" + ID + "';";
       const char* printer = str_to_charptr(x);
       ModifyDatabase(db, printer);
     }

     if (word == "classes")
     {
       const char* print = "select * from classes;";
       dumpdatabase(db, print);
       cout << "Listed above are the current courses in the classes table." << endl;
       cout << "Please enter the section of the course you want to change." << endl;
       cin >> section;
       cout << "Please enter the department of the class you want to change." << endl;
       cin >> department;
       cout << "Please enter what you want to change about the class." << endl;
       cout << "With the current set up, you can not change section or department." << endl;
       cin >> word;
       if (word == "class")
       {
         cout << "Enter the updated class name." << endl;
	 cin >> word;
	 string x = "update classes set class = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }

       if (word == "instructor")
       {
         cout << "Enter the updated instructor name." << endl;
	 cin >> word;
	 string x = "update classes set instructor = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }

       if (word == "cap")
       {
         cout << "Enter the updated cap." << endl;
	 cin >> word;
	 string x = "update classes set cap = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }

       if (word == "schedule")
       {
         cout << "Enter the updated schedule." << endl;
	 cin >> word;
	 string x = "update classes set schedule = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }

       if (word == "period")
       {
         cout << "Enter the updated period." << endl;
	 cin >> word;
	 string x = "update classes set period = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }

       if (word == "semester")
       {
         cout << "Enter the updated semester." << endl;
	 cin >> word;
	 string x = "update classes set semester = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }

       if (word == "CRN")
       {
	 cout << "Enter the updated CRN." << endl;
	 cin >> word;
	 string x = "update classes set CRN = '" + word + "' where section = '" + section + "' and department = '" + department + "';";
	 const char* printer = str_to_charptr(x);
	 ModifyDatabase(db, printer);
       }
     }
 }
}
 

void teacher(sqlite3 * db)
{
  string word;
  cout << "Please specify which instructor you are." << endl;
  cout << "Vault for Vault-Tec, Grey for Grey Beards and Guards for Guards." << endl;

  cin >> word;

  if (word == "Vault")
  {
    const char* printer = "select * from classes where classes.instructor = 'Vault-Tec';";
    dumpdatabase(db, printer);
  }

  if (word == "Grey")
  {
    const char* printer = "select * from classes where classes.instructor = 'Grey Beards';";
    dumpdatabase(db, printer);
  }

  if (word == "Guards")
  {
    const char* printer = "select * from classes where classes.instructor = 'Guards';";
    dumpdatabase(db, printer);
  }
}

void student(sqlite3 * db)
{
  string word, day, time1, time2, tablename, section, course, CRN;

  cout << "Please type in the information you would like to access." << endl;
  cout << "Your options are classes by term, department, or professor." << endl;
  cout << "Term options are: Spring 2017 and Fall 2017. Type Fall or Spring to select term." << endl;
  cout << "Department options are: Fallout and Elder Scrolls. Type Fallout or Elder to choose." << endl;
  cout << "Professor options are: Vault-Tec, Grey Beards and Guards. Type Vault, Grey or Guards to choose." << endl;
  cout << "If you would like to see classes listed by when they meet type schedule." << endl;
  cout << "If you are a student in the database that wants to sign up for classes, enter create if it is your first time or update if you just want to edit your existing schedule." << endl;
  cout << "If you have registered for classes and would like to see your current schedule type dumpschedule." << endl;
  cin >> word;

  
  if (word == "Guards")
  {
    const char* printer = "select * from classes where classes.instructor = 'Guards';";
    dumpdatabase(db, printer);
  }

  if (word == "Grey")
  {
    const char* printer = "select * from classes where classes.instructor = 'Grey Beards';";
    dumpdatabase(db, printer);
  }

  if (word == "Vault")
  {
    const char* printer = "select * from classes where classes.instructor = 'Vault-Tec';";
    dumpdatabase(db, printer);
  }

  if (word == "Fallout")
  {
    const char* printer = "select * from classes where classes.department = 'Fallout';";
    dumpdatabase(db, printer);
  }
  
  if (word == "Elder")
  {
    const char* printer = "select * from classes where classes.department = 'Elder Scrolls';";
    dumpdatabase(db, printer);
  }

  if (word == "Fall")
  {
    const char* printer = "select * from classes where classes.semester = 'Fall 2017';";
    dumpdatabase(db, printer);
  }

  if (word == "Spring")
  {
    const char* printer = "select * from classes where classes.semester = 'Spring 2017';";
    dumpdatabase(db, printer);
  }

  if (word == "schedule")
  {
    cout << "Enter MWF or TR to look at specific schedule times." << endl;
    cin >> day;
    cout << "Enter the first time period your looking for classes between." << endl;
    cin >> time1;
    cout << "Enter the second time period your looking for classes between." << endl;
    cin >> time2;
    string x = "select * from classes where classes.schedule = '" + day + "' and period between '" + time1 + "' and '" + time2 + "';";
    const char* printer = str_to_charptr(x);
    dumpdatabase(db, printer);
  }

  if (word == "create")
  {
    cout << "Please enter your name + ID to create your table for registration. Example: Bob198." << endl;
    cin >> tablename;
    string x = "create table " + tablename + "(section text, class text, department text, instructor text, cap int, schedule text, period int, semester text, CRN int);";
    const char* printer = str_to_charptr(x);
    ModifyDatabase(db, printer);
  }

  if (word == "update")
  {
    const char* print = "select * from classes;";
    dumpdatabase(db, print);
    cout << "Listed above is a list of the current available classes." << endl;
    cout << "Please enter your name+ ID to select what table you are adding to. Example: Bob198." << endl;
    cin >> tablename;
    cout << "Please enter the CRN of the class you want to add." << endl;
    cin >> CRN;
    string x = "insert into " + tablename + " select * from classes where classes.CRN = '" + CRN + "';";
    const char* printer = str_to_charptr(x);
    ModifyDatabase(db, printer); 
  }

  if (word == "dumpschedule")
  {
    cout << "Please enter your name + ID to see your current schedule." << endl;
    cin >> tablename;
    string x = "select * from " + tablename + ";";
    const char* printer = str_to_charptr(x);
    dumpdatabase(db, printer);
  }
}

int main(int argc, char * argv[])
{
  sqlite3 * db;
  sqlite3_open(argv[1], &db);
  string arg2 = argv[2];

  if (arg2 == "student")
  {
    student(db);
  }

  if (arg2 == "teacher")
  {
    teacher(db);
  }

  if (arg2 == "registrar")
  {
    registrar(db);
  }

  sqlite3_close(db);

return 0;
}

