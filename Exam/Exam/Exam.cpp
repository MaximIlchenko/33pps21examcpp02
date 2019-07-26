// Exam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<functional>
#include<string>
#include<list>
using namespace std;

struct ISalaryCalculator
{
	virtual double calcSalary() = 0;
};
//1 почасовой оклад
class Rule1 : public ISalaryCalculator
{
protected:
	double hour;
	double rate;
public:
	Rule1() { hour = 0; rate = 0; }
	Rule1(double hour, double rate) { this->hour = hour; this->rate = rate; }
	virtual double calcSalary()
	{
		return hour * rate;
	}
};
//2 оплата оклад + премия
class Rule2 : public ISalaryCalculator
{
protected:
	double base;
	double premium;
public:
	Rule2() { base = 0; premium = 0; }
	Rule2(double base, double premium)
	{
		this->base = base;
		this->premium = premium;
	}
	virtual double calcSalary()
	{
		return base + premium;
	}
};
//3 база + % от выручки
class Rule3 :public ISalaryCalculator
{
protected:
	double base;
	double percent;
public:
	Rule3() { base = 0; percent = 0; }
	Rule3(double base, double percent)
	{
		this->base = base;
		this->percent = percent;
	}
	virtual double calcSalary()
	{
		return base + (base*percent);
	}
};
//4 оклад
class Rule4 : public ISalaryCalculator
{
protected:
	double base;
public:
	Rule4() { base = 0; }
	Rule4(double base) { this->base = base;  }
	virtual double calcSalary()
	{
		return base;
	}
};

class AdressInfo
{
protected:
	string city;
	string street;
	string home;
	string room;
public:
	AdressInfo()
	{
		this->city = "none";
		this->street = "none";
		this->home = "none";
		this->room = "none";
	}
	AdressInfo(string city, string street, string home, string room)
	{
		this->city = city;
		this->street = street;
		this->home = home;
		this->room = room;
	}
	friend ostream& operator<<(ostream& os, AdressInfo& t)
	{
		os << " city: " << t.city << " street: " << t.street
			<< " home: " << t.home << " room: " << t.room;
		return os;
	}
	~AdressInfo() {}
};
class AnimalEntity : public AdressInfo
{
protected:
	string gender;
	int age;
	
public:
	AnimalEntity()
	{
		this->gender = "none";
		this->age = 0;
	}
	AnimalEntity(string gender, int age)
	{
		this->gender = gender;
		this->age = age;
	}
	friend ostream& operator<<(ostream& os, AnimalEntity& t)
	{
		os << " gender: " << t.gender << " age: " << t.age;
		return os;
	}
	~AnimalEntity() {}
};
class HumanEntity : public AnimalEntity
{
protected:
	string name;
	string surname;
public:
	HumanEntity() { name = "none"; surname = "none"; }
	HumanEntity(string name, string surname)
	{
		this->name = name;
		this->surname = surname;
	}
	friend ostream& operator<<(ostream& os, HumanEntity& t)
	{
		os << " name: " << t.name << " syrname: " << t.surname;
		return os;
	}
	~HumanEntity() {}
};
class Person : public HumanEntity
{
protected:
	string phone;
public:
	Person() 
	{ 
		phone = "000";
	}
	Person(string phone) { this->phone = phone; }
	friend ostream& operator<<(ostream& os, Person& t)
	{
		os <<" phone:"<< t.phone;
		return os;
	}
	~Person() {}
};

class Employee : public Person, public ISalaryCalculator
{
protected:
	string position;
	double account;
	double base;
	double percent;
	double premium;
	double hour;
	double rate;
	ISalaryCalculator* salaryCalc;
public:
	virtual double calcSalary()
	{
		if (this->salaryCalc == NULL)
			return 0;
		else
			return this->salaryCalc->calcSalary();
	}
	Employee()
	{
		position = "none";
		account = 0;
	}
	//почасовой оклад
	Employee(string name, string position, double hour, double rate)
	{
		this->name = name;
		this->position = position;
		this->rate = rate;
		this->hour = hour;
		salaryCalc = new Rule1(this->hour,this->rate);
		this->percent = 0;
		this->base = 0;
		this->premium = 0;
	}
	//оплата оклад + премия
	Employee(string name, string positionName, double base, double premium,int)
	{
		this->name = name;
		this->position = positionName;
		this->base = base;
		this->premium = premium;
		salaryCalc = new Rule2(this->base, this->premium);
		this->rate = 0;
		this->hour = 0;
		this->percent = 0;
	}
	//база + % от выручки
	Employee(string name, string positionName, double base, double percent,double)
	{
		this->name = name;
		this->position = positionName;
		this->base = base;
		this->percent = percent;
		salaryCalc = new Rule3(this->base, this->percent);
		this->rate = 0;
		this->hour = 0;
		this->premium = 0;
	}
	// оклад
	Employee(string name, string positionName, double base)
	{
		this->name = name;
		this->position = positionName;
		this->base = base;
		salaryCalc = new Rule4(this->base);
		this->percent = 0;
		this->rate = 0;
		this->hour = 0;
		this->premium = 0;
	}
	friend ostream& operator<<(ostream& os, Employee& t)
	{
		os << " name: " << t.name << " position: " << t.position << " salary: " << t.calcSalary();
		return os;
	}
	~Employee(){}
};
bool operator< (Employee& a, Employee& b)
{
	return a.calcSalary() < b.calcSalary();
};
class Department : public Employee
{
private:
	string dep_name;
	Employee* employee_list;
	Employee head_of_dep;
public:
	Department()
	{
		dep_name = "none";
		employee_list = new Employee();
		head_of_dep = employee_list[0];
	}
	Department(string dep,Employee* list,Employee head)
	{
		this->dep_name = dep;
		this->employee_list = list;
		this->head_of_dep = head;
	}
	friend ostream& operator<<(ostream& os, Department& t)
	{
		os << "Department name: " << t.dep_name << " employee list" << t.employee_list
			<<" head of department: "<<t.head_of_dep;
		return os;
	}
	~Department() 
	{
		delete employee_list;
	}
};
int main()
{
	vector<Employee*> MEN;
	Employee* m1 = new Employee("tester1", "QA",500,100,0);
	Employee* m2 = new Employee("tester 2", "Junior QA",200,35.5,0);
	Employee* m3 = new Employee("tester 3", "Junior QA",12,35);
	MEN.push_back(m1);
	MEN.push_back(m2);
	MEN.push_back(m3);
	vector<Employee*>::iterator ptr;
	cout << "before sorting : " << endl;;
	for (ptr = MEN.begin(); ptr < MEN.end(); ptr++)
	{
		cout << *(*ptr) <<endl;
	}
	system("pause");
    return 0;
}

