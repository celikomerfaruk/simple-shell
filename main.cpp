#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <sys/wait.h>

using namespace std;

int executeCommand(string cmd, string arg1, string arg2)
{
    pid_t pid = fork(); //creating child proccess
    if (pid < 0)        //if failed
    {
        return 1;
    }
    else if (pid == 0) //if it's child process
    {

        if (cmd == "mycomputername")
        {
            execlp("/bin/hostname", "hostname", NULL); //execute /bin/hostname
        }
        else if (cmd == "listdir")
        {
            execlp("/bin/ls", "ls", NULL); //execute /bin/ls
        }
        else if (cmd == "whatsmyip")
        {
            system("hostname -i"); //execute /bin/hostname -i
        }
        else if (cmd == "printfiletwo")
        {
            string param = "cp " + arg1 + " " + arg2;
            system(param.c_str()); //execute /bin/cp from first arguement to second
        }
        else if (cmd == "hellotext")
        {
            system("gedit"); //execute gedit from command line
        }
        exit(0);
    }
    else
    {
        wait(NULL); //parent process wait for child
    }
    return 0;
}

int main()
{
    cout << "Welcome! It's great to see you again." << endl; //welcome message
    string user = getenv("USER");                            //username
    string command_hist[15];                                 //string array for keep history
    int histindex = 0;

    while (1) //loop continues until exit command
    {
        if (histindex == 15)
        {
            histindex = 0; //if it reaches 15 elements, add new command in place of oldest one
        }
        string input;
        string command;
        cout << user << " >>> ";
        getline(cin, input);   //get input
        stringstream s(input); //to split input
        string args[6];        //to keep words of input
        int argcount = 0;      //to keep number of words in input
        string tmparg;
        while (s >> tmparg) //splitting input
        {
            args[argcount] = tmparg;
            argcount++;
        }
        command = args[0]; //first word is command name

        if (command == "exit")
        {
            break; //finish program
        }

        if (command != "dididothat")
        {
            string quotecommand = "\"" + input + "\""; //quotation mark is appended to the beginning and the end
            command_hist[histindex] = quotecommand;    //quoted input added to the history
            histindex++;
        }

        if (command == "printfile")
        {

            if (argcount == 2)
            {
                ifstream input(args[1]);
                for (string line; getline(input, line);) //read file
                {
                    cout << line; //read and write file line by line
                    cin.ignore(); //when user click enter continue with next line
                }
            }
            else if (argcount == 4)
            {
                executeCommand("printfiletwo", args[1], args[3]); //printfile with two files
            }
        }
        else if (command == "dididothat")
        {
            string::size_type start_pos = 0;
            string::size_type end_pos = 0;
            string quotedText;

            start_pos = input.find("\""); //find quotation mark in input
            if (start_pos != string::npos)
            {
                start_pos++;
                end_pos = input.find("\""); //find second quotation mark in input
                if (end_pos != string::npos)
                {
                    quotedText = input.substr(start_pos, end_pos - start_pos); //get the part enclosed in the quotation marks
                }
            }
            string query = "\"" + quotedText; //final format

            string res = "No";
            for (int i = 0; i < 15; i++)
            {
                if (command_hist[i] == query)
                {
                    res = "Yes"; // if quoted input has found in command history array print yes; otherwise false
                }
            }
            cout << res << endl;
        }
        else
        {
            executeCommand(command, "s", "s"); //for other commands, s has no meaning
        }
    }

    return 0;
}
