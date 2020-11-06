#include "visualcategory.h"

#include "visualstackelement.h"
#include "visualcontainer.h"
#include "flowlayout.h"

#include "ios.h"

#include <QVBoxLayout>
#include <QApplication>
#include <QPaintEvent>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListElement *element = new ListElement{"Address", QIcon("://icons/address-card-solid.svg")};
    ListElement *element1 = new ListElement{"Archive", QIcon("://icons/archive-solid.svg")};
    ListElement *element2 = new ListElement{"Downloads", QIcon("://icons/arrow-alt-circle-down-solid.svg")};
    ListElement *element3 = new ListElement{"Hater", QIcon("://icons/hat-cowboy-side-solid.svg")};
    ListElement *element4 = new ListElement{"List", QIcon("://icons/list.svg")};
    ListElement *element5 = new ListElement{"Stacks", QIcon("://icons/stack.svg")};

    ListCategory *cat = new ListCategory{
        {element, element1, element2, element3, element4, element5},
        "Basic items",
        QIcon::fromTheme("ao-app")
    };
    ListCategory *cat1 = new ListCategory{
        {element, element1, element2, element3, element4, element5},
        "Addons",
        QIcon::fromTheme("ao-app")
    };
    ListCategory *cat2 = new ListCategory{
        {element, element1, element2, element3, element4, element5},
        "Templates",
        QIcon::fromTheme("ao-app")
    };

    ListCategories *data = new ListCategories{
            "Addons",
            QIcon::fromTheme("chromium"),
            { cat, cat1, cat2 }
    };

    VisualStackElement *swipe = new VisualStackElement;
    VisualCategory *visual = new VisualCategory(data, swipe);
    QWidget *w = new QWidget;
    w->setStyleSheet("background-color: red");
    QWidget *w2 = new QWidget;
    w2->setStyleSheet("background-color: blue");
    QWidget *w1 = new QWidget;
    w1->setStyleSheet("background-color: green");

    //swipe->addWidget(visual);

    VisualContainer *container = new VisualContainer;
    QVBoxLayout *lay = new QVBoxLayout;
    //lay->addWidget(visual);
    lay->setMargin(5);

    container->setLayout(lay);

    //w->setLayout(new FlowLayout);

    swipe->TouchInterfacing::enableEventRedirection(true);
    swipe->addWidget(w);
    swipe->addWidget(w1);
    swipe->addWidget(w2);
    swipe->addWidget(visual);

    ios::IOS::setOutputFile("/home/nicolas/Desktop/log.txt");
    ios::IOS::output("\n______________STARTING NEW PROC INST____________\n");
    swipe->show();
    (new VisualCategory(data))->show();

    return a.exec();
}
