#include <functions.cpp>
#include "mainwindow.h"
#include "ui_mainwindow.h"

QMap<QString,int> NAME_TO_NUMBER { //��������i� ����� �����i� � ᨬ���
    {"����� ����", 1},
    {"���i ��i", 2},
    {"����i �� ��i", 3},
    {"����i ��� ��i", 4},
    {"����i �'��� ��i�", 5},
    {"����i �i��� ��i�", 6},
    {"����i �i� ��i�", 7}
};

void **rail;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);

    setWindowIcon(QIcon(":/61-612858_news-briciole-di-tuttoun-po-train-clipart.png"));

    ui->actionAdd->setIcon(QPixmap(":/34-349188_all-photo-png-clipart-green-plus-button-transparent.png"));
    ui->actionDel->setIcon(QPixmap(":/button-24843_1280.png"));
    ui->actionEdit->setIcon(QPixmap(":/244-2445421_clip-art-vector-graphics-computer-icons-drawing-portable-pencil-icon-png.png"));
    ui->actionSave->setIcon(QPixmap(":/192-1922110_diskette-icons-downl-icono-guardar.png"));
    ui->actionOpen->setIcon(QPixmap(":/folder-28128_1280.png"));
    ui->actionShow->setIcon(QPixmap(":/biyMpxE7T.png"));
    ui->actionShowTrip->setIcon(QPixmap(":/biyMpxE7T.png"));
    ui->actionShowByRoute->setIcon(QPixmap(":/biyMpxE7T.png"));
    ui->actionRateRailStations->setIcon(QPixmap(":/R-400.png"));

    rail = initArr();
    void *Pnew = new Railway;
    ((Railway*)Pnew)->branch = QString::fromLocal8Bit("���i����쭠 ���i����� ������");
    ((Railway*)Pnew)->regions << QString::fromLocal8Bit("�i����쪠") << QString::fromLocal8Bit("������쪠") << QString::fromLocal8Bit("��i�ய��஢�쪠")
                              << QString::fromLocal8Bit("�����쪠") << QString::fromLocal8Bit("��⮬���쪠") << QString::fromLocal8Bit("����௠��쪠")
                              << QString::fromLocal8Bit("�����i�쪠") << QString::fromLocal8Bit("i����-�࠭�i��쪠") << QString::fromLocal8Bit("�����쪠")
                              << QString::fromLocal8Bit("�i஢��ࠤ�쪠") << QString::fromLocal8Bit("�㣠��쪠") << QString::fromLocal8Bit("��i��쪠")
                              << QString::fromLocal8Bit("���������쪠") << QString::fromLocal8Bit("����쪠") << QString::fromLocal8Bit("���⠢�쪠")
                              << QString::fromLocal8Bit("�i�����쪠") << QString::fromLocal8Bit("���쪠") << QString::fromLocal8Bit("��୮�i���쪠")
                              << QString::fromLocal8Bit("���i��쪠") << QString::fromLocal8Bit("���ᮭ�쪠") << QString::fromLocal8Bit("����쭨�쪠")
                              << QString::fromLocal8Bit("��ઠ�쪠") << QString::fromLocal8Bit("���i���쪠") << QString::fromLocal8Bit("���i�i��쪠");
    ((Railway*)Pnew)->sublevel = initArr();
    addToSort(rail,Pnew,0);
}
MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionShow_triggered(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� ᯨ��"));

    QTreeWidget *show = new QTreeWidget;

    QTreeWidgetItem *item, *childCity, *childRailStation, *childTrip;
    QString railway, city, railSt, trip;
    void **cit, **rai, **trp;

    item = new QTreeWidgetItem;
    railway = QString::fromLocal8Bit("�i�i�� ���i����쭮� �����쪮� ���i����i: ") + ((Railway*)rail[0])->branch +
            QString::fromLocal8Bit("\n������i: ") + ((Railway*)rail[0])->regions.join(", ");
    item->setText(0, railway);
    show->addTopLevelItem(item);

    cit = ((Railway*)rail[0])->sublevel;
    int aCity = ((int*)cit)[POS_CNT];
    for(int i = 0; i < aCity; i++){
        childCity = new QTreeWidgetItem;
        city = QString::fromLocal8Bit("�i��: ") + ((City*)cit[i])->city + QString::fromLocal8Bit("\n�������: ") + ((City*)cit[i])->region +
                QString::fromLocal8Bit("\n��� ��ᥫ����� �㭪��: ") + ((City*)cit[i])->type;
        childCity->setText(0,city);
        item->addChild(childCity);

        rai = ((City*)cit[i])->sublevel;
        int aRail = ((int*)rai)[POS_CNT];
        for(int j = 0; j < aRail; j++){
            childRailStation = new QTreeWidgetItem;
            railSt = QString::fromLocal8Bit("����� �������: ") + ((RailStation*)rai[j])->name + QString::fromLocal8Bit("\n��ᠦ�ய��i�: ") +
                    QString::number(((RailStation*)rai[j])->pastrafic) + QString::fromLocal8Bit(" / ���i��\n�i��i��� ���i�: ") +
                    QString::number(((RailStation*)rai[j])->rails) + QString::fromLocal8Bit("\n���㣨: ") +
                    QString::fromLocal8Bit(" ��� - ") + (((RailStation*)rai[j])->service.bathroom ? QString::fromLocal8Bit("⠪") : QString::fromLocal8Bit("�i")) +
                    QString::fromLocal8Bit("\t��� - ") + (((RailStation*)rai[j])->service.food ? QString::fromLocal8Bit("⠪") : QString::fromLocal8Bit("�i")) +
                    QString::fromLocal8Bit("\tVIP-���� - ") + (((RailStation*)rai[j])->service.vip ? QString::fromLocal8Bit("⠪") : QString::fromLocal8Bit("�i")) +
                    QString::fromLocal8Bit("\tWi-fi - ") + (((RailStation*)rai[j])->service.wifi ? QString::fromLocal8Bit("⠪") : QString::fromLocal8Bit("�i"));
            childRailStation->setText(0,railSt);
            childCity->addChild(childRailStation);

            trp = ((RailStation*)rai[j])->sublevel;
            int aTrip = ((int*)trp)[POS_CNT];
            for(int k = 0; k < aTrip; k++){
                childTrip = new QTreeWidgetItem;
                trip = QString::fromLocal8Bit("����� ���: ") + ((Trip*)trp[k])->number +
                        QString::fromLocal8Bit("\n����� ��i���: ") + ((Trip*)trp[k])->from +
                        QString::fromLocal8Bit("\n����� �㤨: ") + ((Trip*)trp[k])->to +
                        QString::fromLocal8Bit("\n�ਢ��i���: ") + QString::number((int)((Trip*)trp[k])->duration) +  QString::fromLocal8Bit(" ��� ") +
                        QString::number(((((Trip*)trp[k])->duration) - (int)((Trip*)trp[k])->duration) * 100) +  QString::fromLocal8Bit(" � ") +
                        QString::fromLocal8Bit("\n������i���: ") + ((Trip*)trp[k])->regularity;
                childTrip->setText(0,trip);
                childRailStation->addChild(childTrip);
            }
        }
    }

    QHBoxLayout *fordialog = new QHBoxLayout;
    fordialog->addWidget(show);
    show->setFixedSize(600,450);
    show->setHeaderHidden(true);

    dialogWindow->setLayout(fordialog);
    dialogWindow->show();
}

