#include <QCoreApplication>
#include <iostream>
#include <glm/glm.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout << "test output" << std::endl;
    a.exit();
    return 0;
}
