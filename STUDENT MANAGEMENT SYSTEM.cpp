#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Student{
    int rollNo;
    string name;
    float grade;
    Student* next;
};

void addStudent(Student*& head, int rollNo, string name, float grade){
    // Check for duplicate roll number
    Student* temp=head;
    while(temp){
        if(temp->rollNo==rollNo){
            cout<<"Error: Roll number already exists!\n";
            return;
        }
        temp=temp->next;
    }
    
    Student* newStudent=new Student{rollNo, name, grade, NULL};
    if(!head){
        head=newStudent;
    } else{
        temp=head;
        while(temp->next) temp=temp->next;
        temp->next=newStudent;
    }
    cout<<"Student added successfully!\n";
}

void displayStudents(Student* head){
    if(!head){
        cout<<"No student records found.\n";
        return;
    }
    
    cout<<"\n=== STUDENT RECORDS ===\n";
    cout<<left<<setw(10)<<"Roll No"<<setw(20)<<"Name"<<setw(10)<<"Grade"<<"\n";
    cout<<string(40, '-')<<"\n";
    
    Student* temp=head;
    while(temp){
        cout<<left<<setw(10)<<temp->rollNo 
            <<setw(20)<<temp->name 
            <<setw(10)<<fixed<<setprecision(2)<<temp->grade<<"\n";
        temp=temp->next;
    }
}

void searchStudent(Student* head, int rollNo){
    Student* temp=head;
    while(temp){
        if(temp->rollNo==rollNo){
            cout<<"\nStudent Found:\n";
            cout<<"Roll No: "<<temp->rollNo<<"\n";
            cout<<"Name: "<<temp->name<<"\n";
            cout<<"Grade: "<<fixed<<setprecision(2)<<temp->grade<<"\n";
            return;
        }
        temp=temp->next;
    }
    cout<<"Student with Roll No "<<rollNo<<" not found.\n";
}

void updateStudent(Student* head, int rollNo){
    Student* temp=head;
    while(temp){
        if(temp->rollNo==rollNo){
            cout<<"Enter new name: ";
            cin.ignore();
            getline(cin, temp->name);
            cout<<"Enter new grade: ";
            cin>>temp->grade;
            cout<<"Student record updated successfully!\n";
            return;
        }
        temp=temp->next;
    }
    cout<<"Student not found.\n";
}

void deleteStudent(Student*& head, int rollNo){
    if(!head){
        cout<<"No students in records.\n";
        return;
    }
    
    if(head->rollNo==rollNo){
        Student* toDelete=head;
        head=head->next;
        delete toDelete;
        cout<<"Student record deleted successfully.\n";
        return;
    }
    
    Student* temp=head;
    while(temp->next && temp->next->rollNo!=rollNo){
        temp=temp->next;
    }
    
    if(temp->next){
        Student* toDelete=temp->next;
        temp->next=temp->next->next;
        delete toDelete;
        cout<<"Student record deleted successfully.\n";
    } else{
        cout<<"Student not found.\n";
    }
}

void calculateStatistics(Student* head){
    if(!head){
        cout<<"No student records available.\n";
        return;
    }
    
    int count=0;
    float total=0, highest=head->grade, lowest=head->grade;
    Student* temp=head;
    
    while(temp){
        count++;
        total += temp->grade;
        if(temp->grade > highest) highest=temp->grade;
        if(temp->grade < lowest) lowest=temp->grade;
        temp=temp->next;
    }
    
    cout<<"\n=== STATISTICS ===\n";
    cout<<"Total Students: "<<count<<"\n";
    cout<<"Average Grade: "<<fixed<<setprecision(2)<<(total / count)<<"\n";
    cout<<"Highest Grade: "<<highest<<"\n";
    cout<<"Lowest Grade: "<<lowest<<"\n";
}

void cleanup(Student*& head){
    while(head){
        Student* temp=head;
        head=head->next;
        delete temp;
    }
}

int main(){
    Student* head=NULL;
    int choice, rollNo;
    string name;
    float grade;

    cout<<"=== STUDENT MANAGEMENT SYSTEM ===\n";
    
    do{
        cout<<"\n1. Add Student\n2. Display Students\n3. Search Student\n"
            <<"4. Update Student\n5. Delete Student\n6. Statistics\n7. Exit\n"
            <<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter Roll No: "; 
                cin>>rollNo;
                cin.ignore();
                cout<<"Enter Name: "; 
                getline(cin, name);
                cout<<"Enter Grade: "; 
                cin>>grade;
                addStudent(head, rollNo, name, grade);
                break;
                
            case 2:
                displayStudents(head);
                break;
                
            case 3:
                cout<<"Enter Roll No to search: "; 
                cin>>rollNo;
                searchStudent(head, rollNo);
                break;
                
            case 4:
                cout<<"Enter Roll No to update: "; 
                cin>>rollNo;
                updateStudent(head, rollNo);
                break;
                
            case 5:
                cout<<"Enter Roll No to delete: "; 
                cin>>rollNo;
                deleteStudent(head, rollNo);
                break;
                
            case 6:
                calculateStatistics(head);
                break;
                
            case 7:
                cout<<"Exiting program. Goodbye!\n";
                break;
                
            default:
                cout<<"Invalid choice. Please try again.\n";
        }
    } while(choice!=7);

    cleanup(head);
    
    return 0;
}