QDialog *createDialog(QString title){
    QDialog *dialogWindow = new QDialog;
    dialogWindow->setWindowIcon(QIcon(":/61-612858_news-briciole-di-tuttoun-po-train-clipart.png"));
    dialogWindow->setWindowTitle(title);
    dialogWindow->setStyleSheet("font: 12pt Arial");
    return dialogWindow;
}

QDialogButtonBox *createDialogButtonBox(QDialog *dialogWindow){
    QDialogButtonBox *buttonsComboBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(buttonsComboBox, SIGNAL(accepted()), dialogWindow, SLOT(accept()));
    QObject::connect(buttonsComboBox, SIGNAL(rejected()), dialogWindow, SLOT(reject()));
    return buttonsComboBox;
}

QLabel *createLabel(QString stroka){
    QLabel *choiceLabel = new QLabel;
    choiceLabel->setText(stroka);
    return choiceLabel;
}

void MainWindow::on_actionAdd_triggered(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� �����"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *choiceLabel = createLabel(QString::fromLocal8Bit("�����i�� �i����, �� 直� ������ ����� �������:"));

    QComboBox *comboBox = new QComboBox;
    comboBox->setMinimumHeight(30);
    comboBox->addItem(QString::fromLocal8Bit("�i��"));
    comboBox->addItem(QString::fromLocal8Bit("������"));
    comboBox->addItem(QString::fromLocal8Bit("����"));

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(choiceLabel);
    forWidgetsDialog->addWidget(comboBox);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        QString value = comboBox->currentText();
        if(value == QString::fromLocal8Bit("�i��"))
            addCity();
        else if(value == QString::fromLocal8Bit("������"))
            addRailStation();
        else if(value == QString::fromLocal8Bit("����"))
            addTrip();
        on_actionShow_triggered();
    }
}

void addCity(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� ������� �� �i���� �i��"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *labelCity = createLabel(QString::fromLocal8Bit("����i�� ����� �i��"));
    QLabel *labelRegion = createLabel(QString::fromLocal8Bit("�����i�� �������"));
    QLabel *labelType = createLabel(QString::fromLocal8Bit("�����i�� ⨯ ��ᥫ����� �㭪��"));

    QLineEdit *city= new QLineEdit;
    QComboBox *region = new QComboBox;
    region->setMinimumHeight(30);
    for(int i = 0; i < ((Railway*)rail[0])->regions.size(); i++)
        region->addItem(((Railway*)rail[0])->regions[i]);
    QComboBox *type = new QComboBox;
    type->setMinimumHeight(30);
    type->addItem(QString::fromLocal8Bit("�i��"));
    type->addItem(QString::fromLocal8Bit("����� �i�쪮�� ⨯�"));
    type->addItem(QString::fromLocal8Bit("����"));

    QGridLayout *forWidgetsDialog = new QGridLayout;
    forWidgetsDialog->addWidget(labelCity,1,1,Qt::AlignRight);
    forWidgetsDialog->addWidget(city,1,2);
    forWidgetsDialog->addWidget(labelRegion,2,1,Qt::AlignRight);
    forWidgetsDialog->addWidget(region,2,2);
    forWidgetsDialog->addWidget(labelType,3,1,Qt::AlignRight);
    forWidgetsDialog->addWidget(type,3,2);
    forWidgetsDialog->addWidget(buttonsComboBox,4,2);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        if(city->text() == ""){
            QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("���� \"�i��\" �� ���������"));
            return;
        }
        void *Pnew = new City;
        ((City*)Pnew)->city = city->text();
        ((City*)Pnew)->region = region->currentText();
        ((City*)Pnew)->type = type->currentText();
        ((City*)Pnew)->sublevel = initArr();

        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, ((City*)Pnew)->city, findPosCity, findOK, cmpCity);
        if(findOK){
            QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("����� ������� ��� i���"));
            return;
        }
        addToSort(((Railway*)rail[0])->sublevel, Pnew, findPosCity);
    }
}

