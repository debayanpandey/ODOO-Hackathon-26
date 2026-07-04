
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct User{
    int id;
    string name;
    string email;
    string password;
    string role;
    int salary;
    int attendanceDays;
    bool checkedInToday;
    string leaveStatus;
    string leaveReason;
};

User users[50];
int userCount=0;

void clearInput(){
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

bool emailExists(const string &mail){
    for(int i=0;i<userCount;i++)
        if(users[i].email==mail) return true;
    return false;
}

void setupDefaultAdmin(){
    users[0]={101,"HR Manager","admin@hrms.com","admin123","Admin",80000,0,false,"None",""};
    userCount=1;
}

void signUp(){
    if(userCount>=50){
        cout<<"Database Full!\n";
        return;
    }

    User u;
    u.id=101+userCount;
    clearInput();

    cout<<"Full Name: ";
    getline(cin,u.name);

    cout<<"Email: ";
    getline(cin,u.email);

    if(emailExists(u.email)){
        cout<<"Email already registered!\n";
        return;
    }

    cout<<"Password (min 6 chars): ";
    getline(cin,u.password);

    if(u.password.length()<6){
        cout<<"Password too short!\n";
        return;
    }

    u.role="Employee";
    u.salary=25000;
    u.attendanceDays=0;
    u.checkedInToday=false;
    u.leaveStatus="None";
    u.leaveReason="";

    users[userCount++]=u;

    cout<<"\nRegistration Successful!\n";
    cout<<"Employee ID : "<<u.id<<"\n";
}

void employeeDashboard(int i){
    int ch;
    do{
        cout<<"\n====== EMPLOYEE DASHBOARD ======\n";
        cout<<"1.Profile\n2.Check In\n3.Apply Leave\n4.Leave Status\n5.Logout\nChoice: ";
        cin>>ch;

        switch(ch){
        case 1:
            cout<<"\nID : "<<users[i].id
                <<"\nName : "<<users[i].name
                <<"\nEmail : "<<users[i].email
                <<"\nSalary : "<<users[i].salary
                <<"\nAttendance : "<<users[i].attendanceDays
                <<"\nLeave : "<<users[i].leaveStatus<<"\n";
            break;

        case 2:
            if(users[i].checkedInToday){
                cout<<"Already checked in today.\n";
            }else{
                users[i].attendanceDays++;
                users[i].checkedInToday=true;
                cout<<"Attendance marked successfully.\n";
            }
            break;

        case 3:
            clearInput();
            cout<<"Leave Reason: ";
            getline(cin,users[i].leaveReason);
            users[i].leaveStatus="Pending";
            cout<<"Leave request submitted.\n";
            break;

        case 4:
            cout<<"Current Status : "<<users[i].leaveStatus<<"\n";
            break;
        }
    }while(ch!=5);
}

void adminDashboard(){
    int ch;
    do{
        cout<<"\n======= ADMIN DASHBOARD =======\n";
        cout<<"1.View Employees\n2.Leave Requests\n3.Update Salary\n4.Logout\nChoice: ";
        cin>>ch;

        if(ch==1){
            for(int i=0;i<userCount;i++){
                cout<<"\nID:"<<users[i].id
                    <<" | "<<users[i].name
                    <<" | "<<users[i].role
                    <<" | Attendance:"<<users[i].attendanceDays
                    <<" | Salary:"<<users[i].salary;
            }
            cout<<"\n";
        }

        else if(ch==2){
            bool found=false;
            for(int i=0;i<userCount;i++){
                if(users[i].leaveStatus=="Pending"){
                    found=true;
                    cout<<"\n"<<users[i].name<<" -> "<<users[i].leaveReason<<"\n";
                    cout<<"1.Approve 2.Reject : ";
                    int x; cin>>x;
                    users[i].leaveStatus=(x==1)?"Approved":"Rejected";
                }
            }
            if(!found) cout<<"No pending requests.\n";
        }

        else if(ch==3){
            int id,sal;
            cout<<"Employee ID : ";
            cin>>id;

            bool found=false;
            for(int i=0;i<userCount;i++){
                if(users[i].id==id){
                    cout<<"New Salary : ";
                    cin>>sal;
                    users[i].salary=sal;
                    cout<<"Salary Updated.\n";
                    found=true;
                    break;
                }
            }
            if(!found) cout<<"Employee not found.\n";
        }
    }while(ch!=4);
}

void signIn(){
    string email,password;
    clearInput();
    cout<<"Email : ";
    getline(cin,email);
    cout<<"Password : ";
    getline(cin,password);

    for(int i=0;i<userCount;i++){
        if(users[i].email==email && users[i].password==password){
            cout<<"\nWelcome "<<users[i].name<<"\n";
            if(users[i].role=="Admin")
                adminDashboard();
            else
                employeeDashboard(i);
            return;
        }
    }
    cout<<"Invalid Login!\n";
}

int main(){
    setupDefaultAdmin();

    int ch;
    do{
        cout<<"\n=====================================\n";
        cout<<" HUMAN RESOURCE MANAGEMENT SYSTEM\n";
        cout<<"=====================================\n";
        cout<<"1.Sign In\n2.Sign Up\n3.Exit\nChoice : ";
        cin>>ch;

        switch(ch){
        case 1: signIn(); break;
        case 2: signUp(); break;
        case 3: cout<<"Thank you!\n"; break;
        default: cout<<"Invalid Choice\n";
        }
    }while(ch!=3);

    return 0;
}
