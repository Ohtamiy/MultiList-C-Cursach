#ifndef TYPES_H
#define TYPES_H
//POS_CNT i POS_SZ - позицiї в масивi вказiвникiв,
#define POS_CNT      -1 //позицiя, яка зберiгає iнформацiю про кiлькiсть вказiвникiв в масивi
#define POS_SZ       -2 //позицiя, яка зберiгає iнформацiю про можливу кiлькiсть вказiвникiв в масивi
#define SIZE_AR_FIRST 10 //початковий розмiр масиву вказiвникiв
#define DELTA         3 //розмiр, на який буде збiльшено масив у разi необхiдностi
#include <QString>
#include <QList>

typedef struct{
    bool wifi;
    bool bathroom;
    bool vip;
    bool food;
} Service;

typedef struct{
    QString branch;
    QList <QString> regions;
    void ** sublevel;
} Railway; //тип структури, за яким будемо звертатися до елементiв цього рiвня

typedef struct{
    QString city;
    QString region;
    QString type;
    void ** sublevel;
} City; //тип структури, за яким будемо звертатися до елементiв цього рiвня

typedef struct{
    QString name;
    int pastrafic;
    int rails;
    Service service;
    void ** sublevel;
} RailStation; //тип структури, за яким будемо звертатися до елементiв цього рiвня

typedef struct{
    QString number;
    QString from;
    QString to;
    float duration;
    QString regularity;
} Trip; //тип структури, за яким будемо звертатися до елементiв цього рiвня

struct temp{
    QString city;
    QString railSt;
    int trip;
    QStringList service;
    temp *next;
};

#endif // TYPES_H