void addRailStation(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("���i� ������� �� �i��i �i��"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label = createLabel(QString::fromLocal8Bit("�����i��, � 瘟 �i�� ������ ����� ������"));

    QComboBox *city = new QComboBox;
    city->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++)
        city->addItem(((City*)((Railway*)rail[0])->sublevel[i])->city);
    if(city->itemText(0) == "")
        return;

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(city);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, city->currentText(), findPosCity, findOK, cmpCity);

        QDialog *dialogWindowNew = createDialog(QString::fromLocal8Bit("��������� ������� �� �i���� ������"));
        QDialogButtonBox *buttonsComboBoxNew = createDialogButtonBox(dialogWindowNew);

        QLabel *nameLabel = createLabel(QString::fromLocal8Bit("����i�� ����� �������"));
        QLabel *ptraficLabel = createLabel(QString::fromLocal8Bit("����i�� ��ᠦ�ய��i�"));
        QLabel *railsLabel = createLabel(QString::fromLocal8Bit("�i��i��� ���i�"));
        QLabel *serviceLabel = createLabel(QString::fromLocal8Bit("�����i�� ��i ���㣨"));

        QLineEdit *name= new QLineEdit;
        QSpinBox *ptrafic = new QSpinBox;
        ptrafic->setRange(1,10000);
        QSpinBox *rails = new QSpinBox;
        rails->setMinimum(1);
        QCheckBox *wifi = new QCheckBox;
        wifi->setText(QString::fromLocal8Bit("Wi-fi"));
        QCheckBox *bathroom = new QCheckBox;
        bathroom->setText(QString::fromLocal8Bit("���"));
        QCheckBox *vip = new QCheckBox;
        vip->setText(QString::fromLocal8Bit("VIP-����"));
        QCheckBox *food = new QCheckBox;
        food->setText(QString::fromLocal8Bit("���"));

        QHBoxLayout *forservice1 = new QHBoxLayout;
        forservice1->addWidget(wifi);
        forservice1->addWidget(bathroom);
        QHBoxLayout *forservice2 = new QHBoxLayout;
        forservice2->addWidget(food);
        forservice2->addWidget(vip);

        QGridLayout *forWidgetsDialogNew = new QGridLayout;
        forWidgetsDialogNew->addWidget(nameLabel,1,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(name,1,2);
        forWidgetsDialogNew->addWidget(ptraficLabel,2,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(ptrafic,2,2);
        forWidgetsDialogNew->addWidget(railsLabel,3,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(rails,3,2);
        forWidgetsDialogNew->addWidget(serviceLabel,4,1,Qt::AlignRight);
        forWidgetsDialogNew->addItem(forservice1,5,1);
        forWidgetsDialogNew->addItem(forservice2,5,2);
        forWidgetsDialogNew->addWidget(buttonsComboBoxNew,6,2);

        dialogWindowNew->setLayout(forWidgetsDialogNew);

        result = dialogWindowNew->exec();
        if(result == QDialog::Accepted){
            if(name->text() == ""){
                QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("���� \"����� �������\" �� ���������"));
                return;
            }

            void *Pnew = new RailStation;
            ((RailStation*)Pnew)->name = name->text();
            ((RailStation*)Pnew)->pastrafic = ptrafic->value();
            ((RailStation*)Pnew)->rails = rails->value();
            ((RailStation*)Pnew)->service.bathroom = bathroom->isChecked() ? true : false;
            ((RailStation*)Pnew)->service.food = food->isChecked() ? true : false;
            ((RailStation*)Pnew)->service.vip = vip->isChecked() ? true : false;
            ((RailStation*)Pnew)->service.wifi = wifi->isChecked() ? true : false;
            ((RailStation*)Pnew)->sublevel = initArr();

            int findPosRailSt;
            findEl(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, ((RailStation*)Pnew)->name, findPosRailSt, findOK, cmpRailSt);
            if(findOK){
                QMessageBox::critical(dialogWindowNew, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("����� ������� ��� i���"));
                return;
            }
            addToSort(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, Pnew, findPosRailSt);
        }
    }
}

void addTrip(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("���i� ������� �� �i��i �i�� i ������"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label = createLabel(QString::fromLocal8Bit("�����i�� ������� �� �i��i �i�� i ������"));

    QComboBox *cityAndRail = new QComboBox;
    cityAndRail->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){
        QStringList city;
        city << ((City*)((Railway*)rail[0])->sublevel[i])->city;
        for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
            city << ((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->name;
            cityAndRail->addItem(city.join(", "));
            city.removeLast();
        }
    }

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(cityAndRail);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, cityAndRail->currentText().split(", ")[0], findPosCity, findOK, cmpCity);
        int findPosRailSt;
        findEl(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, cityAndRail->currentText().split(", ")[1], findPosRailSt, findOK, cmpRailSt);

        QDialog *dialogWindowNew = createDialog(QString::fromLocal8Bit("��������� ������� �� �i���� ����"));
        QDialogButtonBox *buttonsComboBoxNew = createDialogButtonBox(dialogWindowNew);

        QLabel *numberLabel = createLabel(QString::fromLocal8Bit("����i�� ����� �����"));
        QLabel *fromLabel = createLabel(QString::fromLocal8Bit("����i�� �i��ࠢ�� ���"));
        QLabel *toLabel = createLabel(QString::fromLocal8Bit("����i�� ��� �ਡ����"));
        QLabel *durationLabel = createLabel(QString::fromLocal8Bit("�த���㢠�i���(���,�)"));
        QLabel *regulatiryLabel = createLabel(QString::fromLocal8Bit("�����i�� ॣ���i���"));

        QSpinBox *number= new QSpinBox;
        number->setMinimum(1);
        QLineEdit *from= new QLineEdit;
        QLineEdit *to= new QLineEdit;
        QSpinBox *hours = new QSpinBox;
        hours->setMinimum(1);
        QSpinBox *minutes = new QSpinBox;
        minutes->setRange(0,59);

        QHBoxLayout *forduration = new QHBoxLayout;
        forduration->addWidget(hours);
        forduration->addWidget(minutes);

        QComboBox *regulatiry = new QComboBox;
        regulatiry->setMinimumHeight(30);
        regulatiry->addItem(QString::fromLocal8Bit("����� ����"));
        regulatiry->addItem(QString::fromLocal8Bit("���i ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("�����i ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �� ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("����i ��� ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �'��� ��i�"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �i��� ��i�"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �i� ��i�"));

        QGridLayout *forWidgetsDialogNew = new QGridLayout;
        forWidgetsDialogNew->addWidget(numberLabel,1,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(number,1,2);
        forWidgetsDialogNew->addWidget(fromLabel,2,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(from,2,2);
        forWidgetsDialogNew->addWidget(toLabel,3,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(to,3,2);
        forWidgetsDialogNew->addWidget(durationLabel,4,1,Qt::AlignRight);
        forWidgetsDialogNew->addItem(forduration,4,2);
        forWidgetsDialogNew->addWidget(regulatiryLabel,5,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(regulatiry,5,2);
        forWidgetsDialogNew->addWidget(buttonsComboBoxNew,6,2);

        dialogWindowNew->setLayout(forWidgetsDialogNew);

        result = dialogWindowNew->exec();
        if(result == QDialog::Accepted){
            if(from->text() == "" || to->text() == ""){
                QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("�� ��i ���i �㫨 ������i"));
                return;
            }

            void *Pnew = new Trip;
            ((Trip*)Pnew)->number = number->text();
            ((Trip*)Pnew)->from = from->text();
            ((Trip*)Pnew)->to = to->text();
            ((Trip*)Pnew)->regularity = regulatiry->currentText();
            ((Trip*)Pnew)->duration = hours->value() + (float)(minutes->value()/100);

            int findPosTrip;
            findEl(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel, ((Trip*)Pnew)->number, findPosTrip, findOK, cmpTrip);
            if(findOK){
                QMessageBox::critical(dialogWindowNew, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("����� ������� ��� i���"));
                return;
            }
            addToSort(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel, Pnew, findPosTrip);
        }
    }
}

void MainWindow::on_actionDel_triggered(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� �����"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *choiceLabel = createLabel(QString::fromLocal8Bit("�����i��, � 类�� �i��� ������ ������� �������"));

    QComboBox *comboBox = new QComboBox;
    comboBox->setMinimumHeight(30);
    comboBox->addItem(QString::fromLocal8Bit("�i��"));
    comboBox->addItem(QString::fromLocal8Bit("������"));
    comboBox->addItem(QString::fromLocal8Bit("����"));

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(choiceLabel);
    forWidgetsDialog->addWidget(comboBox);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        QString value = comboBox->currentText();
        if(value == QString::fromLocal8Bit("�i��"))
            delCity();
        else if(value == QString::fromLocal8Bit("������"))
            delRailSt();
        else if(value == QString::fromLocal8Bit("����"))
            delTrip();
        on_actionShow_triggered();
    }
}

void delCity(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� ������� � �i��� �i��"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label =  createLabel(QString::fromLocal8Bit("�����i�� �i��, 瘟 ������ �������"));

    QComboBox *city= new QComboBox;
    city->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++)
        city->addItem(((City*)((Railway*)rail[0])->sublevel[i])->city);

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(city);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOk;
        findEl(((Railway*)rail[0])->sublevel, city->currentText(), findPosCity, findOk, cmpCity);
        deletingRailSt(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel);
        del(((Railway*)rail[0])->sublevel, findPosCity);
    }
}

