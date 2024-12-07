#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

// function that lets the user view the tasks
int viewTasks (const string& filename) {
    // open view in file stream
    fstream view;
    vector<string> vec; // variable to store the retreived tasks from the file
    vector<int> isCompleted; // variable to store the retrieved status of task completion from the file
    int temp; // buffer to store completion status
    string line; // buffer between file and vector variable

    view.open(filename, ios::in);
    if (view.fail()) {
        cout<<"Error occured while opening file. Code: 2"<<endl;
        return 2;
    }
    while(!(view.eof())) {
        view>>temp;
        isCompleted.push_back(temp);
        getline(view, line);
        vec.push_back(line);
    }
    if((vec.size()-1)==0) {
        cout<<"No taks are available. You can rest for now...or can you?"<<endl;
        return -1;
    }
    for(int i=0; i<isCompleted.size()-1; i++) {
        if (isCompleted[i]) {
            cout<<"[X] "<<vec[i]<<endl;
        } else {
            cout<<"["<<i+1<<"] "<<vec[i]<<endl;
        }
    }
    view.close();
    return 1;
}

// function to write tasks into the file
int writeTasks (const string& filename) {
    string line; // hold the task title

    // read the task title
    cout<<"Enter a task: ";
    getline(cin, line);

    if(line=="0") {
        cout<<"Going back to main menu..."<<endl;
        return 123;
    }
    
    // open a file in append mode and write the contents of line to the file "tasks.txt"
    fstream ofile;
    ofile.open(filename, ios::app);
    if(ofile.bad()) {
        cout<<"Error opening file. Code: 3";
        return 3;
    }
    ofile<<0<<" "<<line<<endl;
    ofile.close();
    return 1;
}

// function to count the number of tasks stored in the file
int countTasks (const string& filename) {
    vector<string> v; // holds the vectors from the tasks.txt file
    string line; // buffer

    ifstream ifile (filename);
    if(ifile) {
        while(getline(ifile, line)) {
            v.push_back(line);
        }
        return v.size();
    } else {
        cout<<"Error reading file. Code: 4"<<endl;
        return 0;
    }
    ifile.close();
    return 0;
}

// function to delete a task
int deleteTask (const string& filename) {
    // show the tasks so that the user can choose which task to delete
    viewTasks(filename);

    vector<string> vec; // to store the tasks from task.txt
    string line; // buffer
    int choice; // index of the task the user wants to delete

    // open file in input mode
    ifstream ifile(filename);
    if(ifile.fail()) {
        cout<<"Error opening file. Code: 5";
        return 5;
    }

    // read the tasks from the file and push it into vec
    while(getline(ifile, line)) {
        vec.push_back(line);
    }
    ifile.close();

    // ask the user the task to delete
    cout<<endl;
    cout<<"Which task do you want to delete?\n->";
    cin>>choice;
    if(choice == 0) {
        cout<<"Going back to main menu..."<<endl;
        return 123;
    }
    choice--;
    // cout<<vec.size();
    if (choice>=vec.size()) {
        cout<<"I kid you not, there are fewer tasks than that. err_code: 102"<<endl;
        return 102;
    }

    // open file in output mode to write the file contents except the deleted one
    ofstream ofile(filename);
    if(ofile.fail()) {
        cout<<"Error opening file. Code: 5";
        return 5;
    }
    // write into the file
    for(int i=0; i<vec.size(); i++) {
        if (i==choice) {
            continue;
        } else {
            ofile<<vec[i]<<endl;
        }
    }
    ofile.close();
    return 1;
}

// function to mark a task as completed
int completeTask (const string& filename, int choice) {
    vector<int> isComplete; // to hold the new values of the completion status
    int temp; // buffer
    vector<string> vec; // to hold the lines temporarily from the file
    string line; // buffer

    // read the completion status and task titles from tasks.txt
    ifstream ifile (filename);
    if(ifile.fail()) {
        cout<<"Error opening file. err_code: 1002"<<endl;
        return 1002;
    }

    while(!(ifile.eof())) {
        ifile>>temp;
        isComplete.push_back(temp);
        getline(ifile, line);
        vec.push_back(line);
    }

    ifile.close();

    // mark the chosen task as completed
    isComplete[choice]=1;

    // write the new completion status and task titles back into the file
    ofstream ofile(filename);
    if(ofile.fail()) {
        cout<<"Error opening file. err_code: 1002";
        return 1002;
    }
    for(int i=0; i<vec.size()-1;i++) {
        ofile<<isComplete[i];
        ofile<<vec[i]<<endl;
    }
    ofile.close();
    return 1;
}

// function to delete all tasks
int deleteAll (const string& filename) {
    ofstream ofile(filename);
    if(ofile.fail()) {
        cout<<"Error opening file. err_code: 122"<<endl;
        return 122;
    }
    ofile.close();
    return 1;
}

// function to delete completed tasks
int deleteCompleted (const string& filename) {
    vector<int> isComplete; // to hold the new values of the completion status
    int temp; // buffer
    vector<string> vec; // to hold the lines temporarily from the file
    string line; // buffer

    // read completion status and task titles from the file tasks.txt
    ifstream ifile (filename);
    if(ifile.fail()) {
        cout<<"Error opening file. err_code: 1004"<<endl;
        return 1004;
    }

    while(!(ifile.eof())) {
        ifile>>temp;
        isComplete.push_back(temp);
        getline(ifile, line);
        vec.push_back(line);
    }

    ifile.close();

    // write all tasks except the ones that have completion status 1
    ofstream ofile(filename);
    if(ofile.fail()) {
        cout<<"Error opening file. err_code: 127"<<endl;
        return 127;
    }
    for (int i=0; i<vec.size()-1; i++) {
        if(isComplete[i]==1) {
            continue;
        } else {
            ofile<<isComplete[i]
                <<vec[i]<<endl;
        }
    }
    return 1;
}

