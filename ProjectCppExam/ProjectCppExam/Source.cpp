#include <iostream>
#include <string>
using namespace std;

enum Type { TEAM = 0, INDIVIDUAL = 1 };

class CppProject
{
private:
	const int projectId;
	string* members = nullptr;
	int noMembers = 0;
	int noLinesOfCode = 0;
	Type type = Type::INDIVIDUAL;
	bool isComplex = false;
	const static int LINES_OF_CODE_PER_HOUR;

public:
	CppProject(int projectId, string member) : projectId(0)
	{
		members = new string(member);
		noMembers = 1;
	}

	CppProject(int projectId, string* members, int noMembers) : projectId(projectId)
	{
		this->members = new string[noMembers];
		for (size_t i = 0; i < noMembers; i++)
		{
			this->members[i] = members[i];
		}
		this->noMembers = noMembers;
		this->type = Type::TEAM;
	}

	CppProject(const CppProject& cppProject) : projectId(cppProject.projectId)
	{
		if (cppProject.noMembers > 0)
		{
			this->members = new string[cppProject.noMembers];
			this->noMembers = cppProject.noMembers;
			for (int i = 0; i < cppProject.noMembers; i++)
			{
				this->members[i] = cppProject.members[i];
			}
		}
		else
		{
			this->members = nullptr;
			this->noMembers = 0;
		}
		this->noLinesOfCode = cppProject.noLinesOfCode;
		this->type = cppProject.type;
		this->isComplex = cppProject.isComplex;
	}

	CppProject& operator=(const CppProject& cppProject)
	{
		if (this != &cppProject)
		{
			if (cppProject.noMembers > 0)
			{
				this->members = new string[cppProject.noMembers];
				this->noMembers = cppProject.noMembers;
				for (int i = 0; i < cppProject.noMembers; i++)
				{
					this->members[i] = cppProject.members[i];
				}
			}
			else
			{
				this->members = nullptr;
				this->noMembers = 0;
			}
			this->noLinesOfCode = cppProject.noLinesOfCode;
			this->type = cppProject.type;
			this->isComplex = cppProject.isComplex;
			return *this;
		}
	}

	bool operator>(CppProject cppProject)
	{
		if (this->noLinesOfCode > cppProject.noLinesOfCode)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void operator+=(string member)
	{
		string* aux = new string[this->noMembers + 1];
		this->noMembers++;
		for (int i = 0; i < noMembers - 1; i++)
		{
			aux[i] = this->members[i];
		}
		aux[noMembers - 1] = member;
		if (this->noMembers - 1 == 1)
		{
			delete this->members;
		}
		else if (this->noMembers - 1 > 1)
		{
			delete[] this->members;
		}
		this->members = aux;
		aux = nullptr;
		if (this->noMembers > 1)
		{
			this->type = Type::TEAM;
		}
	}

	explicit operator float()
	{
		return this->noLinesOfCode / this->LINES_OF_CODE_PER_HOUR;
	}

	void setNoLinesOfCode(int noLinesOfCode)
	{
		this->noLinesOfCode = noLinesOfCode;
	}

	int getNoLinesOfCode()
	{
		return this->noLinesOfCode;
	}

	string getType() const
	{
		if ((int)type == 0)
		{
			return "TEAM";
		}
		else
		{
			return "INDIVIDUAL";
		}
	}

	int getId()
	{
		return projectId;
	}

	bool isEasy()
	{
		if (this->isComplex == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void markAsEasy()
	{
		this->isComplex = "false";
	}

	void writeCode(int lines)
	{
		this->noLinesOfCode += lines;
	}

	~CppProject()
	{
		if (noMembers == 1)
		{
			delete this->members;
		}
		else
		{
			delete[] members;
		}
	}

	friend ostream& operator<<(ostream& out, CppProject cppProject);
};

const int CppProject::LINES_OF_CODE_PER_HOUR = 30;

ostream& operator<<(ostream& out, CppProject cppProject)
{
	out << endl;
	out << "Project Id : " << cppProject.projectId << endl;
	out << "Members: ";
	for (int i = 0; i < cppProject.noMembers; i++)
	{
		out << cppProject.members[i] << " ";
	}
	out << endl;
	out << "Number of members: " << cppProject.noMembers << endl;
	out << "Number of lines of code: " << cppProject.noLinesOfCode << endl;
	out << "Project type: " << cppProject.getType() << endl;
	out << "Is complex: " << cppProject.isEasy() << endl;
	return out;
}

int main()
{
	CppProject prj1(1, "John");
	prj1.setNoLinesOfCode(1000);
	cout << prj1.getNoLinesOfCode() << endl;

	cout << prj1.getType() << endl;

	string members[] = { "John", "Alice", "Bob" };
	int noMembers = 3;
	CppProject prj2(2, members, noMembers);
	cout << prj2.getType() << endl;

	if (!prj2.isEasy())
	{
		cout << endl << "Is complex";
	}
	cout << endl << prj2.getId() << endl;
	prj2.markAsEasy();

	prj1.writeCode(1500);
	cout << prj1.getNoLinesOfCode() << endl;

	CppProject prj3 = prj2;

	prj1 = prj2;
	prj1 = prj1;

	cout << prj2;

	if (prj2 > prj1)
	{
		cout << "\nStation 3 has sold more than 1000 liters" << endl;
	}
	else
	{
		cout << "\nStation 3 has sold less than 1000 liters" << endl;
	}

	CppProject prj4(1, "John");
	prj4 += "Alice";
	cout << prj4;

	prj2.setNoLinesOfCode(1800);
	float totalHours = (float)prj2;
	cout << "\nTotal Hours: " << totalHours << endl;
}