void delRailSt(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� ������� � �i��� ������"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label =  createLabel(QString::fromLocal8Bit("�����i�� ������, 直� ������ �������"));

    QComboBox *cityAndRail= new QComboBox;
    cityAndRail->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){
        QStringList city;
        city << ((City*)((Railway*)rail[0])->sublevel[i])->city;
        for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
            city << ((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->name;
            cityAndRail->addItem(city.join(", "));
            city.removeLast();
        }
    }

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(cityAndRail);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, cityAndRail->currentText().split(", ")[0], findPosCity, findOK, cmpCity);
        int findPosRailSt;
        findEl(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, cityAndRail->currentText().split(", ")[1], findPosRailSt, findOK, cmpRailSt);

        deletingTrip(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel);
        del(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, findPosRailSt);
    }
}

void delTrip(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("��������� ������� � �i��� ����"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label = createLabel(QString::fromLocal8Bit("�����i�� ����, 直� ������ �������"));

    QComboBox *cityAndRailAndTrip = new QComboBox;
    cityAndRailAndTrip->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){
        QStringList city;
        city << ((City*)((Railway*)rail[0])->sublevel[i])->city;
        for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
            city << ((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->name;
            for(int k = 0; k < ((int*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel)[POS_CNT]; k++){
                city << ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->number;
                cityAndRailAndTrip->addItem(city.join(", "));
                city.removeLast();
            }
            city.removeLast();
        }
    }

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(cityAndRailAndTrip);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, cityAndRailAndTrip->currentText().split(", ")[0], findPosCity, findOK, cmpCity);
        int findPosRailSt;
        findEl(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, cityAndRailAndTrip->currentText().split(", ")[1], findPosRailSt, findOK, cmpRailSt);
        int findPosTrip;
        findEl(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel, cityAndRailAndTrip->currentText().split(", ")[2], findPosTrip, findOK, cmpTrip);
        del(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel, findPosTrip);
    }
}

void MainWindow::on_actionEdit_triggered(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("�����㢠��� �����"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *choiceLabel = createLabel(QString::fromLocal8Bit("�����i��, ������� 类�� �i��� ������ �i�।��㢠�"));

    QComboBox *comboBox = new QComboBox;
    comboBox->setMinimumHeight(30);
    comboBox->addItem(QString::fromLocal8Bit("�i��"));
    comboBox->addItem(QString::fromLocal8Bit("������"));
    comboBox->addItem(QString::fromLocal8Bit("����"));

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(choiceLabel);
    forWidgetsDialog->addWidget(comboBox);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        QString value = comboBox->currentText();
        if(value == QString::fromLocal8Bit("�i��"))
            editCity();
        else if(value == QString::fromLocal8Bit("������"))
            editRailSt();
        else if(value == QString::fromLocal8Bit("����"))
            editTrip();
        on_actionShow_triggered();
    }
}

void editCity(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("�����㢠��� ������� �� �i��i �i��"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label = createLabel(QString::fromLocal8Bit("�����i�� �i��, 瘟 ������ ।��㢠�"));

    QComboBox *city= new QComboBox;
    city->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++)
        city->addItem(((City*)((Railway*)rail[0])->sublevel[i])->city);

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(city);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, city->currentText(), findPosCity, findOK, cmpCity);

        QDialog *dialogWindowNew = createDialog(QString::fromLocal8Bit("�����㢠��� ������� �� �i��i �i��"));
        QDialogButtonBox *buttonsComboBoxNew = createDialogButtonBox(dialogWindowNew);

        QLabel *labelCity = createLabel(QString::fromLocal8Bit("����i�� ���� ����� �i��"));
        QLabel *labelRegion = createLabel(QString::fromLocal8Bit("�����i�� ����� �������"));
        QLabel *labelType = createLabel(QString::fromLocal8Bit("�����i�� ����� ⨯ ��ᥫ����� �㭪��"));

        QLineEdit *name= new QLineEdit;
        name->setText(((City*)((Railway*)rail[0])->sublevel[findPosCity])->city);
        QComboBox *region = new QComboBox;
        region->setMinimumHeight(30);
        for(int i = 0; i < ((Railway*)rail[0])->regions.size(); i++)
            region->addItem(((Railway*)rail[0])->regions[i]);
        region->setCurrentText(((City*)((Railway*)rail[0])->sublevel[findPosCity])->region);
        QComboBox *type = new QComboBox;
        type->setMinimumHeight(30);
        type->addItem(QString::fromLocal8Bit("�i��"));
        type->addItem(QString::fromLocal8Bit("����� �i�쪮�� ⨯�"));
        type->addItem(QString::fromLocal8Bit("����"));
        type->setCurrentText(((City*)((Railway*)rail[0])->sublevel[findPosCity])->type);

        QGridLayout *forWidgetsDialogNew = new QGridLayout;
        forWidgetsDialogNew->addWidget(labelCity,1,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(name,1,2);
        forWidgetsDialogNew->addWidget(labelRegion,2,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(region,2,2);
        forWidgetsDialogNew->addWidget(labelType,3,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(type,3,2);
        forWidgetsDialogNew->addWidget(buttonsComboBoxNew,4,2);

        dialogWindowNew->setLayout(forWidgetsDialogNew);

        result = dialogWindowNew->exec();
        if(result == QDialog::Accepted){
            if(name->text() == ""){
                QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("���� \"�i��\" �� ���������"));
                return;
            }
            QString temp = ((City*)((Railway*)rail[0])->sublevel[findPosCity])->city;
            ((City*)((Railway*)rail[0])->sublevel[findPosCity])->type = type->currentText();
            ((City*)((Railway*)rail[0])->sublevel[findPosCity])->region = region->currentText();
            ((City*)((Railway*)rail[0])->sublevel[findPosCity])->city = name->text();
            if(temp != name->text())
                sortAfterChanging(((Railway*)rail[0])->sublevel, findPosCity, name->text(), cmpCity);
        }
    }
}