// shows the list of commands that can be performed and returns the chosen command to the main function
int menu (int count) {
    char n;
    cout<<"=============================="<<endl
        <<setw(20)<<"TO-DO LIST"<<endl
        <<"=============================="<<endl
        <<setw(21)<<"Total Tasks: "<<count<<endl
        <<"=============================="<<endl
        <<endl
        <<"1. View tasks"<<endl
        <<"2. Add task"<<endl
        <<"3. Mark a task to be marked as completed"<<endl
        <<"4. Delete a task"<<endl
        <<"5. Delete all tasks"<<endl
        <<"6. Delete completed tasks"<<endl
        <<"7. Exit program"<<endl
        <<endl
        <<"Choose what to-do: ";
        cin>>n;
        cin.ignore();
        cout<<endl<<endl;
        if (int(n)>=48 && int(n)<=55) {
            return int(n)-48;
        } else {
            return -1;
        }
        return 0;
}

int main() {
    int choice = 0; // initialize choice for storing the value returned by the menu function
    int count = 0; // variable to store the number of tasks
    char tempchar1 = '\0', tempchar2 = '\0'; // this variable is used in the code for exiting the program
    string line; // variable used to assist reading from the file into the vector t
    const string filename = "tasks.txt";

    // get the number of tasks from the file and store it in count
    count = countTasks(filename);

    while(true) {
        choice = menu(count); // stores the command choice of the user

        // switch statements to perform the corresponding command
        switch (choice) {
            // code for reading tasks from tasks.txt and displaying it on the console screen
            case 1:
            // call viewtasks() and send "tasks.txt" as a parameter
                if(viewTasks(filename)) {     
                    cout<<endl<<"Hit enter to go back.";
                    cin.get(tempchar1);
                } else return 2;
            break;

            // code for adding a task to the tasks.txt file
            case 2:
                if (writeTasks(filename)==1) {
                    cout<<"Task entered successfully!"<<endl;
                    count=countTasks(filename);
                } else {
                    break;
                };
            break;

            // code for marking a task as completed
            case 3:
                if (count!=0) {
                    viewTasks(filename)==2;

                    cout<<endl;
                    cout<<"Which task have you completed?\n-> ";
                    cin>>choice;
                    // if user enters 0 go back to main menu
                    if (choice==0) {
                        cout<<"Going back to main menu..."<<endl;
                        break;
                    } else if(choice>count) {
                        cout<<"Are there even that many tasks? I think not."<<endl;
                    }
                    choice--;

                    // call complete task function that will overwrite the status contents of the file according to the choice made by user
                    if(completeTask(filename, choice)) {
                        cout<<"Task has been marked as completed! Way to go!"<<endl;
                    } else {
                        cout<<"unexpected error has occured. err_code: 1001"<<endl;
                        return 1001;
                    }
                } else {
                    cout<<"Have mercy...Add a few tasks first."<<endl;
                }
            break;

            // code for deleting a task
            case 4:
                if (count!=0) {
                    deleteTask(filename);
                    count = countTasks(filename);
                } else {
                    cout<<"You need tasks to be able to delete them... I think."<<endl;
                }
            break;
            
            // code for deleting all the tasks
            case 5:
                if (count == 0) {
                    cout<<"No tasks to be deleted."<<endl;
                    break;
                }
                cout<<"Are you sure you want to delete all tasks?(Y/N)\n-> ";
                cin>>tempchar1;
                if(!(tempchar1=='Y' || tempchar1=='y')) {
                    break;
                }
                if(deleteAll(filename)==1) {
                    cout<<"All tasks have been deleted."<<endl;
                    count = countTasks(filename);
                } else {
                    cout<<"Unsuccessful attempt."<<endl;
                }
            break;

            // code for deleting completed tasks
            case 6:
                cout<<"Are you sure you want to delete completed tasks?(Y/N)\n-> ";
                cin>>tempchar1;
                cin.ignore();
                if(!(tempchar1=='Y' || tempchar1=='y')) {
                    cout<<"Tasks not deleted. Going back to main menu..."<<endl;
                    break;
                }
                if (count==0) {
                    cout<<"No tasks to be deleted..."<<endl;
                    break;
                }
                if (deleteCompleted(filename)==1) {
                    cout<<"Completed tasks have been deleted. "<<endl;
                    count = countTasks(filename);
                } else {
                    cout<<"Unexpected error occured."<<endl;
                }
            break;

            // code for exiting program
            case 7:
                cout<<"Are you sure you want to exit? (Y/N)"<<endl;
                cin>>tempchar2;
            break;
            // default case
            default:
                cout<<"Please enter a valid choice."<<endl;
            break;
            
        }

        // functionality to loop the program until the user enters Y or y after choosing to exit the program
        if (tempchar2=='Y' || tempchar2=='y') {
            cout<<"Thank you for using TO-DO List."<<endl;
            break;
        }
        cout<<endl<<endl;
    }
    

    // system("pause>0"); // it is a platform specific function, bad practice
    return 0;
}