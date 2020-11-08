#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
//#include"MatlabEngine.hpp"
//#include"NewHacks.hpp"

class Hospital
{
	int hospital_bed_no;
	char name[30];
	char address[50];
	char phone[10];

	public:
	void main_menu();	   //to display the main menu
	void add();		   //to book a hospital_bed
	void display();	           //to display the Patient record
	void hospital_beds();	   //to display allotted hospital_beds
	void edit();	           //to edit the Patient record
	int check(int);	           //to check hospital_bed status
	void modify(int);	   //to modify the record
	void delete_rec(int);      //to delete the record
	void CallPlotGraph();           //to graph the number of beds
};

/* void Hospital::CallPlotGraph()
{


    // Start MATLAB engine synchronously
    unique_ptr<MatlabEngine> matlabPtr = startMATLAB();

    // Call MATLAB function and return result
    matlabPtr->NewHacks(u"NewHacks", hospital_bed_no);
} */

void Hospital::main_menu()
{	int choice;
	while(choice!=5)
	{
		clrscr();
		cout<<"\n\t\t\t\t+++++++++++++";
		cout<<"\n\t\t\t\t+ MAIN MENU +";
		cout<<"\n\t\t\t\t+++++++++++++";
		cout<<"\n\n\t\t\t1.Book A Hospital Bed";
		cout<<"\n\t\t\t2.Patient Record";
		cout<<"\n\t\t\t3.Hospital beds Allotted";
		cout<<"\n\t\t\t4.Edit Record";
		cout<<"\n\t\t\t5. Bar Graph";
		cout<<"\n\t\t\t6.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;

		switch(choice)
		{			case 1: add();
					break;
			case 2: display();
					break;
			case 3: hospital_beds();
					break;
			case 4: edit();
					break;

		       //	case 5: CallPlotGraph();


			case 6:clrscr();
					  cout<<"\n\n\t\t\t THANK YOU FOR YOUR TIME!!!!  ";
				 getch();
					break;
			default:cout<<"\n\n\t\t\tWrong choice!!!";
				      cout<<"\n\t\t\t\t\t\t\t\t\tPress any key to continue!!";
				    getch();
		}
	}
}
void Hospital::add()
{	clrscr();
	int r,flag;
	ofstream o1("Record.dat",ios::app);

	cout<<"\n Enter Patient Detalis";
	cout<<"\n ______________________";
	cout<<"\n\n Hospital bed no: ";
	cin>>r;
	flag=check(r);



if(flag)
		cout<<"\n Sorry..!!!Hospital bed is already booked";
	else
	{
		hospital_bed_no=r;
		cout<<" Name: ";
		gets(name);
		cout<<" Address: ";
		gets(address);
		cout<<" Phone No: ";
		gets(phone);
		o1.write((char*)this,sizeof(Hospital));
		cout<<"\n  You have booked the hospital bed!!!";
	}
	cout<<"\n Press any key to continue!!";
	getch();
	o1.close();
}

void Hospital::display()
{        clrscr();
	ifstream i1("Record.dat",ios::in);
	int r,flag=0;
	cout<<"\n Enter hospital bed no: ";
	cin>>r;

	while(i1.read((char*)this,sizeof(Hospital)))
	{
	if(hospital_bed_no==r)
		{
			cout<<"\n\t Patient Details";
			cout<<"\n ________________________";
			cout<<"\n\n Hospital bed no: "<<hospital_bed_no;
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Phone no: "<<phone;
			flag=1;
			break;
		}
	}
	if(flag==0)
	  cout<<"\n Sorry Hospital bed no. not found or vacant!!";
	cout<<"\n\n Press any key to continue!!";
	getch();
	i1.close();
}

void Hospital::hospital_beds()
{
	clrscr();
	ifstream i1("Record.dat",ios::in);
	cout<<"\n\t\t\tList Of Hospital beds Allotted";
	cout<<"\n\t\t\t+++++++++++++++++++++";
	cout<<"\n\n Hospital bed No.\tName\t\tAddress\t\tPhone No.\n";

	while(i1.read((char*)this,sizeof(Hospital)))
	{
		cout<<"\n\n "<<hospital_bed_no<<"\t\t"<<name;
		cout<<"\t\t"<<address<<"\t\t"<<phone;
	}
	cout<<"\n\n\n\t\t\tPress any key to continue!!";
	getch();
	i1.close();
}


void Hospital::edit()
{
	clrscr();
	int choice,r;

	cout<<"\n \tEDIT MENU";
	cout<<"\n ___________________";
	cout<<"\n\n 1.Modify Patient Record";
	cout<<"\n 2.Delete Patient Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;
	clrscr();
	cout<<"\n Enter hospital bed no: ";
	cin>>r;

	switch(choice)
	{
		case 1: modify(r);
				break;
		case 2: delete_rec(r);
				break;
		default: cout<<"\n Wrong Choice!!";
	}

	cout<<"\n Press any key to continue!!!";
	getch();
}


int Hospital::check(int r)
{
	int flag=0;
	ifstream i1("Record.dat",ios::in);
	while(i1.read((char*)this,sizeof(Hospital)))
	{
		if(hospital_bed_no==r)
		{
			flag=1;
				break;
		}
	}
	i1.close();
	return(flag);
}

void Hospital::modify(int r)
{
	long pos,flag=0;
	fstream file("Record.dat",ios::in|ios::out|ios::binary);
	while(file.read((char*)this,sizeof(Hospital)))
	{
		pos=file.tellg();


	if(hospital_bed_no==r)
		{
			cout<<"\n\t Enter New Details";
			cout<<"\n ____________________________";
			cout<<"\n Name: ";
			gets(name);
			cout<<" Address: ";
			gets(address);
			cout<<" Phone no: ";
			gets(phone);

			file.seekg(pos-sizeof(Hospital));
			file.write((char*)this,sizeof(Hospital));
			cout<<"\n Record is modified!!";
			flag=1;
			break;
		}
	}

	if(flag==0)
		cout<<"\n Sorry Hospital_bed no. not found or vacant!!";

	file.close();
}

void Hospital::delete_rec(int r)
{
	int flag=0;
	char ch;
	ifstream i1("Record.dat",ios::in);
	ofstream o1("temp.dat",ios::out);

	while(i1.read((char*)this,sizeof(Hospital)))
	{
		if(hospital_bed_no==r)
		{
			cout<<"\n Name: "<<name;
			cout<<"\n Address: "<<address;
			cout<<"\n Pone No: "<<phone;
			cout<<"\n\n Do you want to delete this record(y/n): ";
			cin>>ch;

			if(ch=='n')
			o1.write((char*)this,sizeof(Hospital));

			flag=1;
		}
		else
			o1.write((char*)this,sizeof(Hospital));
	}
	i1.close();
	o1.close();

	if(flag==0)
		cout<<"\n Sorry hospital_bed no. not found or vacant!!";
	else
	{
		remove("Record.dat");
		rename("temp.dat","Record.dat");
	}
}

void main()
{
	Hospital h;

	clrscr();
	cout<<"\n\t\t\t++++++++++++++++++++++++++++";
	cout<<"\n\t\t\t+ Newhacks Hospital database +";
	cout<<"\n\t\t\t++++++++++++++++++++++++++++";

	cout<<"\n\n\n\n\t\tMade By:";

	cout<<"\n\tLavanya\n\tHarshit\n\tChahit\n";
   cout<<endl<<endl<<"WELCOME to the Hospital management database system click a key so we can decide how to help you";
   getch();
	h.main_menu();
}
