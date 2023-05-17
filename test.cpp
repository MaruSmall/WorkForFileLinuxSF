#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include "LibChat.h"

using namespace std;

int main()
{
    string path_u = getenv("HOME");
    string doc_path_u = path_u+"/user.txt";

    const char* user_path = doc_path_u.c_str();
    fstream user_file = fstream(doc_path_u, ios::in|ios::out);

    if(!user_file.is_open())
    {
        user_file = fstream(doc_path_u, ios::in| ios::out|ios::trunc);

        if(user_file)
        {
            User user("Mary", "mary","123");
            user_file<<user<<endl;
            user_file.seekg(0,ios_base::beg);
            user_file>>user;
            user_file.seekg(0,ios_base::beg);
            string u_temp;

            user_file >>u_temp;
            cout<<"Name: ";
            cout<<u_temp<<endl;
            user_file>>u_temp;
            cout<<"Login: "<<u_temp<<endl;
            user_file>>u_temp;
            cout<<"Password: ";
            cout<<u_temp<<endl;

        }
        else
        {
            cout<<"Could not open file user.txt"<<endl;
            return 0;
        }
    }

    chmod(user_path, S_IRWXU);
    user_file.close();

    string doc_path_m = path_u+"/message.txt";
    const char* mes_path = doc_path_m.c_str();

    fstream message_file = fstream(mes_path, ios::in|ios::out|ios::app);

    if(!message_file)
    {
        message_file = fstream(mes_path, ios::in|ios::out|ios::trunc | ios::app);
    }

    if(message_file)
    {
        Message mes("Hello friend of mine", "Mary", "Anton");

        message_file<<mes <<endl;
        message_file.seekg(0, ios_base::beg);
        message_file>>mes;
        message_file.seekg(0, ios_base::beg);

        string m_temp;

        while(!message_file.eof())
        {
            m_temp = "";
            message_file >>m_temp;
            if(m_temp=="")
            {
                break;
            }

            cout<<"Sender: "<<m_temp<<endl;
            message_file>>m_temp;
            cout<<"Receiver: "<<m_temp<<endl;
            getline(message_file, m_temp);
            cout<<"Text: "<<m_temp<<endl;
        }
    }
    else
    {
        cout<<"Could not open file message.txt"<<endl;
    }

    chmod(mes_path, S_IRWXU);
    message_file.close();

    return 0;

}