void editRailSt(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("�����㢠��� ������� �� �i��i ������"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label = createLabel(QString::fromLocal8Bit("�����i�� ������, 直� ������ ।��㢠�"));

    QComboBox *cityAndRail= new QComboBox;
    cityAndRail->setMaximumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){
        QStringList city;
        city << ((City*)((Railway*)rail[0])->sublevel[i])->city;
        for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
            city << ((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->name;
            cityAndRail->addItem(city.join(", "));
            city.removeLast();
        }
    }

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(cityAndRail);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, cityAndRail->currentText().split(", ")[0], findPosCity, findOK, cmpCity);
        int findPosRailSt;
        findEl(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, cityAndRail->currentText().split(", ")[1], findPosRailSt, findOK, cmpRailSt);

        QDialog *dialogWindowNew = createDialog(QString::fromLocal8Bit("�����㢠��� ������� �� �i��i ������"));
        QDialogButtonBox *buttonsComboBoxNew = createDialogButtonBox(dialogWindowNew);

        QLabel *nameLabel = createLabel(QString::fromLocal8Bit("����i�� ���� ����� �������"));
        QLabel *ptraficLabel = createLabel(QString::fromLocal8Bit("����i�� ����� ��ᠦ�ய��i�"));
        QLabel *railsLabel = createLabel(QString::fromLocal8Bit("���� �i��i��� ���i�"));
        QLabel *serviceLabel = createLabel(QString::fromLocal8Bit("�����i�� ���i ��i ���㣨"));

        QLineEdit *name = new QLineEdit;
        name->setText(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->name);
        QSpinBox *ptrafic = new QSpinBox;
        ptrafic->setRange(1,10000);
        ptrafic->setValue(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->pastrafic);
        QSpinBox *rails = new QSpinBox;
        rails->setMinimum(1);
        rails->setValue(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->rails);
        QCheckBox *wifi = new QCheckBox;
        wifi->setText(QString::fromLocal8Bit("Wi-fi"));
        wifi->setChecked(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.wifi ? true : false);
        QCheckBox *bathroom = new QCheckBox;
        bathroom->setText(QString::fromLocal8Bit("���"));
        bathroom->setChecked(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.bathroom ? true : false);
        QCheckBox *vip = new QCheckBox;
        vip->setText(QString::fromLocal8Bit("VIP-����"));
        vip->setChecked(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.vip ? true : false);
        QCheckBox *food = new QCheckBox;
        food->setText(QString::fromLocal8Bit("���"));
        food->setChecked(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.food ? true : false);

        QHBoxLayout *forservice1 = new QHBoxLayout;
        forservice1->addWidget(wifi);
        forservice1->addWidget(bathroom);
        QHBoxLayout *forservice2 = new QHBoxLayout;
        forservice2->addWidget(food);
        forservice2->addWidget(vip);

        QGridLayout *forWidgetsDialogNew = new QGridLayout;
        forWidgetsDialogNew->addWidget(nameLabel,1,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(name,1,2);
        forWidgetsDialogNew->addWidget(ptraficLabel,2,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(ptrafic,2,2);
        forWidgetsDialogNew->addWidget(railsLabel,3,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(rails,3,2);
        forWidgetsDialogNew->addWidget(serviceLabel,4,1,Qt::AlignRight);
        forWidgetsDialogNew->addItem(forservice1,5,1);
        forWidgetsDialogNew->addItem(forservice2,5,2);
        forWidgetsDialogNew->addWidget(buttonsComboBoxNew,6,2);

        dialogWindowNew->setLayout(forWidgetsDialogNew);

        result = dialogWindowNew->exec();
        if(result == QDialog::Accepted){
            if(name->text() == ""){
                QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("���� \"����� �������\" �� ���������"));
                return;
            }
            QString temp = ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->name;
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->name = name->text();
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->pastrafic = ptrafic->value();
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->rails = rails->value();
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.bathroom = bathroom->isChecked() ? true : false;
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.wifi = wifi->isChecked() ? true : false;
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.vip = vip->isChecked() ? true : false;
            ((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->service.food = food->isChecked() ? true : false;
            if(temp != name->text())
                sortAfterChanging(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, findPosRailSt, name->text(), cmpRailSt);
        }
    }
}

void editTrip(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("�����㢠��� ������� �� �i��i ����"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *label = createLabel(QString::fromLocal8Bit("�����i�� ����, 直� ������ ।��㢠�"));

    QComboBox *cityAndRailAndTrip= new QComboBox;
    cityAndRailAndTrip->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){
        QStringList city;
        city << ((City*)((Railway*)rail[0])->sublevel[i])->city;
        for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
            city << ((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->name;
            for(int k = 0; k < ((int*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel)[POS_CNT]; k++){
                city << ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->number;
                cityAndRailAndTrip->addItem(city.join(", "));
                city.removeLast();
            }
            city.removeLast();
        }
    }

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(cityAndRailAndTrip);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        int findPosCity;
        bool findOK;
        findEl(((Railway*)rail[0])->sublevel, cityAndRailAndTrip->currentText().split(", ")[0], findPosCity, findOK, cmpCity);
        int findPosRailSt;
        findEl(((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel, cityAndRailAndTrip->currentText().split(", ")[1], findPosRailSt, findOK, cmpRailSt);
        int findPosTrip;
        findEl(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel, cityAndRailAndTrip->currentText().split(", ")[2], findPosTrip, findOK, cmpTrip);

        QDialog *dialogWindowNew = createDialog(QString::fromLocal8Bit("�����㢠��� ������� �� i ����"));
        QDialogButtonBox *buttonsComboBoxNew = createDialogButtonBox(dialogWindowNew);

        QLabel *numberLabel = createLabel(QString::fromLocal8Bit("����� ����� �����"));
        QLabel *fromLabel = createLabel(QString::fromLocal8Bit("���� �i��ࠢ�� ���"));
        QLabel *toLabel = createLabel(QString::fromLocal8Bit("���� ��� �ਡ����"));
        QLabel *durationLabel = createLabel(QString::fromLocal8Bit("�த���㢠�i���(���,�)"));
        QLabel *regulatiryLabel = createLabel(QString::fromLocal8Bit("���� ॣ���i���"));

        QSpinBox *number= new QSpinBox;
        number->setMinimum(1);
        number->setValue(atoi(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->number.toLocal8Bit().constData()));
        QLineEdit *from= new QLineEdit;
        from->setText(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->from);
        QLineEdit *to= new QLineEdit;
        to->setText(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->to);
        QSpinBox *hours = new QSpinBox;
        hours->setMinimum(1);
        hours->setValue((int)((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->duration);
        QSpinBox *minutes = new QSpinBox;
        minutes->setRange(0,59);
        minutes->setValue((float)(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->duration -
                        (int)((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->duration) * 100 + 1);

        QHBoxLayout *forduration = new QHBoxLayout;
        forduration->addWidget(hours);
        forduration->addWidget(minutes);

        QComboBox *regulatiry = new QComboBox;
        regulatiry->setMinimumHeight(30);
        regulatiry->addItem(QString::fromLocal8Bit("����� ����"));
        regulatiry->addItem(QString::fromLocal8Bit("���i ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("�����i ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �� ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("����i ��� ��i"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �'��� ��i�"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �i��� ��i�"));
        regulatiry->addItem(QString::fromLocal8Bit("����i �i� ��i�"));
        regulatiry->setCurrentText(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosRailSt])->regularity);

        QGridLayout *forWidgetsDialogNew = new QGridLayout;
        forWidgetsDialogNew->addWidget(numberLabel,1,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(number,1,2);
        forWidgetsDialogNew->addWidget(fromLabel,2,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(from,2,2);
        forWidgetsDialogNew->addWidget(toLabel,3,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(to,3,2);
        forWidgetsDialogNew->addWidget(durationLabel,4,1,Qt::AlignRight);
        forWidgetsDialogNew->addItem(forduration,4,2);
        forWidgetsDialogNew->addWidget(regulatiryLabel,5,1,Qt::AlignRight);
        forWidgetsDialogNew->addWidget(regulatiry,5,2);
        forWidgetsDialogNew->addWidget(buttonsComboBoxNew,6,2);

        dialogWindowNew->setLayout(forWidgetsDialogNew);

        result = dialogWindowNew->exec();
        if(result == QDialog::Accepted){
            if(from->text() == "" || to->text() == ""){
                QMessageBox::critical(dialogWindow, QString::fromLocal8Bit("�������"), QString::fromLocal8Bit("���� \"����� �������\" �� ���������"));
                return;
            }
            QString temp = ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->number;
            ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->from = from->text();
            ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->to = to->text();
            ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->regularity = regulatiry->currentText();
            ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->duration = hours->value() + (float)minutes->value()/100;
            ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel[findPosTrip])->number = number->text();
            if(temp != number->text())
                sortAfterChanging(((RailStation*)((City*)((Railway*)rail[0])->sublevel[findPosCity])->sublevel[findPosRailSt])->sublevel, findPosTrip, number->text(), cmpTrip);
        }
    }
}

void MainWindow::on_actionRateRailStations_triggered(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("I����i�㠫쭥 �������� �1")); // �i������� �i���

    QTableWidget *rate = new QTableWidget; // ⠡����
    rate->setColumnCount(4);
    rate->setRowCount(1);

    QStringList columnHeads; // ��������� ⠡���i
    columnHeads << QString::fromLocal8Bit("�i��") << QString::fromLocal8Bit("������")
                << QString::fromLocal8Bit("����") << QString::fromLocal8Bit("���㣨");
    rate->setHorizontalHeaderLabels(columnHeads);

    temp *start = NULL; // ����i���� �� ����⪮��� ᯨ᮪
    void **city, **railSt, **trip; // �����i��i ��i��i ��� ��ॣ��� ᯨ��
    city = ((Railway*)rail[0])->sublevel;
    int aCity=((int*)city)[POS_CNT];
    for (int k = 0; k < aCity; k++){ // ���i� �� ᯨ��
        railSt = ((City*)city[k])->sublevel;
        int aRailSt = ((int*)railSt)[POS_CNT];
        for(int i = 0; i < aRailSt; i++){ // ���i� �� ᯨ��
            int trips = 0;
            trip = ((RailStation*)railSt[i])->sublevel;
            trips += ((int*)trip)[POS_CNT]; // �����'�⮢�� �i��i��� ३�i�

            int count = 0;
            temp *pNew = new temp; // ���?��� ���'��� �?� ����� �������
            pNew->railSt = ((RailStation*)railSt[i])->name; // �������� i��ଠ�i��i ����
            pNew->city = ((City*)city[k])->city;
            pNew->trip = trips;
            pNew->service << QVariant(((RailStation*)railSt[i])->service.bathroom).toString()
                          << QVariant(((RailStation*)railSt[i])->service.food).toString()
                          << QVariant(((RailStation*)railSt[i])->service.vip).toString()
                          << QVariant(((RailStation*)railSt[i])->service.wifi).toString();
            if(((RailStation*)railSt[i])->service.bathroom) count++; // ��ॢi��� ��i��� ���㣨
            if(((RailStation*)railSt[i])->service.food) count++;
            if(((RailStation*)railSt[i])->service.vip) count++;
            if(((RailStation*)railSt[i])->service.wifi) count++;
            pNew->next = NULL; // ����㯭��� �����

            temp *wp = start, *pp = NULL; // �����i��i ��i��i ��� ��ॣ��� ᯨ��
            while(wp) // 横�: ���� �� �i���� ᯨ��
            {
                int cnt = 0;
                for(int k = 0; k < 4; k++) // �i��客�� �i��i��� ����
                    if(QVariant(wp->service.at(k)).toBool()) cnt++;
                if(count <= cnt){ // ���� �i��� ��� ��⠢�� � ��⮢����� ᯨ��
                    pp = wp;
                    wp = wp->next;
                }
                else break;
            }
            if (pp == NULL) start = pNew; // ���'��� � i�訬� ������⠬� ᯨ��
            else pp->next = pNew;
            pNew->next = wp;
        }
    }

    for(int i = 0; i < countRailStations(rail); i++){ // 横� ������ ������i� � ⠡����
        int j = 0;

        QTableWidgetItem *item = new QTableWidgetItem; // ���i��� ���'��� �i� ������� ⠡���i
        item->setText(start->city); // ��������
        rate->setItem(i,j++,item); // ����� � ⠡����

        item = new QTableWidgetItem;
        item->setText(start->railSt);
        rate->setItem(i,j++,item);

        item = new QTableWidgetItem;
        item->setText(QString::number(start->trip));
        rate->setItem(i,j++,item);

        item = new QTableWidgetItem;
        QString tmp = "";
        for(int k = 0; k < 4; k++)
            if(QVariant(start->service.at(k)).toBool()) tmp.append(QString::fromUtf8("\u2605"));
        item->setText(tmp);
        rate->setItem(i,j,item);

        if(start->next)
            rate->insertRow(rate->rowCount());

        temp *pdel = start; // ������� ᯨ᮪
        start = start->next;
        delete pdel;
    }

    rate->setFixedSize(rate->columnWidth(0) * rate->columnCount() + 20, rate->rowHeight(0) * (rate->rowCount() + 1));
    dialogWindow->setFixedSize(rate->width() + 38, rate->height() + 50); // �i�ᮢ���� ஧�i�

    QLabel *label = createLabel(QString::fromLocal8Bit("���⨭� ������i� �� �i��i��� ३�i� i ���㣠��"));
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(rate);

    dialogWindow->setLayout(forWidgetsDialog);
    dialogWindow->exec();
}

void MainWindow::on_actionShowTrip_triggered(){
    time_t now = time(0); // ��ਬ�� ��⥬��� ��
    char* dt = ctime(&now); // ��ਬ�� ��⥬�� ����
    tm *ltm = localtime(&now); // ������� � �i����� ⨯��� ���

    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("I����i�㠫쭥 �������� �2")); // �i������� �i���

    QLabel *label = createLabel(QString::fromLocal8Bit("�쮣���i�� ��� + ��: ") + dt);
    label->setAlignment(Qt::AlignCenter);

    QTableWidget *show = new QTableWidget; // ⠡����
    show->setColumnCount(6);
    show->setRowCount(0);

    QStringList columnHeads; // ���������
    columnHeads << QString::fromLocal8Bit("�i��") << QString::fromLocal8Bit("������") << QString::fromLocal8Bit("����")
                << QString::fromLocal8Bit("��i���") << QString::fromLocal8Bit("�㤨") << QString::fromLocal8Bit("������i���");
    show->setHorizontalHeaderLabels(columnHeads);
    show->setColumnWidth(5,140);

    void **city, **railSt, **trip;
    city = ((Railway*)rail[0])->sublevel;
    int aCity=((int*)city)[POS_CNT];
    for(int k = 0; k < aCity; k++){ // ��室��� �� ᯨ��
        railSt = ((City*)city[k])->sublevel;
        int aRailSt = ((int*)railSt)[POS_CNT];
        for(int i = 0; i < aRailSt; i++){ // ��室��� �� ᯨ��
            trip = ((RailStation*)railSt[i])->sublevel;
            int aTrip = ((int*)trip)[POS_CNT];
            for(int j = 0; j < aTrip; j++){ // ��室��� �� ᯨ��
                /* �� ����� ३� ��� ॣ���i���: ����୨� ���� i �쮣���i�� ��� ⠪�� ����ୠ ���
                 * �� ॣ���i���: ��୨� ���� i �쮣���i�� ��� � ����, 猪 �i������ � ॣ���i��� ������ ३�� */
                if((((Trip*)trip[j])->regularity == QString::fromLocal8Bit("�����i ��i") && ltm->tm_mday % 2 != 0) ||
                   (((Trip*)trip[j])->regularity != QString::fromLocal8Bit("�����i ��i") && ltm->tm_mday % NAME_TO_NUMBER[((Trip*)trip[j])->regularity.toLocal8Bit()] == 0)){
                    int f = 0;

                    show->insertRow(show->rowCount());

                    QTableWidgetItem *item = new QTableWidgetItem; // ���i��� ���'���
                    item->setText(((City*)city[k])->city); // ��������
                    show->setItem(show->rowCount()-1,f++,item); // ��⠢��� � ⠡����

                    item = new QTableWidgetItem;
                    item->setText(((RailStation*)railSt[i])->name);
                    show->setItem(show->rowCount()-1,f++,item);

                    item = new QTableWidgetItem;
                    item->setText(((Trip*)trip[j])->number);
                    show->setItem(show->rowCount()-1,f++,item);

                    item = new QTableWidgetItem;
                    item->setText(((Trip*)trip[j])->from);
                    show->setItem(show->rowCount()-1,f++,item);

                    item = new QTableWidgetItem;
                    item->setText(((Trip*)trip[j])->to);
                    show->setItem(show->rowCount()-1,f++,item);

                    item = new QTableWidgetItem;
                    item->setText(((Trip*)trip[j])->regularity);
                    show->setItem(show->rowCount()-1,f++,item);
                }
            }
        }
    }
    show->removeRow(show->rowCount());

    show->setFixedSize(show->columnWidth(0) * show->columnCount() + 60, show->rowHeight(0) * (show->rowCount() + 1));
    dialogWindow->setFixedSize(show->width() + 38, show->height() + 65);

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(label);
    forWidgetsDialog->addWidget(show);

    dialogWindow->setLayout(forWidgetsDialog);
    dialogWindow->exec();
}

void MainWindow::on_actionShowByRoute_triggered(){
    QDialog *dialogWindow = createDialog(QString::fromLocal8Bit("I����i�㠫쭥 �������� �3"));
    QDialogButtonBox *buttonsComboBox = createDialogButtonBox(dialogWindow);

    QLabel *labelFirst = createLabel(QString::fromLocal8Bit("�����i�� �i��ࠢ�� ���"));
    QLabel *labelSecond = createLabel(QString::fromLocal8Bit("�����i�� ��� �ਡ����"));

    QComboBox *first = new QComboBox;
    first->setMinimumHeight(30);
    for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){ // 横�: ��㢠��� ������ �i��ࠢ��� �窨
        for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
            for(int k = 0; k < ((int*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel)[POS_CNT]; k++){
                first->addItem(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->from); // ����� �������
                for(int h = 0; h < first->count(); h++){ // 横�: ��ॢiન �����i ⠪��� �������� � ᯨ��
                    QString t = first->itemText(h);
                    for(int f = h+1; f < first->count(); f++)
                        if(t == first->itemText(f)) // �� ⠪�� ������� i���
                            first->removeItem(f); // �������
                }
            }
        }
    }

    QVBoxLayout *forWidgetsDialog = new QVBoxLayout;
    forWidgetsDialog->addWidget(labelFirst);
    forWidgetsDialog->addWidget(first);
    forWidgetsDialog->addWidget(buttonsComboBox);

    dialogWindow->setLayout(forWidgetsDialog);
    int result = dialogWindow->exec();
    if(result == QDialog::Accepted){
        QComboBox *second = new QComboBox;
        second->setMinimumHeight(30);

        for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){ // 横�: ��㢠��� ������ �窨 �ਡ����
            for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){
                for(int k = 0; k < ((int*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel)[POS_CNT]; k++){
                    if(first->currentText() == ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->from){
                        second->addItem(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->to); // ����� �������
                        for(int h = 0; h < second->count(); h++){ // 横�: ��ॢiન �����i ⠪��� �������� � ᯨ��
                            QString t = second->itemText(h);
                            for(int f = h+1; f < second->count(); f++)
                                if(t == second->itemText(f)) // �� ⠪�� ������� i���
                                    second->removeItem(f); // �������
                        }
                    }
                }
            }
        }

        dialogWindow = createDialog(QString::fromLocal8Bit("I����i�㠫쭥 �������� �3"));
        buttonsComboBox = createDialogButtonBox(dialogWindow);

        forWidgetsDialog = new QVBoxLayout;
        forWidgetsDialog->addWidget(labelSecond);
        forWidgetsDialog->addWidget(second);
        forWidgetsDialog->addWidget(buttonsComboBox);

        dialogWindow->setLayout(forWidgetsDialog);
        result = dialogWindow->exec();
        if(result == QDialog::Accepted){
            dialogWindow = createDialog(QString::fromLocal8Bit("I����i�㠫쭥 �������� �3")); // �i������� �i���

            QLabel *label = createLabel(QString::fromLocal8Bit("�� ��ࠫ� ⠪�� �������:\n") + first->currentText() +
                                        QString::fromLocal8Bit(">---------->") + second->currentText());
            label->setAlignment(Qt::AlignCenter);

            QTableWidget *show = new QTableWidget;
            show->setColumnCount(5);
            show->setRowCount(0);

            QStringList columnHeads; // ���������
            columnHeads << QString::fromLocal8Bit("�i��") << QString::fromLocal8Bit("������") << QString::fromLocal8Bit("����")
                        << QString::fromLocal8Bit("�த���㢠�i���") << QString::fromLocal8Bit("������i���");
            show->setHorizontalHeaderLabels(columnHeads);
            show->setColumnWidth(3,140);

            for(int i = 0; i < ((int*)((Railway*)rail[0])->sublevel)[POS_CNT]; i++){ // ��室��� �� ᯨ��
                for(int j = 0; j < ((int*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel)[POS_CNT]; j++){ // ��室��� �� ᯨ��
                    for(int k = 0; k < ((int*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel)[POS_CNT]; k++){ // ��室��� �� ᯨ��
                        if(first->currentText() == ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->from &&
                           second->currentText() == ((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->to){ // �� ���࠯��� �� ��࠭�� �������
                            int f = 0;

                            show->insertRow(show->rowCount());

                            QTableWidgetItem *item = new QTableWidgetItem; // ����� � ⠡����
                            item->setText(((City*)((Railway*)rail[0])->sublevel[i])->city);
                            show->setItem(show->rowCount()-1,f++,item);

                            item = new QTableWidgetItem;
                            item->setText(((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->name);
                            show->setItem(show->rowCount()-1,f++,item);

                            item = new QTableWidgetItem;
                            item->setText(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->number);
                            show->setItem(show->rowCount()-1,f++,item);

                            item = new QTableWidgetItem;
                            item->setText(QString::number((int)((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->duration) +
                                          QString::fromLocal8Bit(" ��� ") + QString::number((((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->duration - (int)((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->duration)*100)
                                          + QString::fromLocal8Bit(" �"));
                            show->setItem(show->rowCount()-1,f++,item);


                            item = new QTableWidgetItem;
                            item->setText(((Trip*)((RailStation*)((City*)((Railway*)rail[0])->sublevel[i])->sublevel[j])->sublevel[k])->regularity);
                            show->setItem(show->rowCount()-1,f++,item);
                        }
                    }
                }
            }
            show->removeRow(show->rowCount());

            show->setFixedSize(show->columnWidth(0) * show->columnCount() + 60, show->rowHeight(0) * (show->rowCount() + 1));
            dialogWindow->setFixedSize(show->width() + 38, show->height() + 65);

            forWidgetsDialog = new QVBoxLayout;
            forWidgetsDialog->addWidget(label);
            forWidgetsDialog->addWidget(show);

            dialogWindow->setLayout(forWidgetsDialog);
            dialogWindow->exec();
        }
    }
}

// �㭪�i� ���᪠��� �� ����i�� ���०���� ᯨ�� � 䠩�
void MainWindow::on_actionSave_triggered(){
    QFileDialog chooseFile; //�������� �i������� �i��� ��� ������ 䠩��
    chooseFile.setAcceptMode(QFileDialog::AcceptSave); //��⠭����� �����
    chooseFile.setFileMode(QFileDialog::AnyFile); //��⠭����� ����㯭i ⨯� 䠩�i�
    chooseFile.setNameFilter("*.txt"); //䠩�� � �த������� .txt

    if(chooseFile.exec() != QDialog::Accepted) return; //�� 䠩� �� �� ��࠭��

    QString fileName = chooseFile.selectedFiles().at(0); //��ਬ�� i�'� 䠩��
    if(!fileName.endsWith(".txt")) //�� �i� �� ⥪�⮢��
        fileName += ".txt"; //஡��� ⥪�⮢��
    saveToFile(rail, fileName); //�������� �㭪�i� ���०����
}

// �㭪�i� ���᪠��� �� ����i�� �i��������� ᯨ�� i� 䠩��
void MainWindow::on_actionOpen_triggered(){
    QFileDialog chooseFile; //�������� �i������� �i��� ��� ������ 䠩��
    chooseFile.setAcceptMode(QFileDialog::AcceptOpen); //��⠭����� �����
    chooseFile.setFileMode(QFileDialog::ExistingFile); //��⠭����� ����㯭i ⨯� 䠩�i�
    chooseFile.setNameFilter("*.txt"); //䠩�� � �த������� .txt

    if(chooseFile.exec() != QDialog::Accepted) return; //�� 䠩� �� �� ��࠭��

    QString fileName = chooseFile.selectedFiles().at(0); //��ਬ�� i�'� 䠩��
    if(!fileName.endsWith(".txt")) //�� �i� �� ⥪�⮢��
        fileName += ".txt"; //஡��� ⥪�⮢��
    retrieveFromFile(rail, fileName); //�i�������
    update(); //������� ������� �i���
    on_actionShow_triggered(); //�������� ᯨ᮪
}
