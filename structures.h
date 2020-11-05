#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QIcon>
#include <QString>

class CategoryWidget;

struct ListElement {
    QString name;
    QIcon icon;
};

struct ListCategory {
    QList<ListElement *> elements;
    QString categoryName;
    QIcon categoryIcon;
};

struct ListCategories {
    QString containerName;
    QIcon containerIcon;
    QList<ListCategory *> categories;
};

#define op(str) std::cout << str << std::endl;

#endif // STRUCTURES_H
