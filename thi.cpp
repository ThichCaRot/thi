#include <iostream>
#include <string>

//Câu 1
struct Employee
{
    int employeeID;
    std::string fullName;
    int birthYear;
    long salary;
    Employee* left;
    Employee* right;

    Employee(int id, std::string name, int year, long sal)
    {
        employeeID = id;
        fullName = name;
        birthYear = year;
        salary = sal;
        left = nullptr;
        right = nullptr;
    }
};

class EmployeeTree
{
private:
    Employee* root;

    // Câu 2
    Employee* insert(Employee* node, int id, std::string name, int year, long sal)
    {
        if (node == nullptr) return new Employee(id, name, year, sal);

        if (id < node->employeeID) node->left = insert(node->left, id, name, year, sal);
        else
            if (id > node->employeeID) node->right = insert(node->right, id, name, year, sal);

        return node;
    }

    //Hàm tìm kiếm sử dụng ID nhân viên em dùng để test chương trình
    Employee* search(Employee* node, int id)
    {
        if (node == nullptr || node->employeeID == id) return node;

        if (id < node->employeeID) return search(node->left, id);
        else return search(node->right, id);
    }

    // Câu 3
    Employee* searchByName(Employee* node, std::string name)
    {
        if (node == nullptr || node->fullName == name) return node;

        if (name < node->fullName) return searchByName(node->left, name);
        else return searchByName(node->right, name);
    }

    //Câu 4
    Employee* deleteNode(Employee* node, int id)
    {
        if (node == nullptr) return nullptr;

        if (id < node->employeeID) node->left = deleteNode(node->left, id);
        else
            if (id > node->employeeID) node->right = deleteNode(node->right, id);
            else
            {
                if (node->left == nullptr)
                {
                    Employee* temp = node->right;
                    delete node;
                    return temp;
                }
                else
                    if (node->right == nullptr)
                    {
                        Employee* temp = node->left;
                        delete node;
                        return temp;
                    }

                Employee* temp = node->right;
                while (temp->left != nullptr) temp = temp->left;

                node->employeeID = temp->employeeID;
                node->fullName = temp->fullName;
                node->birthYear = temp->birthYear;
                node->salary = temp->salary;

                node->right = deleteNode(node->right, temp->employeeID);
            }
        return node;
    }

    //Câu 5
    void printHighSalary(Employee* node, long minSalary)
    {
        if (node == nullptr) return;

        printHighSalary(node->left, minSalary);

        if (node->salary >= minSalary)
        {
            std::cout << "------------------------" << std::endl;
            std::cout << "Employee ID: " << node->employeeID << std::endl;
            std::cout << "Full Name: " << node->fullName << std::endl;
            std::cout << "Birth Year: " << node->birthYear << std::endl;
            std::cout << "Salary: " << node->salary << std::endl;
            std::cout << "------------------------" << std::endl;
        }

        printHighSalary(node->right, minSalary);
    }

public:
    EmployeeTree()
    {
        root = nullptr;
    }

    //Câu 2
    void insert(int id, std::string name, int year, long sal)
    {
        root = insert(root, id, name, year, sal);
    }

    //Tìm kiếm bằng ID nhân viên, dùng để test
    Employee* search(int id)
    {
        return search(root, id);
    }

    //Câu 3
    Employee* searchByName(std::string name)
    {
        return searchByName(root, name);
    }

    //Câu 4
    void deleteEmployee(int id)
    {
        root = deleteNode(root, id);
    }

    //Câu 5
    void printHighSalaryEmployees(long minSalary)
    {
        printHighSalary(root, minSalary);
    }
};

//Câu 6
// int main(int argc, char* argv[]) 
// {
//     EmployeeTree companyTree;

//     companyTree.insert(1001, "John Doe", 1985, 5000000);
//     companyTree.insert(1002, "Jane Smith", 1990, 6000000);
//     companyTree.insert(1003, "Michael Johnson", 1988, 15000000);

//     int deleteID = 1002;
//     // companyTree.deleteEmployee(deleteID);

//     int searchID = 1002;
//     Employee* foundEmployee = companyTree.search(searchID);
//     // Test chương trình 
//     // std::string searchName = "Jane Smith";
//     // Employee* foundEmployee = companyTree.searchByName(searchName);
//     if (foundEmployee != nullptr) 
//     {
//         std::cout << "Employee ID: " << foundEmployee->employeeID << std::endl;
//         std::cout << "Full Name: " << foundEmployee->fullName << std::endl;
//         std::cout << "Birth Year: " << foundEmployee->birthYear << std::endl;
//         std::cout << "Salary: " << foundEmployee->salary << std::endl;
//         std::cout << "------------------------" << std::endl;
//     } 
//     else std::cout << "Employee with ID " << searchID << " not found." << std::endl;
//     // else std::cout << "Employee with name " << searchName << " not found." << std::endl;

