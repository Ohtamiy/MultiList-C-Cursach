#ifndef TYPES_H
#define TYPES_H
//POS_CNT i POS_SZ - �����i� � ��ᨢi ����i����i�,
#define POS_CNT      -1 //�����i�, 猪 ����i��� i��ଠ�i� �� �i��i��� ����i����i� � ��ᨢi
#define POS_SZ       -2 //�����i�, 猪 ����i��� i��ଠ�i� �� ������� �i��i��� ����i����i� � ��ᨢi
#define SIZE_AR_FIRST 10 //���⪮��� ஧�i� ��ᨢ� ����i����i�
#define DELTA         3 //஧�i�, �� 直� �㤥 ��i��襭� ��ᨢ � ࠧi �����i�����i
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
} Railway; //⨯ �������, �� 直� �㤥�� �������� �� �������i� �쮣� �i���

typedef struct{
    QString city;
    QString region;
    QString type;
    void ** sublevel;
} City; //⨯ �������, �� 直� �㤥�� �������� �� �������i� �쮣� �i���

typedef struct{
    QString name;
    int pastrafic;
    int rails;
    Service service;
    void ** sublevel;
} RailStation; //⨯ �������, �� 直� �㤥�� �������� �� �������i� �쮣� �i���

typedef struct{
    QString number;
    QString from;
    QString to;
    float duration;
    QString regularity;
} Trip; //⨯ �������, �� 直� �㤥�� �������� �� �������i� �쮣� �i���

struct temp{
    QString city;
    QString railSt;
    int trip;
    QStringList service;
    temp *next;
};

#endif // TYPES_H

