#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

// Клас Employee
class Employee {
public:
    std::string name;
    std::string position;
    double salary;

    Employee(std::string n, std::string p, double s) : name(n), position(p), salary(s) {}
};

// Клас Product
class Product {
public:
    std::string name;
    std::string category;
    double price;
    int stock;

    Product(std::string n, std::string c, double p, int s) : name(n), category(c), price(p), stock(s) {}
};

int main() {
    // Завдання 1
    std::vector<Employee> employees = {
        Employee("John Doe", "Manager", 50000),
        Employee("Jane Smith", "Developer", 60000),
        Employee("Emily Davis", "Designer", 55000)
    };

    std::vector<std::string> employeeStrings;
    std::transform(employees.begin(), employees.end(), std::back_inserter(employeeStrings), [](const Employee& e) {
        return e.name + " - " + e.position;
    });

    std::cout << "Employee List:" << std::endl;
    for (const auto& str : employeeStrings) {
        std::cout << str << std::endl;
    }

    // Завдання 2
    std::vector<Product> products = {
        Product("Laptop", "Electronics", 1000, 5),
        Product("Phone", "Electronics", 500, 20),
        Product("Shirt", "Clothing", 30, 50),
        Product("Pants", "Clothing", 40, 8)
    };

    // Сортування продуктів за ціною в порядку зростання
    std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
        return a.price < b.price;
    });

    // Фільтрація продуктів, які мають низький запас (менше 10 одиниць)
    std::vector<Product> lowStockProducts;
    std::copy_if(products.begin(), products.end(), std::back_inserter(lowStockProducts), [](const Product& p) {
        return p.stock < 10;
    });

    // Знаходження середньої ціни продуктів у певній категорії
    std::string targetCategory = "Electronics";
    auto categoryProducts = std::count_if(products.begin(), products.end(), [&targetCategory](const Product& p) {
        return p.category == targetCategory;
    });

    double totalCategoryPrice = std::accumulate(products.begin(), products.end(), 0.0, [&targetCategory](double sum, const Product& p) {
        return p.category == targetCategory ? sum + p.price : sum;
    });

    double averageCategoryPrice = categoryProducts > 0 ? totalCategoryPrice / categoryProducts : 0;

    // Обчислення загальної вартості всіх продуктів на складі
    double totalStockValue = std::accumulate(products.begin(), products.end(), 0.0, [](double sum, const Product& p) {
        return sum + (p.price * p.stock);
    });

    // Виведення результатів на екран
    std::cout << "\nSorted Products by Price:" << std::endl;
    for (const auto& p : products) {
        std::cout << p.name << " - " << p.price << std::endl;
    }

    std::cout << "\nLow Stock Products:" << std::endl;
    for (const auto& p : lowStockProducts) {
        std::cout << p.name << " - " << p.stock << std::endl;
    }

    std::cout << "\nAverage Price in Category '" << targetCategory << "': " << averageCategoryPrice << std::endl;
    std::cout << "Total Stock Value: " << totalStockValue << std::endl;

    return 0;
}