//     long minSalary = 1000000.0;
//     companyTree.printHighSalaryEmployees(minSalary);

//     return 0;
// }


//Câu 6: main để chạy các hàm đề bài đã cho
//Phần block comment phía trên là hàm main em dùng để test riêng từng hàm
//Em để nguyên không xoá để tránh việc bị sai phải viết hay dò lại hàm từ đầu ạ
int main(int argc, char* argv[])
{
    EmployeeTree companyTree;

    while (true)
    {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add employee (thêm nhân viên)" << std::endl;
        std::cout << "2. Search by ID (tìm nhân viên theo ID)" << std::endl;
        std::cout << "3. Search by name (tìm nhân viên theo tên)" << std::endl;
        std::cout << "4. Delete employee (xóa nhân viên theo ID)" << std::endl;
        std::cout << "5. Sort by salary (lọc nhân viên theo mức lương)" << std::endl;
        std::cout << "6. Exit (thoát)" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            //Câu 2: thêm nhân viên vào cây
            int id, birthYear;
            long salary;
            std::string fullName;

            std::cout << "Input employee ID (nhập mã nhân viên): ";
            std::cin >> id;
            std::cout << "Input employee name (no space)(nhập tên nhân viên)(không dấu cách): ";
            std::cin.ignore();
            getline(std::cin, fullName);
            std::cout << "Input birth year (nhập năm sinh): ";
            std::cin >> birthYear;
            std::cout << "Input salary (nhập mức lương): ";
            std::cin >> salary;

            companyTree.insert(id, fullName, birthYear, salary);
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Employee inserted" << std::endl;
            std::cout << "Nhân viên mới đã được thêm vào cây" << std::endl;
            std::cout << "----------------------------------" << std::endl;
            break;
        }
        case 2:
        {
            //Dùng để kiểm tra hàm, không có trong đề bài
            int searchID;
            std::cout << "Input ID of employee need to find: " << std::endl;
            std::cout << "Nhập mã số nhân viên cần tìm: " << std::endl;
            std::cin >> searchID;

            Employee* foundEmployee = companyTree.search(searchID);
            if (foundEmployee != nullptr)
            {
                std::cout << "---------------------" << std::endl;
                std::cout << "Employee Information:" << std::endl;
                std::cout << "Employee ID: " << foundEmployee->employeeID << std::endl;
                std::cout << "Full Name: " << foundEmployee->fullName << std::endl;
                std::cout << "Birth Year: " << foundEmployee->birthYear << std::endl;
                std::cout << "Salary: " << foundEmployee->salary << std::endl;
                std::cout << "---------------------" << std::endl;
            }
            else std::cout << "404 Error for ID " << searchID << "." << std::endl;
            break;
        }
        case 3:
        {
            //Câu 3: tìm nhân viên bằng tên
            std::string searchName;
            std::cout << "Input name of employee need to find: " << std::endl;
            std::cout << "Nhập tên nhân viên cần tìm: " << std::endl;
            std::cin.ignore();
            getline(std::cin, searchName);

            Employee* foundEmployee = companyTree.searchByName(searchName);
            if (foundEmployee != nullptr)
            {
                std::cout << "---------------------" << std::endl;
                std::cout << "Employee Information:" << std::endl;
                std::cout << "Employee ID: " << foundEmployee->employeeID << std::endl;
                std::cout << "Full Name: " << foundEmployee->fullName << std::endl;
                std::cout << "Birth Year: " << foundEmployee->birthYear << std::endl;
                std::cout << "Salary: " << foundEmployee->salary << std::endl;
                std::cout << "---------------------" << std::endl;
            }
            else std::cout << "404 Error with name " << searchName << "." << std::endl;
            break;
        }
        case 4:
        {
            //Câu 4: xoá nhân viên trong cây dùng ID
            int deleteID;
            std::cout << "Input ID of employee need to be removed: " << std::endl;
            std::cout << "Nhập mã số nhân viên cần xóa: " << std::endl;
            std::cin >> deleteID;

            companyTree.deleteEmployee(deleteID);
            std::cout << "-----------------" << std::endl;
            std::cout << "Employee with ID " << deleteID << " has been deleted." << std::endl;
            std::cout << "-----------------" << std::endl;
            break;
        }
        case 5:
        {
            //Câu 5: lọc và hiển thị nhân viên theo mức lương
            long minSalary;
            std::cout << "Input salary need to sort: " << std::endl;
            std::cout << "Nhập mức lương tối thiểu: " << std::endl;
            std::cin >> minSalary;

            companyTree.printHighSalaryEmployees(minSalary);
            break;
        }
        case 6:
        {
            std::cout << "Exit." << std::endl;
            return 0;
        }
        default:
        {
            std::cout << "Invalid choice! Please input again..." << std::endl;
            break;
        }
        }
    }

    return 0;
}

